#include <iostream>
#include <span>
#include <vector>
#include <array>

/*
* std::span 是 C++20 新增的一个类模板，用于表示连续的内存区间。
* std::span 可以用于数组、std::vector、std::array 等容器，提供了统一的访问接口。
* std::span 不拥有数据，只是对数据的一个引用，因此不需要担心内存管理问题。
* 类似于C++17中的std::string_view，std::span 也是一个只读的视图。
*/


// 常用函数
// size() : 获取容器的大小
// empty() : 判断容器是否为空
// operator[] : 通过下标访问元素
// subspan() : 获取容器的子范围


void print_span(std::span<int> sp) {
    for (int i : sp) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

int main() {
    int arr[] = { 1, 2, 3, 4, 5 };
    std::vector<int> vec = { 6, 7, 8, 9, 10 };
    std::array<int, 5> arr2 = { 11, 12, 13, 14, 15 };

    // 创建 std::span 的不同方法
    std::span<int> sp1(arr);
    std::span<int> sp2(vec);
    std::span<int> sp3(arr2);

    print_span(sp1);  // 输出: 1 2 3 4 5
    print_span(sp2);  // 输出: 6 7 8 9 10
    print_span(sp3);  // 输出: 11 12 13 14 15

    // 截取子范围
    std::span<int> sp4 = sp1.subspan(1, 3);  // 从索引 1 开始，取 3 个元素
    print_span(sp4);  // 输出: 2 3 4
}
