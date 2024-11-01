#include <iostream>
#include <variant>
#include <any>

/*
* std::variant 是一种类型安全的union。它是一种可以保存其实例化时指定的类型之一的值的类型。
* std::any 是一种类型安全的容器，可以容纳任何类型的单个值。包括自定义类型。
*/


int main() {
    std::variant<int, double, std::string> v;       // variant可以容纳多种类型，但在某一时刻只能容纳其中一种
    v = 42;
    std::cout << std::get<int>(v) << std::endl;
    v = 3.14;
    std::cout << std::get<double>(v) << std::endl;
    v = "hello";
    std::cout << std::get<std::string>(v) << std::endl;

    try
    {
        std::cout << std::get<int>(v) << std::endl;     // 当variant中的类型与get的类型不匹配时，会抛出异常
    }
    catch (const std::bad_variant_access &e)
    {
        std::cerr << e.what() << '\n';
    }


    std::any a;      // any可以容纳任何类型，但在某一时刻只能容纳其中一种
    a = 42;
    std::cout << std::any_cast<int>(a) << std::endl;
    a = 3.14;
    std::cout << std::any_cast<double>(a) << std::endl;
    a = "hello";
    std::cout << std::any_cast<const char *>(a) << std::endl;

    // 常用的函数
    // a.has_value();               // 判断any是否有值
    // a.reset();                   // 重置any的值
    // a.type();                    // 获取any的类型信息
    // std::any_cast<int>(a);       // 获取any的值

    if (a.has_value())
    {
        std::cout << "a has value" << std::endl;
    }
    else
    {
        std::cout << "a has no value" << std::endl;
    }

    if (a.type() == typeid(int))
    {
        std::cout << "a is int" << std::endl;
    }
    else if (a.type() == typeid(double))
    {
        std::cout << "a is double" << std::endl;
    }
    else if (a.type() == typeid(const char *))
    {
        std::cout << "a is const char *" << std::endl;
    }
    else
    {
        std::cout << "a is unknown type" << std::endl;
    }


    try
    {
        std::cout << std::any_cast<int>(a) << std::endl;     // 当any中的类型与any_cast的类型不匹配时，会抛出异常
    }
    catch (const std::bad_any_cast &e)
    {
        std::cerr << e.what() << '\n';
    }



    return 0;
}