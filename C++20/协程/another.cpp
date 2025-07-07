#include <iostream>
#include <coroutine>

struct promise
{

    struct promise_type
    {

        // 决定协程初始化后的行为：挂起、还是直接运行
        std::suspend_always initial_suspend()
        {
            return {};
        }

        // 决定协程结束后的行为：挂起、还是直接退出
        std::suspend_always final_suspend() noexcept
        {
            return {};
        }

        // 协程的返回值，用于协程函数返回promise对象
        promise get_return_object()
        {
            return promise{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        // 出现没有捕获的异常时的行为
        void unhandled_exception()
        {
            // 程序中止
            terminate();
        }

        // co_yield 时触发这个函数
        std::suspend_always yield_value(int i)
        {
            my_data = i;
            return {};
        }

        // co_return 时触发这个函数，它还有另一种形态叫return_value
        void return_void() {}

        // 用于co_yield时保存中间变量
        int my_data;
    };

    // 协程跑一步，并且得到co_yield的值
    int step()
    {
        // resume 协程恢复，其实就是跑一步
        // 跑到下一个co_yield, co_await, co_return或者协程结束的位置
        handle.resume();

        // 取得promise_type对象，把里面的中间变量返回出来
        return handle.promise().my_data;
    }

    // 协程句柄，用于控制协程行为的
    std::coroutine_handle<promise_type> handle;
};

promise fun()
{
    int i = 0;
    while (1)
    {
        co_yield i;
        i++;
    }
}

int main()
{
    promise coro = fun();

    std::cout << "第1次跑到co_yield, i = " << coro.step() << std::endl;
    std::cout << "第2次跑到co_yield, i = " << coro.step() << std::endl;
    std::cout << "第3次跑到co_yield, i = " << coro.step() << std::endl;

    return 0;
}