#include <iostream>
#include <vector>

/*
* C++14 引入了 auto 和 decltype(auto) 用于函数返回值类型推导
* auto 用于推导函数返回值类型，decltype(auto) 用于保留返回值类型的引用
*/

auto sum(int a, int b) {
    return a + b; // 返回 int
}

auto createVector() {
    return std::vector<int>{1, 2, 3}; // 返回 std::vector<int>
}

decltype(auto) getValue(std::vector<int> &vec, int index) {
    return vec[index]; // 保留引用
}

int main() {
    auto result = sum(5, 10);
    std::cout << "Sum: " << result << std::endl;

    auto vec = createVector();
    for (const auto &v : vec) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    getValue(vec, 1) = 100;
    for (const auto &v : vec) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    return 0;
}