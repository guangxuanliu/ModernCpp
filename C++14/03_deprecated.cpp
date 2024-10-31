#include <iostream>

/*
* C++14 引入了[[deprecated]]属性，用于标记已弃用的函数、变量或类型。
* 当使用已弃用的函数、变量、类型、枚举、模板特化时，编译器会产生警告。
* deprecated接受一个可选的字符串参数，用于提供有关为什么已弃用的信息或替代的方法。
*/

[[deprecated("Use newFunction instead")]]
void oldFunction() {
    std::cout << "This function is deprecated." << std::endl;
}

void newFunction() {
    std::cout << "This is the new function." << std::endl;
}

int main() {
    oldFunction(); // 使用已弃用的函数，编译时会产生警告
    // windows下警告如下：
    // warning C4996: 'oldFunction': Use newFunction instead

    newFunction(); // 使用新函数
    return 0;
}