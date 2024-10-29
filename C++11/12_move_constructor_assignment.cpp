#include <iostream>
#include <utility>

/*
* 移动构造、移动赋值
* 对应《C++ Primer》第五版的第13章 拷贝控制
* 包括5种特殊的成员函数：
*   1、拷贝构造函数
*   2、移动构造函数
*   3、拷贝赋值运算符
*   4、移动赋值运算符
*   5、析构函数
* 
* 记住：移动操作只是优化操作，如果没有移动构造、赋值，那么会使用拷贝构造、赋值来代替，但是不会影响程序的正确性。
*/

// 1、拷贝构造函数
// 定义：构造函数的第一个参数为自身类类型的引用，且任何额外参数均有默认值
// 合成：如果我们没有定义自己的拷贝构造函数，编译器会为我们自动合成一个（即使我们定义了其他构造函数，编译器也会为我们合成一个拷贝构造函数。）
// 备注：默认构造函数，如果类不包含任何构造函数，编译器会为它合成一个默认构造函数，如果类包含了某些构造函数，编译器将不会为它合成一个默认构造函数。
//      （编译器认为，如果你想在某些情况下控制其初始化，那么应该在所有情况下都需要控制）
// 合成的拷贝构造函数的作用：
//      将其参数的（非static）成员逐个拷贝到正在创建的对象中
//      类类型：使用其拷贝构造函数来拷贝成员
//      内置类型：直接拷贝
//      数组：逐个拷贝，如果数组成员是类类型，则递归调用其拷贝构造函数
// 什么时候需要自己定义拷贝构造函数？
// 简单的判断规则，看类是否需要自己定义析构函数，如果需要，那么很可能需要自己定义拷贝构造函数
class Foo {
public:
    class Foo();                // 默认构造函数       
    class Foo(const Foo &);     // 拷贝构造函数
};
// 什么时候调用？
// 1、拷贝初始化
//      拷贝初始化与直接初始化的区别：
//      拷贝初始化：要求编译器将右侧运算对象拷贝到正在创建的对象中
//      直接初始化：要求编译器使用普通的函数匹配来选择与实参匹配的构造函数
// 2、传递非引用类型的参数
// 3、返回非引用类型的参数
// 4、用花括号列表初始化一个数组中的元素或一个聚合类中的成员
// 5、初始化标准库容器或调用标准库容器的insert或push成员
std::string dots(10, '.');                  // 直接初始化
std::string s(dots);                        // 拷贝初始化
std::string s2 = dots;                      // 拷贝初始化
std::string null_book = "9-999-99999-9";    // 拷贝初始化
std::string nines = "999999999";            // 拷贝初始化

// 2、拷贝赋值运算符
// 定义：赋值运算符的左侧运算对象绑定到隐式的this参数，右侧运算对象作为显式参数传递
// 合成：如果我们没有定义自己的拷贝赋值运算符，编译器会为我们自动合成一个
// 作用：将右侧运算对象的每个非static成员赋予左侧运算对象的对应成员
// 什么时候需要自己定义拷贝赋值运算符？
// 简单的判断规则，看类是否需要自己定义析构函数，如果需要，那么很可能需要自己定义拷贝赋值运算符
class Foo2 {
public:
    class Foo2();                        // 默认构造函数       
    class Foo2(const Foo2 &);             // 拷贝构造函数
    class Foo2 &operator=(const Foo2 &);  // 拷贝赋值运算符
};

// 3、析构函数
// 定义：析构函数没有参数，没有返回值，析构函数名字由波浪号接类名构成
// 合成：如果我们没有定义自己的析构函数，编译器会为我们自动合成一个
// 作用：释放对象使用的资源
// 


// std::move
// 作用：将一个左值强制转换为一个右值引用
// 用途：在需要右值引用的地方，将一个左值传递给它
// 用法：std::move(expr)
// 当使用了上述move之后，我们可以销毁expr，或者给他赋予新的值，但是不能再使用expr的值。


// 4、移动构造函数
// 定义：移动构造函数通常是将资源从给定对象“移动”（或者成为“窃取”）到正在创建的对象中，而不是拷贝资源
// 除了移动资源，移动构造函数还要确保被移动的对象处于一种状态，使得其析构函数不会释放这些资源
// 合成：只有当一个类没有定义任何自己版本的拷贝控制成员时，编译器才会为它合成移动构造函数和移动赋值运算符

// 示例：StrVec类
//StrVec::StrVec(StrVec &&s) noexcept
//    : elements(s.elements), first_free(s.first_free), cap(s.cap)
//{
//    s.elements = s.first_free = s.cap = nullptr;
//}


// 5、移动赋值运算符
// 定义：移动赋值运算符通常是将资源从右侧运算对象“移动”（或者成为“窃取”）到左侧运算对象中，而不是拷贝资源
// 除了移动资源，移动赋值运算符还要确保被移动的对象处于一种状态，使得其析构函数不会释放这些资源
// 合成：只有当一个类没有定义任何自己版本的拷贝控制成员时，编译器才会为它合成移动构造函数和移动赋值运算符
// 函数匹配：如果一个类没有定义自己版本的移动操作，但是定义了拷贝操作，那么编译器将使用拷贝操作来代替移动操作
//          即使使用了std::move，编译器也会调用拷贝操作
// 
// 示例：StrVec类
//StrVec &StrVec::operator=(StrVec &&rhs) noexcept
//{
//    if (this != &rhs) {
//        free();
//        elements = rhs.elements;
//        first_free = rhs.first_free;
//        cap = rhs.cap;
// 
//        //将rhs置于可析构状态
//        rhs.elements = rhs.first_free = rhs.cap = nullptr;
//    }
//    return *this;
//}

// 三五法则
// 所有的五个拷贝控制成员，应该看成一个整体，如果需要定义一个，那么通常需要定义全部五个

// 完整的例子
class Example {
public:
    // 默认构造函数
    Example() : data(new int(0)) {
        std::cout << "Default constructor called" << std::endl;
    }

    // 拷贝构造函数
    Example(const Example& other) : data(new int(*other.data)) {
        std::cout << "Copy constructor called" << std::endl;
    }

    // 拷贝赋值运算符
    Example& operator=(const Example& other) {
        if (this == &other) return *this; // 防止自我赋值
        delete data; // 释放旧资源
        data = new int(*other.data); // 分配新资源并拷贝值
        std::cout << "Copy assignment operator called" << std::endl;
        return *this;
    }

    // 移动构造函数
    Example(Example&& other) noexcept : data(other.data) {
        other.data = nullptr; // 将源对象置于可析构状态
        std::cout << "Move constructor called" << std::endl;
    }

    // 移动赋值运算符
    Example& operator=(Example&& other) noexcept {
        if (this == &other) return *this; // 防止自我赋值
        delete data; // 释放旧资源
        data = other.data; // 窃取资源
        other.data = nullptr; // 将源对象置于可析构状态
        std::cout << "Move assignment operator called" << std::endl;
        return *this;
    }

    // 析构函数
    ~Example() {
        delete data;
        std::cout << "Destructor called" << std::endl;
    }

private:
    int* data;
};

int main() {
    Example ex1;                    // 调用默认构造函数
    Example ex2 = ex1;              // 调用拷贝构造函数
    Example ex3; 
    ex3 = ex1;                      // 调用拷贝赋值运算符
    Example ex4 = std::move(ex1);   // 调用移动构造函数
    Example ex5;
    ex5 = std::move(ex2);           // 调用移动赋值运算符

    return 0;
}
