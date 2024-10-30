#include <iostream>
#include <vector>

/*
* 类型别名
* 有两种方式
* 1. using
* 2. typedef
* 现代C++中，更推荐使用using
*/

int main()
{
    // Type aliases
    using myInt = int;
    typedef double myDouble;

    myInt a = 5;
    myDouble b = 5.5;

    std::cout << a << std::endl;
    std::cout << b << std::endl;

    return 0;
}

// Q：using 和 typedef 的区别
// 1、using 可以定义模板别名
template <typename T>
using myVector = std::vector<T>;

// typedef 不可以定义模板别名
// typedef std::vector<T> myVector; // error
//typedef std::vector<int> myVector; // ok，typedef只能定义具体类型的别名

// 2、using更清晰，更直观
typedef std::pair<int, std::vector<std::string>> PairInt; // typedef不直观
using PairInt = std::pair<int, std::vector<std::string>>; // using更直观


// Q：typedef 和 define 的区别
// 1、typedef 是类型别名，define 是宏定义
// 2、typedef 是在编译器处理，define 是在预处理器处理
// 3、对指针的处理，typedef可以清晰地定义指针，而define可能导致混淆
typedef int *IntPtr; // IntPtr 是指向int的指针
IntPtr a, b; // a, b 都是指向int的指针

//#define IntPtr int * // IntPtr 是int的指针
//IntPtr a, b; // a 是int的指针，b 是int，不符合预期

// 4、typedef具有作用域限制，define没有作用域限制，只要宏被定义，它在整个文件中都有效，直到#undef


// 最佳实践：
// 定义类型别名使用using或者typedef，现代C++更推荐使用using
// 简单文本替换或条件编译使用define