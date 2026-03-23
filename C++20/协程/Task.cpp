#include <coroutine>
#include <exception>
#include <utility>
#include <string>
#include <iostream>

// ════════════════════════════════════════════════════════════════
//  Task<T>：热启动任务（eager）
//  initial_suspend = suspend_never → 协程被调用后立即执行协程体，
//  不需要等别人来 resume。
//
//  本文件包含两个版本：
//    1. Task<T>     热启动，演示 CoAwaitAwaiter::await_ready = true 的路径
//    2. LazyTask<T> 冷启动，演示对称转移（symmetric transfer）真实触发的路径
// ════════════════════════════════════════════════════════════════
template<typename T>
struct Task {
    struct promise_type {
        T result;
        std::exception_ptr exception;

        // ----------------------------------------------------------------
        // continuation：存储"正在等我完成的那个外层协程"的句柄
        //
        // 场景：外层协程 A 执行 co_await taskB
        //   Step1：A 挂起时，把 A 自己的 handle 写入 taskB.promise.continuation
        //   Step2：taskB 执行完毕时，FinalSuspendAwaiter 读取 continuation，恢复 A
        //
        // 如果没有人 co_await 这个 Task（比如最外层的 greet），
        // continuation 就是空的 (nullptr)。
        // ----------------------------------------------------------------
        std::coroutine_handle<> continuation;

        Task<T> get_return_object() {
            return Task<T>{
                std::coroutine_handle<promise_type>::from_promise(*this)
            };
        }

        // 热启动：协程被调用后立即执行，不暂停
        std::suspend_never initial_suspend() noexcept {
            std::cout << "  [Task] initial_suspend → suspend_never，立即执行\n";
            return {};
        }

        // ----------------------------------------------------------------
        // FinalSuspendAwaiter：替代 std::suspend_always 作为 final_suspend 的返回值
        //
        // 核心问题：协程体跑完了，接下来把执行权交给谁？
        //
        // 朴素方案（直接用 suspend_always）：
        //   协程挂起 → 控制权回到"调用 resume() 的那行代码"
        //   → 那行代码继续执行 → 栈正常弹出
        //   问题：如果是深层协程链（A await B await C await D...），
        //         D 完成后要依次 resume C、B、A，每次 resume 都是一次新的
        //         函数调用，调用栈会越来越深，最终可能栈溢出。
        //
        // 对称转移方案（FinalSuspendAwaiter 返回 coroutine_handle）：
        //   await_suspend 返回"等待者的句柄" → 编译器直接跳过去（尾调用优化）
        //   → 不增加调用栈深度，O(1) 栈空间完成任意深度的协程链切换。
        // ----------------------------------------------------------------
        struct FinalSuspendAwaiter {
            // 永远返回 false：协程体结束后一定要走 await_suspend 这条路，
            // 不能跳过（因为我们需要在这里做"把控制权交回等待者"的操作）。
            bool await_ready() noexcept { return false; }

            // h：就是"我自己（刚刚执行完的这个协程）"的句柄
            //
            // 对称转移的精髓：
            //   返回 coroutine_handle 时，编译器不会回到调用方的 resume() 处，
            //   而是直接恢复返回的那个 handle 所代表的协程（相当于尾调用）。
            //
            //   返回 noop_coroutine() 时：什么都不做，当前协程彻底挂起（done=true），
            //   控制权返回给最近一次调用过 resume() 的代码（通常是 main）。
            std::coroutine_handle<> await_suspend(
                std::coroutine_handle<promise_type> h) noexcept
            {
                auto cont = h.promise().continuation;
                if (cont) {
                    std::cout << "  [FinalSuspendAwaiter] 有等待者，对称转移 → 恢复外层协程\n";
                    return cont;                    // 对称转移：直接跳到等待者
                } else {
                    std::cout << "  [FinalSuspendAwaiter] 无等待者，返回 noop_coroutine\n";
                    return std::noop_coroutine();   // 无事可做，正常结束
                }
            }

            void await_resume() noexcept {}
        };

        FinalSuspendAwaiter final_suspend() noexcept { return {}; }

        void return_value(T val) {
            std::cout << "  [Task] return_value() 保存结果\n";
            result = std::move(val);
        }

        void unhandled_exception() { exception = std::current_exception(); }
    };

    // ----------------------------------------------------------------
    // CoAwaitAwaiter：当外层协程执行 co_await someTask 时，
    //              编译器先调用 someTask.operator co_await()，
    //              得到这个 CoAwaitAwaiter，然后走三段式协议。
    //
    // 两条执行路径：
    //
    //  路径 A（Task 已完成，await_ready = true）：
    //    Task 在被 co_await 之前就已经跑完了（热启动的典型情况）。
    //    await_ready 返回 true → 跳过 await_suspend，直接 await_resume 取结果。
    //    外层协程不会挂起，就像调用普通函数一样。
    //
    //  路径 B（Task 未完成，await_ready = false）：
    //    Task 还在等某个异步事件（比如 IO），没有跑完。
    //    await_ready 返回 false → 进入 await_suspend：
    //      1. 把外层协程的 handle 存到 Task.promise.continuation
    //      2. 返回 Task 的 handle（对称转移）→ 跳进 Task 继续执行
    //    Task 执行完毕时，FinalSuspendAwaiter 读出 continuation，对称转移回外层协程。
    // ----------------------------------------------------------------
    struct CoAwaitAwaiter {
        std::coroutine_handle<promise_type> handle; // 被等待的 Task 的句柄

