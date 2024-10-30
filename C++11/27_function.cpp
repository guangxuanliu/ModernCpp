#include <iostream>
#include <functional>
#include <map>

/*
* function
* C++中有几种可调用对象：函数、函数指针、lambda表达式、bind创建的对象、以及重载了函数调用运算符的类对象
* 每种可调用对象都有自己的类型。
* 但是只要调用形式相同，function对象就可以包装任何可调用对象
* 
*/

// 普通函数
int add(int a, int b)
{
    return a + b;
}

// 函数指针
using pf = int (*)(int, int);
pf pf_add = add;

// lambda表达式
auto mod = [](int a, int b) -> int { return a % b; };

// std::bind创建的对象
auto myAdd = std::bind(add, std::placeholders::_1, std::placeholders::_2);

// 重载了函数调用运算符的类对象
class divide
{
public:
    int operator()(int a, int b)
    {
        return a / b;
    }
};


std::map<std::string, std::function<int(int, int)>> binops = {
    {"+", add},                                 // 普通函数
    {"++", pf_add},                             // 函数指针
    {"*", [](int a, int b) { return a * b; }},  // lambda表达式
    {"%", mod},                               // lambda表达式
    {"+++", myAdd},                             // bind创建的对象
    {"/", divide()},                            // 重载了函数调用运算符的类对象
    {"-", std::minus<int>()}                   // 标准库函数对象  
};

int main()
{
    std::cout << binops["+"](10, 5) << std::endl;
    std::cout << binops["++"](10, 5) << std::endl;
    std::cout << binops["*"](10, 5) << std::endl;
    std::cout << binops["%"](10, 5) << std::endl;
    std::cout << binops["+++"](10, 5) << std::endl;
    std::cout << binops["/"](10, 5) << std::endl;
    std::cout << binops["-"](10, 5) << std::endl;


    return 0;
}