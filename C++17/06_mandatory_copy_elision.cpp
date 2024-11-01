#include <iostream>

/*
* C++17 强制拷贝省略
* 该特性和编译器有关，使用vs2010来编译，仍然只输出"Constructed"，可能是编译器自动优化了
*/

struct Example {
    Example() { std::cout << "Constructed\n"; }
    Example(const Example &) { std::cout << "Copied\n"; }
};

Example create() {
    return Example();       // C++17 中不会生成临时对象
}

int main() {
    Example ex = create(); // 只会输出 "Constructed"
    return 0;
}