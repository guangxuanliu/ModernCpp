#include <iostream>
#include <initializer_list>
#include <cstdarg>


/*
* initializer_list
* 可变函数参数
*/

// C++方式，实现可变参数函数
void error_msg(std::initializer_list<std::string> il)
{
    for (auto beg = il.begin(); beg != il.end(); ++beg)
    {
        std::cout << *beg << " ";
    }
    std::cout << std::endl;
}

// C方式，实现可变参数函数
void error_msg2(int numOfArgs, ...)
{
    va_list args;
    va_start(args, numOfArgs);
    for (int i = 0; i < numOfArgs; ++i)
    {
        std::cout << va_arg(args, std::string) << " ";
    }
    std::cout << std::endl;
    va_end(args);
}

int main()
{
    error_msg({ "functionX", "expected", "actual" });
    error_msg2(3, "functionX", "expected", "actual");


    return 0;
}


// Q：initializer_list和vector的区别？
// A：1、initializer_list中的值是常量的，不能修改
//    2、initializer_list支持的操作有限，比vector更轻量
// 
// Q：是否还有其他实现可变参数函数的方式？
// A：有，可变参数模板。见：19_variadic_template.cpp