        // 被等待的 Task 是否已经跑完了？
        bool await_ready() noexcept {
            bool done = handle.done();
            std::cout << "  [CoAwaitAwaiter] await_ready = " << (done ? "true（已完成，跳过挂起）" : "false（未完成，需要挂起）") << "\n";
            return done;
        }

        // 只有 await_ready = false 时才会进入这里
        // caller：正在执行 co_await 的那个外层协程的句柄
        std::coroutine_handle<> await_suspend(
            std::coroutine_handle<> caller) noexcept
        {
            std::cout << "  [CoAwaitAwaiter] await_suspend：保存外层协程，对称转移 → 进入 Task\n";

            // 第1步：把外层协程（caller）登记为"等我完成后要恢复的协程"
            handle.promise().continuation = caller;

            // 第2步：对称转移，直接跳进被等待的 Task 开始/继续执行。
            // 注意：这里 return handle 不是"返回给调用方"，
            //       而是告诉编译器"请立刻切换到 handle 这个协程"。
            return handle;
        }

        // 恢复后取出结果，这就是 co_await 表达式的返回值
        T await_resume() {
            std::cout << "  [CoAwaitAwaiter] await_resume：取出结果\n";
            if (handle.promise().exception)
                std::rethrow_exception(handle.promise().exception);
            return std::move(handle.promise().result);
        }
    };

    // operator co_await：让 Task 成为 Awaitable
    // 外层协程写 co_await someTask 时，编译器调用此函数得到 CoAwaitAwaiter
    CoAwaitAwaiter operator co_await() noexcept {
        return CoAwaitAwaiter{handle};
    }

    std::coroutine_handle<promise_type> handle;

    explicit Task(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Task() { if (handle) handle.destroy(); }
    Task(const Task&) = delete;
    Task(Task&& o) : handle(std::exchange(o.handle, {})) {}
};


// ════════════════════════════════════════════════════════════════
//  LazyTask<T>：冷启动任务（lazy）
//  initial_suspend = suspend_always → 协程被调用后立即挂起，
//  只有当外层协程 co_await 它时，才通过对称转移跳进来执行。
//
//  这个版本能让 CoAwaitAwaiter::await_suspend 的对称转移逻辑真实触发，
//  因为 LazyTask 被调用时一定是挂起状态（done = false），
//  所以 await_ready 一定返回 false，一定会走 await_suspend。
// ════════════════════════════════════════════════════════════════
template<typename T>
struct LazyTask {
    struct promise_type {
        T result;
        std::exception_ptr exception;
        std::coroutine_handle<> continuation;

        LazyTask<T> get_return_object() {
            return LazyTask<T>{
                std::coroutine_handle<promise_type>::from_promise(*this)
            };
        }

        // 冷启动：创建后立刻挂起，等人来 co_await 才开始执行
        std::suspend_always initial_suspend() noexcept {
            std::cout << "  [LazyTask] initial_suspend → suspend_always，等待 co_await 启动\n";
            return {};
        }

        struct FinalSuspendAwaiter {
            bool await_ready() noexcept { return false; }
            std::coroutine_handle<> await_suspend(
                std::coroutine_handle<promise_type> h) noexcept
            {
                auto cont = h.promise().continuation;
                if (cont) {
                    std::cout << "  [LazyTask::FinalSuspendAwaiter] 对称转移 → 恢复外层协程\n";
                    return cont;
                } else {
                    std::cout << "  [LazyTask::FinalSuspendAwaiter] 无等待者，返回 noop_coroutine\n";
                    return std::noop_coroutine();
                }
            }
            void await_resume() noexcept {}
        };

        FinalSuspendAwaiter final_suspend() noexcept { return {}; }

        void return_value(T val) {
            std::cout << "  [LazyTask] return_value() 保存结果\n";
            result = std::move(val);
        }
        void unhandled_exception() { exception = std::current_exception(); }
    };

    struct LazyCoAwaitAwaiter {
        std::coroutine_handle<promise_type> handle;

        // 冷启动任务在 co_await 时一定是挂起的（done = false），
        // 所以 await_ready 永远返回 false，一定会进 await_suspend。
        bool await_ready() noexcept {
            std::cout << "  [LazyCoAwaitAwaiter] await_ready = false（冷启动任务肯定没完成）\n";
            return false;
        }

        std::coroutine_handle<> await_suspend(
            std::coroutine_handle<> caller) noexcept
        {
            std::cout << "  [LazyCoAwaitAwaiter] await_suspend：保存外层协程，对称转移 → 启动 LazyTask\n";
            handle.promise().continuation = caller; // 记住谁在等我
            return handle;                          // 对称转移：跳进 LazyTask 执行
        }

