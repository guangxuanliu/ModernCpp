#include <iostream>

/*
* 概念：
* 希望从表达式的类型中推断出要定义的变量的类型，但是不想用该表达式的值初始化变量。
* 为了满足这一需求，C++11新标准引入了decltype类型说明符，它的作用是选择并返回操作数的数据类型。
* 在此过程中，编译器并不实陫表达式的值，只是使用表达式的类型。
*/

int main() {
    
    //decltype(f()) sum = x; // sum的类型就是函数f的返回类型，编译器不会实际调用f函数

    // delctype与const、引用
    // 因为cj是一个引用，所以decltype(cj)得到的类型是引用，这个和auto不同
    const int ci = 0, &cj = ci;
    decltype(ci) x = 0;         // x的类型是const int
    decltype(cj) y = x;         // y的类型是const int&，y绑定到x
    //decltype(cj) z;           // 错误，z是一个引用，必须初始化

    // decltype和指针
    int i = 42, *p = &i, &r = i;
    decltype(r + 0) b;          // r是一个引用，加法的结果是int，所以b是一个(未初始化的)int
    decltype(*p) c = i;         // c是int&，c绑定到i

    // decltype和括号：特别注意
    // decltype((variable))的结果永远是引用，而decltype(variable)的结果只有当variable本身是一个引用时才是引用
    decltype((i)) d = i;            // d是int&，
    decltype(i) e = i;              // e是int

    return 0;
}
