#include <iostream>
#include <vector>
#include <iterator>

/*
* std::size 是一个 C++17 的新函数，用于获取容器或数组的大小。
* 语法糖
*/

int main() {
    
    // 使用 std::size 获取容器大小
    std::vector<int> vec = { 1, 2, 3, 4, 5 };
    std::cout << "Size of vector: " << std::size(vec) << std::endl; // 输出: 5


    // 使用 std::size 获取数组大小
    int arr[] = { 10, 20, 30, 40, 50 };
    std::cout << "Size of array: " << std::size(arr) << std::endl; // 输出: 5

    // 可以为自己的容器或范围提供 size() 方法，以便与 std::size 兼容。只需确保该类型具有 size() 方法即可。

    return 0;
}
