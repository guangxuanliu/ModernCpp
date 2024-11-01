#include <iostream>
#include <string>

/*
* if语句初始化器
* switch语句初始化器
* C++17引入了if语句和switch语句的初始化器，允许在if和switch语句中声明变量并初始化它们。
* 这些变量的作用域仅限于if或switch语句的范围内。
* 这样可以避免在if或switch语句之外使用这些变量，从而提高代码的可读性和可维护性。
*/

int main() {
    std::string input = "Hello, World!";

    if (auto pos = input.find("World"); pos != std::string::npos) {
        std::cout << "'World' found at position: " << pos << std::endl;
    }
    else {
        std::cout << "'World' not found." << std::endl;
    }


    int value = 2;

    switch (int x = value) {
    case 1:
        std::cout << "Value is 1" << std::endl;
        break;
    case 2:
        std::cout << "Value is 2" << std::endl;
        break;
    default:
        std::cout << "Value is not 1 or 2" << std::endl;
        break;
    }

    return 0;
}
