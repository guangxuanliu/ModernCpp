#include <iostream>

/*
* 折叠表达式
* 用于对模板参数包中的参数进行操作，能够大幅简化对可变参数模板的操作。
* 折叠表达式的语法为：(pack op ...)，其中pack和...可以任意组合。
* 其中 pack 是参数包，op 是二元操作符，init 是初始值。
* 折叠表达式的结果是对参数包中的参数进行 op 操作的结果。
* 
* 可变参数模板参考：C++11文件夹中的19_variadic_template.cpp
*/

template<typename... Args>
int sum(Args... args) {
    return (args + ...);
}

template<typename... Args>
int sum2(Args... args) {
    return (0 + ... + args);
}

template<typename... Args>
int sum3(Args... args) {
    return (args + ... + 10);
}

template<typename... Args>
int sum4(Args... args) {
    return (10 + ... + args);
}

template<typename... Args>
int product(Args... args) {
    return (args * ...);
}

template<typename... Args>
bool all_true(Args... args) {
    return (args && ...);
}

template<typename... Args>
bool any_true(Args... args) {
    return (args || ...);
}


int main() {
    std::cout << "Sum: " << sum(1, 2, 3, 4, 5) << std::endl;                    // 输出: Sum: 15
    std::cout << "Sum2: " << sum2(1, 2, 3, 4, 5) << std::endl;                  // 输出: Sum: 15
    std::cout << "Sum3: " << sum3(1, 2, 3, 4, 5) << std::endl;                  // 输出: Sum: 25
    std::cout << "Sum4: " << sum4(1, 2, 3, 4, 5) << std::endl;                  // 输出: Sum: 25
    std::cout << "Product: " << product(1, 2, 3, 4, 5) << std::endl;            // 输出: Product: 120
    std::cout << "All true: " << all_true(true, true, false) << std::endl;      // 输出: All true: 0
    std::cout << "Any true: " << any_true(false, true, false) << std::endl;     // 输出: Any true: 1



    return 0;
}
