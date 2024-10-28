#include <iostream>

/*
* 限定作用域的枚举类型
*/

// 定义
// 比不限定作用域的枚举类型多一个class或者struct关键字
enum class Color
{
    red,
    green,
    blue
};

// 作用域
// 不限定作用域：枚举成员的作用域和枚举类型的作用域相同
// 限定作用域：枚举类型的枚举值只能通过作用域运算符::来访问
enum color {
    red,        // 枚举值(red、green、blue)的作用域和枚举类型(color)的作用域相同
    green,
    blue
};

//enum spotlight {
//    red,        // 错误：枚举成员重复定义
//    green,
//    blue
//};

enum class peppers {
    red,        // 正确，枚举成员被隐藏了
    green,
    blue
};

color hair = green;             // 正确
color hair2 = color::green;     // 正确
peppers p = peppers::green;     // 正确


// 隐式转换
// 限定作用域的枚举类型的枚举值不会被隐式转换为整数
int i = color::red;             // 正确
//int j = peppers::blue;          // 错误，枚举值不会被隐式转换为整数



int main()
{

}