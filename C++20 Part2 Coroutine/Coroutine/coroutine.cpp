#include <coroutine>
#include <iostream>
/*
* 协程是一个可以被挂起和恢复的函数，它可以在执行过程中暂停，然后在稍后的某个时候恢复执行。
* 协程的执行过程中，可以多次暂停和恢复，这样可以实现一种类似于迭代器的功能。
* 协程的实现是通过生成器(generator)和异步任务(async)来实现的。
* 生成器是一种协程，它可以生成一系列的值，这些值可以被调用者获取。
* 异步任务是一种协程，它可以在后台执行一些任务，然后在任务完成后通知调用者。
*/

// https://www.bennyhuo.com/book/cpp-coroutines/
// https://zhuanlan.zhihu.com/p/649680819
// https://www.zhihu.com/question/625089836


// 等待器（awaiter）是一个结构体，它包含了协程的挂起和恢复逻辑。
// suspend_always 是一个空结构体，它的作用是告诉编译器在协程的某个点暂停执行。
// suspend_never 是一个空结构体，它的作用是告诉编译器在协程的某个点不暂停执行。

struct Generator 
{
    struct promise_type 
    {
        // 用于co_yield保存当前值
        int current_value;

        // 协程的返回值类型
        auto get_return_object() 
        {
            return Generator
            {
                std::coroutine_handle<promise_type>::from_promise(*this) 
            }; 
        }

        // 调用协程函数时，在进入协程函数之前，会先进入该函数
        // 函数返回suspend_always，代表协程初始化之后，先挂起
        // 如果返回suspend_never，则协程初始化之后，不挂起，直接执行协程函数，直至遇到co_yield、co_return、co_await关键字
        std::suspend_always initial_suspend() 
        { 
            std::cout << "initial_suspend()" << std::endl;
            return {}; 
        }

        // 当协程函数执行完毕，会进入该函数
        // 函数返回suspend_always，代表协程结束之后，再次挂起
        // 如果返回suspend_never，则协程结束之后，不挂起，直接结束协程
        std::suspend_always final_suspend() noexcept 
        { 
            std::cout << "final_suspend()" << std::endl;
            return {}; 
        }

        // 当协程函数遇到co_yield关键字时，会进入该函数
        std::suspend_always yield_value(int value) 
        {
            std::cout << "yield_value(" << value << ")" << std::endl;
            current_value = value;
            return {};
        }
        void unhandled_exception() 
        { 
            std::cout << "unhandled_exception()" << std::endl;
            std::terminate(); 
        }

        // 当协程函数遇到co_return关键字时，或协程函数执行完毕后，会进入该函数
        void return_void() 
        {
            std::cout << "return_void()" << std::endl;
        }
    };

    // 协程句柄
    std::coroutine_handle<promise_type> handle;

    Generator(std::coroutine_handle<promise_type> h) : handle(h) 
    {
        std::cout << "Generator()" << std::endl;
    }

    ~Generator() 
    { 
        std::cout << "~Generator()" << std::endl;
        handle.destroy(); 
    }
    
    int getNextValue() 
    {
        std::cout << "getNextValue()" << std::endl;
        if (!handle.done()) 
        {
            handle.resume();
            return handle.promise().current_value;
        }
        return -1; // Indicate the end
    }
};

// 只要包含co_yield、co_return、co_await关键字的函数，就是一个协程函数
Generator counter(int max) 
{
    for (int i = 0; i <= max; ++i) 
    {
        std::cout << "co_yield " << i << std::endl;
        co_yield i;
    }
}

int main() 
{
    auto gen = counter(5);
    while (true) 
    {
        int value = gen.getNextValue();
        if (value == -1) break;
        std::cout << "Generated value: " << value << std::endl;
    }
    return 0;
}
