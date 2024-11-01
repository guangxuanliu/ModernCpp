// main.cpp
#include <iostream>
#include "04_inline_variable.h"

/*
* C++17 引入了 inline 变量，可以在头文件中定义变量，而不会出现重复定义的问题。
* 在C++17之前，仅仅只有函数可以被定义为 inline。
*/

extern void change_value(); // 声明函数

int main() {
    change_value();
    std::cout << "Global value: " << global_value << std::endl; // 使用 inline 变量
    return 0;
}
