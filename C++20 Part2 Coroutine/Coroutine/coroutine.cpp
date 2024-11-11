#include <coroutine>
#include <iostream>
/*
* Э����һ�����Ա�����ͻָ��ĺ�������������ִ�й�������ͣ��Ȼ�����Ժ��ĳ��ʱ��ָ�ִ�С�
* Э�̵�ִ�й����У����Զ����ͣ�ͻָ�����������ʵ��һ�������ڵ������Ĺ��ܡ�
* Э�̵�ʵ����ͨ��������(generator)���첽����(async)��ʵ�ֵġ�
* ��������һ��Э�̣�����������һϵ�е�ֵ����Щֵ���Ա������߻�ȡ��
* �첽������һ��Э�̣��������ں�ִ̨��һЩ����Ȼ����������ɺ�֪ͨ�����ߡ�
*/

// https://www.bennyhuo.com/book/cpp-coroutines/
// https://zhuanlan.zhihu.com/p/649680819
// https://www.zhihu.com/question/625089836


// �ȴ�����awaiter����һ���ṹ�壬��������Э�̵Ĺ���ͻָ��߼���
// suspend_always ��һ���սṹ�壬���������Ǹ��߱�������Э�̵�ĳ������ִͣ�С�
// suspend_never ��һ���սṹ�壬���������Ǹ��߱�������Э�̵�ĳ���㲻��ִͣ�С�

struct Generator 
{
    struct promise_type 
    {
        // ����co_yield���浱ǰֵ
        int current_value;

        // Э�̵ķ���ֵ����
        auto get_return_object() 
        {
            return Generator
            {
                std::coroutine_handle<promise_type>::from_promise(*this) 
            }; 
        }

        // ����Э�̺���ʱ���ڽ���Э�̺���֮ǰ�����Ƚ���ú���
        // ��������suspend_always������Э�̳�ʼ��֮���ȹ���
        // �������suspend_never����Э�̳�ʼ��֮�󣬲�����ֱ��ִ��Э�̺�����ֱ������co_yield��co_return��co_await�ؼ���
        std::suspend_always initial_suspend() 
        { 
            std::cout << "initial_suspend()" << std::endl;
            return {}; 
        }

        // ��Э�̺���ִ����ϣ������ú���
        // ��������suspend_always������Э�̽���֮���ٴι���
        // �������suspend_never����Э�̽���֮�󣬲�����ֱ�ӽ���Э��
        std::suspend_always final_suspend() noexcept 
        { 
            std::cout << "final_suspend()" << std::endl;
            return {}; 
        }

        // ��Э�̺�������co_yield�ؼ���ʱ�������ú���
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

        // ��Э�̺�������co_return�ؼ���ʱ����Э�̺���ִ����Ϻ󣬻����ú���
        void return_void() 
        {
            std::cout << "return_void()" << std::endl;
        }
    };

    // Э�̾��
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

// ֻҪ����co_yield��co_return��co_await�ؼ��ֵĺ���������һ��Э�̺���
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
