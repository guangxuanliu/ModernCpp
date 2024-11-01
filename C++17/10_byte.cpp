#include <iostream>
#include <cstddef>

/*
* std::byte
* C++17引入了std::byte类型，用于表示字节。
* 主要用于处理原始字节数据，如文件I/O、网络I/O等。
* 不需要再使用char或unsigned char来表示字节。
*/

int main()
{
    std::byte b1{ 0b0000'0101 };
    std::byte b2{ 0b0000'1010 };

    std::byte b3 = b1 | b2;
    std::byte b4 = b1 & b2;

    std::cout << "b1 = " << std::to_integer<int>(b1) << '\n';
    std::cout << "b2 = " << std::to_integer<int>(b2) << '\n';
    std::cout << "b3 = " << std::to_integer<int>(b3) << '\n';
    std::cout << "b4 = " << std::to_integer<int>(b4) << '\n';

    // 取值范围
    std::cout << "std::byte min: " << std::to_integer<int>(std::byte{ 0 }) << '\n';     // 最小值 0
    std::cout << "std::byte max: " << std::to_integer<int>(std::byte{ 255 }) << '\n';   // 最大值 255


    return 0;
}