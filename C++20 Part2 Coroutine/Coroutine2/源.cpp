#include <iostream>
#include <future>
#include <coroutine>
#include <chrono>
#include <thread>
#include <tuple>
#include <utility>

// 等待多个协程的组合
template<typename... Ts>
struct WhenAll {
    std::tuple<Ts...> futures;

    WhenAll(Ts... fs) : futures(std::make_tuple(std::move(fs)...)) {}

    struct awaiter {
        WhenAll *whenAll;

        bool await_ready() const noexcept {
            return false;
        }

        void await_suspend(std::coroutine_handle<> handle) {
            std::thread([this, handle] {
                // 等待所有future完成
                std::apply([](auto&... fs) {
                    (fs.wait(), ...); // 等待所有任务
                    }, whenAll->futures);
                handle.resume(); // 恢复协程
                }).detach();
        }

        auto await_resume() {
            return std::apply([](auto&... fs) {
                return std::make_tuple(fs.get()...); // 返回所有结果
                }, whenAll->futures);
        }
    };

    awaiter operator co_await() {
        return awaiter{ this };
    }
};

struct Task {
    struct promise_type {
        Task get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };
};

Task exampleCoroutine() {
    std::cout << "Starting coroutine to await multiple async operations..." << std::endl;

    // 启动多个异步任务
    auto future1 = std::async(std::launch::async, [] {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return 1; // 返回结果1
        });

    auto future2 = std::async(std::launch::async, [] {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return 2; // 返回结果2
        });

    auto future3 = std::async(std::launch::async, [] {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return 3; // 返回结果3
        });

    // 使用 WhenAll 等待所有结果
    auto results = co_await WhenAll{ std::move(future1), std::move(future2), std::move(future3) };

    std::cout << "All async operations completed with results: "
        << std::get<0>(results) << ", "
        << std::get<1>(results) << ", "
        << std::get<2>(results) << std::endl;
}

int main() {
    exampleCoroutine();
    std::this_thread::sleep_for(std::chrono::seconds(5)); // 确保主线程不结束
    return 0;
}
