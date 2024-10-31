#include <iostream>

/*
* 通用lambda表达式
* 通用lambda表达式是C++14的新特性，它允许我们在lambda表达式中使用auto关键字来声明参数，从而使得lambda表达式能否像函数模板一样，可以接受任意类型的参数。
*/

int main() {
    auto add = [](auto a, auto b) { return a + b; };
    std::cout << add(1, 2) << std::endl;
    std::cout << add(1.1, 2.2) << std::endl;
    std::cout << add(1, 2.2) << std::endl;
    std::cout << add(std::string("Hello"), std::basic_string("World")) << std::endl;


    // 通用lambda还可以递归调用自身，而无需使用std::function来包装
    auto power = [](auto self, auto base, int exp) -> decltype(base) {
        return exp == 0 ? 1 : base * self(self, base, exp - 1);
        };

    std::cout << power(power, 2, 10); // 输出1024


    return 0;
}