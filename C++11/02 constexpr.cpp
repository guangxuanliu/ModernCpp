#include <iostream>
using namespace std;

int j = 0;
constexpr int i = 42;

constexpr int new_sz() { return 42; }

int main()
{
    
    /*
    * 概念：常量表达式，指值不会改变并且在编译时就能得到计算结果的表达式
    */
    const int max_files = 20;           // max_files 是常量表达式
    const int limit = max_files + 1;    // limit 是常量表达式
    int staff_size = 27;                // staff_size 不是常量表达式

    /*
    * constexpr变量
    */
    // 在一个复杂系统中，很难分辨一个初始值到底是不是常量表达式，所以C++11 引入 constexpr 关键字，用于声明常量表达式，以便由编译器验证变量的值是否是一个常量表达式

    constexpr int mf = 20;               // 20 是常量表达式
    constexpr int limit2 = mf + 1;       // mf + 1 是常量表达式
    // constexpr int sz = size();           // 当 size() 是一个 constexpr 函数时，sz 是常量表达式

    // 指针和constexpr
    const int *p = nullptr;              // p 是一个指向整型常量的指针，即底层const
    constexpr int *q = nullptr;          // q 是一个指向整型的常量指针，即顶层const

    // 下面的这些也正确
    // i和j都必须定义在函数体之外
    // 因为constexpr要求在编译时就得到计算结果
    constexpr const int *p1 = &i;        // p1 是常量指针，指向整型常量
    constexpr int *p2 = &j;              // p2 是常量指针，指向整型

    /*
    * constexpr函数
    */
    // constexpr函数是指能用于常量表达式的函数
    // constexpr函数的返回值和所有形参都必须是字面值类型, 且函数体中必须有且只有一条return语句
    // new_sz() 是一个 constexpr 函数
    constexpr int foo = new_sz();        // 正确：foo 是一个常量表达式

    // 和inline函数一样，constexpr函数通常放在头文件中


    return 0;
}