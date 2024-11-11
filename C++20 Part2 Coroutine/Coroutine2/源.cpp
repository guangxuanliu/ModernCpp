#include <iostream>
#include <future>
#include <coroutine>
#include <chrono>
#include <thread>
#include <tuple>
#include <utility>

// �ȴ����Э�̵����
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
                // �ȴ�����future���
                std::apply([](auto&... fs) {
                    (fs.wait(), ...); // �ȴ���������
                    }, whenAll->futures);
                handle.resume(); // �ָ�Э��
                }).detach();
        }

        auto await_resume() {
            return std::apply([](auto&... fs) {
                return std::make_tuple(fs.get()...); // �������н��
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

    // ��������첽����
    auto future1 = std::async(std::launch::async, [] {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return 1; // ���ؽ��1
        });

    auto future2 = std::async(std::launch::async, [] {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return 2; // ���ؽ��2
        });

    auto future3 = std::async(std::launch::async, [] {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return 3; // ���ؽ��3
        });

    // ʹ�� WhenAll �ȴ����н��
    auto results = co_await WhenAll{ std::move(future1), std::move(future2), std::move(future3) };

    std::cout << "All async operations completed with results: "
        << std::get<0>(results) << ", "
        << std::get<1>(results) << ", "
        << std::get<2>(results) << std::endl;
}

int main() {
    exampleCoroutine();
    std::this_thread::sleep_for(std::chrono::seconds(5)); // ȷ�����̲߳�����
    return 0;
}
