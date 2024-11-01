#include <iostream>
#include <optional>
#include <string>

/*
* std::optional 是 C++17 中引入的一个模板类，主要用于表示一个可能包含值的对象。
* 它可以用来表示某个值的可选性，通常用于函数返回值，以表明该函数可能返回有效值，也可能返回空值。
* 这种设计在处理可选值或缺失值时提供了更好的安全性和可读性。
*/

// 作为返回值
std::optional<int> findValue(bool found) {
    if (found) {
        return 42; // 返回一个有效的值
    }
    else {
        return std::nullopt; // 返回空值
    }
}

// 作为函数参数
void printValue(const std::optional<int> &value) {
    if (value) {
        std::cout << "Value: " << *value << std::endl;
    }
    else {
        std::cout << "Value not set." << std::endl;
    }
}

// 常见的操作
// has_value()：检查是否有值
// value()：获取值
// reset()：重置为无值
// *：解引用获取值



int main() {
    auto value = findValue(true);

    if (value) { // 检查是否有值
        std::cout << "Found value: " << *value << std::endl; // 解引用获取值
    }
    else {
        std::cout << "Value not found." << std::endl;
    }

    printValue(42);
    printValue(std::nullopt);

    return 0;
}
