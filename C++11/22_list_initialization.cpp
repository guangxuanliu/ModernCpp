#include <iostream>
#include <vector>
#include <string>

/*
* 列表初始化
* C++11 中引入的 Uniform Initialization（统一初始化）是指使用一种统一的语法来初始化对象，不论是基本数据类型、用户定义类型、数组、容器等。
* 它通过使用花括号 {} 来进行初始化，旨在提供更一致和安全的初始化方式。
*/

class Point {
public:
    int x, y;
    Point(int x, int y) : x{ x }, y{ y } {}
};

int main() {
    // 基本数据类型初始化
    int a{ 10 };
    double b{ 3.14 };
    //double d{ a }; // error, 不能窄化转换

    // 字符串初始化
    std::string str{ "Hello, World!" };

    // 类的初始化
    Point p{ 1, 2 };

    // 容器初始化
    std::vector<int> vec{ 1, 2, 3, 4, 5 };
    int arr[]{ 1, 2, 3, 4, 5 };


    return 0;
}
