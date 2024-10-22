#include <iostream>
#include <string>


std::string global = "I am global";
int age = 32;

std::string& getRef()
{
    return global;
}

const std::string &getConstRef()
{
    return global;
}

int *getAge()
{
    return &age;
}

int main()
{
    // 类型自动推断
    // 推断时必须给定初始值，编译器才可以根据已有的信息推断出来
    auto d{ 3.14 };         // double
    auto i{ 32 };           // int
    auto x{ i };            // int


    // 类型自动推断和const、引用、指针
    
    // 顶层const会丢失
    // 底层const不会丢失
    const double a{ 3.14 };     // const double
    auto aa{ a };               // double,因为const丢失了
    const auto caa{ a };        // const double，可以手动添加上const

    // 引用会丢失
    // 和const类似，如果需要的话，要手动添加上
    auto str{ getRef() };       // std::string
    auto &strRef{ getRef() };   // std::string&

    // const &结合在一起的时候，会先丢失&，然后再丢失顶层const
    // 具体步骤：当丢失&时，原本的底层const变成了顶层const，所以顶层const也丢失了
    auto str2{ getConstRef() };                 // std::string
    auto &strConstRef{ getConstRef() };         // const std::string &，原因：先丢失&，然后手动补上&，所以仍然为底层const
    const auto &str2ConstRef{ getConstRef() };  // const std::string &, 原因：同上

    // 最佳实践
    // 如果想保留const，最好一直都手动带上，这样意图明显
    const auto &str3ConstRef{ getConstRef() }; 

    // 指针不会丢失
    auto agePtr{ getAge() };        // int *
    auto *agePtr2{ getAge() };      // int *


    // 类型自动推断与字符串字面量
    // 这种情况下，最好不要使用auto
    auto s{ "Hello World" };        // const char*

    using namespace std::string_literals;
    using namespace std::string_view_literals;
    auto s1{ "Hello"s };            // std::string
    auto s2{ "World"sv };           // std::string_view     C++ 17的用法




    return 0;
}


// 有关概念
// 顶层const、底层const
// const int * const p;
// 顶层const：指的是变量自身不可变（右边的const）
// 底层const：指的是变量所指向的对象不可变（左边的const）
// 
// 引用是底层const
// const int& p;