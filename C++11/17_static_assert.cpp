#include <iostream>
#include <cassert>

/*
* assert
* 如果表达式为假，则显示错误消息，并终止程序执行（通过std::abort）
* assert() 会在 release 模式下被编译器优化掉
* assert() 是宏，所以需要包含头文件 <cassert>
* 
* 
* static_assert
* 在 编译时 检查表达式是否为真，如果为假，则显示错误消息，因此表达式必须是常量表达式
* static_assert() 在 release 模式下 不会 被编译器优化掉
* 因为static_assert是在编译器阶段检查的，所以它没有运行时开销
* static_assert是关键字，所以不需要包含头文件
* static_assert在C++17之前，必须传入第二个参数，用于描述性文本，C++17之后可以省略第二个参数
* 
* 最佳实践：
* 尽量使用 static_assert()，因为它是在编译器阶段检查的，没有运行时开销
*/


double divide(int a, int b)
{
    // 通过添加描述性文本，可以更好地理解错误
    assert(b != 0 && "b can not be zero!");
    return a / b;
}


void func()
{
    std::cout << sizeof(int) << std::endl;          // 4
    std::cout << sizeof(long) << std::endl;         // 4
    std::cout << sizeof(long long) << std::endl;    // 8

    static_assert(sizeof(int) == 4, "int must be 4 bytes");
    //static_assert(sizeof(long) == 8, "long must be 8 bytes"); // 编译错误
    static_assert(sizeof(long long) == 8); // C++17之后，可以省略第二个参数
}

int main()
{
#ifdef NDEBUG
    std::cout << "NDEBUG" << std::endl;
#else
    std::cout << "DEBUG" << std::endl;
#endif // NDEBUG


    std::cout << divide(10, 2) << std::endl;
    //std::cout << divide(10, 0) << std::endl;

    func();

    return 0;
}

// Q：什么时候使用断言，什么时候使用错误处理？
// 断言：
//  断言是用于检查程序员的错误，而不是用户的错误。断言用于检测开发过程中不应该发生的事情，如果真的发生了，那么是程序员的责任。 
//  断言不允许从错误中恢复，而是终止程序执行。断言是一种调试工具，不是一种错误处理机制。
//  断言在Release模式下会被编译器优化掉，所以不会有运行时开销。代码中可大量使用断言，用于检查程序员的错误。
// 错误处理：
//  错误处理用于检测用户的错误，比如文件不存在、网络连接失败等。
//  错误处理是一种恢复机制，允许程序从错误中恢复。错误处理也可能不从错误中恢复，而是终止程序执行。
//  错误处理在Release模式下不会被编译器优化掉，所以会有运行时开销。

// 最佳实践：
// 下面的代码，最好既使用断言，又使用错误处理。
double divide_good(int a, int b)
{
    assert(b != 0 && "b can not be zero!");
    if (b == 0)
    {
        throw std::runtime_error("b can not be zero!");
    }
    return static_cast<double>(a) / b;
}