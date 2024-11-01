#include <iostream>
#include <string>
#include <string_view>

using namespace std::string_view_literals;

/*
* std::string_view 是一个轻量级的字符串视图，它不拥有字符串的所有权，只是对字符串的引用。
*/

// 特点
// 1. 不拥有字符串的所有权，只是对字符串的引用
// 2. 适用于只读字符串，不适用于修改字符串
// 3. 可以直接使用 C 风格字符串,std::string 对象
// 4. 支持常见的字符串操作，如查找、子串、分割等


// 作为参数时，可以接受 std::string 对象、C 风格字符串、字符数组等
// 而且没有必要添加 const 修饰符，因为 string_view 不会修改字符串
void printStringView(std::string_view sv) {
    std::cout << sv << std::endl;
}

int main() {
    std::string str = "Hello, World!";
    std::string_view sv = str; // 从 std::string 创建 string_view

    printStringView(str);   // 输出: Hello, World!
    printStringView(sv);    // 输出: Hello, World!

    // 使用 C 风格字符串
    printStringView("Hello, C-style string!"); // 直接使用字面量


    // sv后缀的使用方式
    // 两种方式都可以创建std::string_view对象，效果一样，但是使用sv后缀更加简洁，但是需要使用using namespace std::string_view_literals;导入命名空间
    std::string_view name = "Liu Guangxuan";    // const char[]被隐式转换为std::string_view，这种转换是合法的，但是经过隐式的构造过程
    std::string_view name2 = "Liu Guangxuan"sv; // 使用sv后缀，直接创建std::string_view对象，更简介且易于阅读

    return 0;
}


// Q：作为函数参数时，哪个更好一些？const string& 和 string_view
// A：const string&，引用传递，不会复制字符串，但是传递给它的参数必须是 string 类型，不能是 C 风格字符串，所以使用时有一定的局限性。
//   string_view，更加通用，可以接受 string 对象、C 风格字符串、字符数组等，但是需要注意的是，string_view 不拥有字符串的所有权，所以在使用时需要注意字符串的生命周期。
// 


// const 的必要性？