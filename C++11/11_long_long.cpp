#include <iostream>

/*
* C++11标准，新引入了long long类型，用于表示更大范围的整数。
*/

int main()
{
    std::cout << "Size of long: " << sizeof(long) << " bytes" << std::endl;
    std::cout << "Size of long long: " << sizeof(long long) << " bytes" << std::endl;
    return 0;
}

// Output
// 注意，Windows和Linux的差异
// +-----------+----------------+----------------+
// |           | Windows (bytes)| Linux (bytes)  |
// +-----------+----------------+----------------+
// | long      |       4        |       8        |
// +-----------+----------------+----------------+
// | long long |       8        |       8        |
// +-----------+----------------+----------------+