        T await_resume() {
            std::cout << "  [LazyCoAwaitAwaiter] await_resume：取出结果\n";
            if (handle.promise().exception)
                std::rethrow_exception(handle.promise().exception);
            return std::move(handle.promise().result);
        }
    };

    LazyCoAwaitAwaiter operator co_await() noexcept {
        return LazyCoAwaitAwaiter{handle};
    }

    std::coroutine_handle<promise_type> handle;

    explicit LazyTask(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~LazyTask() { if (handle) handle.destroy(); }
    LazyTask(const LazyTask&) = delete;
    LazyTask(LazyTask&& o) : handle(std::exchange(o.handle, {})) {}
};


// ════════════════════════════════════════════════════════════════
//  演示一：热启动路径（Task，await_ready = true 的情况）
//
//  执行流程：
//    main 调用 greet()
//    → greet 立即执行（suspend_never）
//      → greet 调用 compute()
//        → compute 立即执行（suspend_never）
//        → co_return 42 → 结果保存，compute 到达 final_suspend，done=true
//        → FinalSuspendAwaiter: continuation=空 → noop_coroutine → compute 彻底结束
//      → co_await compute_task：CoAwaitAwaiter::await_ready() = true（已完成！）
//        → 跳过 await_suspend，直接 await_resume 取出 42
//      → co_return "The answer is 42" → greet 到达 final_suspend，done=true
//    → main 直接访问 task.handle.promise().result
// ════════════════════════════════════════════════════════════════
Task<int> compute() {
    std::cout << "  [compute] 开始执行\n";
    co_return 42;
}

Task<std::string> greet() {
    std::cout << "  [greet] 开始执行，准备 co_await compute()\n";
    int val = co_await compute();
    std::cout << "  [greet] compute 完成，val = " << val << "\n";
    co_return "The answer is " + std::to_string(val);
}


// ════════════════════════════════════════════════════════════════
//  演示二：冷启动路径（LazyTask，await_suspend 对称转移真实触发）
//
//  执行流程：
//    main 调用 greet_lazy() → 立刻挂起（suspend_always），不执行任何协程体
//    main 调用 task.handle.resume() 手动启动
//    → greet_lazy 从 initial_suspend 之后继续
//      → greet_lazy 调用 compute_lazy()
//        → compute_lazy 立刻挂起（suspend_always），不执行协程体
//      → co_await compute_lazy_task：
//        → LazyCoAwaitAwaiter::await_ready() = false（冷启动任务还没运行）
//        → LazyCoAwaitAwaiter::await_suspend(greet_handle)：★对称转移一★
//            continuation = greet_handle（记住谁在等）
//            return compute_lazy_handle → 跳进 compute_lazy 执行
//      → compute_lazy 执行：co_return 42 → 结果保存
//      → compute_lazy FinalSuspendAwaiter::await_suspend：★对称转移二★
//            continuation = greet_handle（之前存的）
//            return greet_handle → 跳回 greet_lazy
//      → greet_lazy 恢复：await_resume 取出 42，val=42
//      → co_return "The answer is 42" → greet_lazy done=true
//    → task.handle.resume() 在 main 中返回
//    → main 读取结果
// ════════════════════════════════════════════════════════════════
LazyTask<int> compute_lazy() {
    std::cout << "  [compute_lazy] 被对称转移启动，开始执行\n";
    co_return 42;
}

LazyTask<std::string> greet_lazy() {
    std::cout << "  [greet_lazy] 被 resume 启动，准备 co_await compute_lazy()\n";
    int val = co_await compute_lazy();
    std::cout << "  [greet_lazy] compute_lazy 完成，val = " << val << "\n";
    co_return "The answer is " + std::to_string(val);
}


int main() {
    // ── 演示一：热启动 ──────────────────────────────────────────
    std::cout << "═══ 演示一：热启动（Task，suspend_never）═══\n";
    std::cout << "调用 greet()...\n";
    auto task = greet();

    // 因为 initial_suspend = suspend_never，greet 和 compute 都同步跑完了
    // task.handle.done() 此时为 true，结果已经在 promise 里
    std::cout << "结果：" << task.handle.promise().result << "\n\n";

    // ── 演示二：冷启动（对称转移真实触发）─────────────────────
    std::cout << "═══ 演示二：冷启动（LazyTask，suspend_always）═══\n";
    std::cout << "调用 greet_lazy()（此时协程立刻挂起，不执行任何协程体）...\n";
    auto lazy_task = greet_lazy();

    // greet_lazy 挂在 initial_suspend，什么都没跑
    std::cout << "greet_lazy 已挂起，done = " << lazy_task.handle.done() << "\n";

    // 手动 resume：触发整条对称转移链
    // greet_lazy → (对称转移) → compute_lazy → (对称转移) → greet_lazy → done
    std::cout << "手动 resume，触发对称转移链...\n";
    lazy_task.handle.resume();

    std::cout << "结果：" << lazy_task.handle.promise().result << "\n";

    return 0;
}