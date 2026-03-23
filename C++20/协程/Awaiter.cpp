#include <coroutine>
#include <functional>
#include <iostream>

// 模拟一个异步 IO 完成通知
struct AsyncIO {
    std::function<void()> callback;  // 操作完成时调用
    int result;
    
    void complete(int val) {
        result = val;
        callback();  // 通知等待者
    }
};

// 等待 AsyncIO 完成的 Awaiter
struct IOAwaiter {
    AsyncIO& io;
    
    // IO 操作还没完成，需要挂起
    bool await_ready() { return false; }
    
    // 挂起时：保存 handle，注册回调
    void await_suspend(std::coroutine_handle<> h) {
        io.callback = [h]() mutable {
            h.resume();  // IO 完成时恢复协程
        };
    }
    
    // 恢复时：返回 IO 结果
    int await_resume() {
        return io.result;
    }
};

// 让 AsyncIO 直接支持 co_await
IOAwaiter operator co_await(AsyncIO& io) {
    return IOAwaiter{io};
}

// 协程任务类型
struct Task {
    struct promise_type {
        Task get_return_object() { return {}; }
        std::suspend_never  initial_suspend() { return {}; }
        std::suspend_never  final_suspend()   noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };
};

// 使用自定义 Awaiter 的协程
Task do_work(AsyncIO& io) {
    std::cout << "开始等待 IO...\n";
    int result = co_await io;  // 挂起，直到 io.complete() 被调用
    std::cout << "IO 完成，结果：" << result << "\n";
}

int main() {
    AsyncIO io;
    do_work(io);  // 协程启动，打印"开始等待 IO..."，然后挂起
    
    std::cout << "主线程继续执行...\n";
    
    io.complete(42);  // 模拟 IO 完成，这里会 resume 协程
    // 协程打印"IO 完成，结果：42"
    
    return 0;
}