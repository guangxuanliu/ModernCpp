#include <iostream>

int main()
{
    int a = 5;
    int b = 6;

    // Lambda function
    auto sum = [](int a, int b) -> int {
        return a + b;
    };

    std::cout << "Sum: " << sum(a, b) << std::endl;

    return 0;
}


// 概念
// 可调用对象：函数、函数指针、函数对象、Lambda表达式
