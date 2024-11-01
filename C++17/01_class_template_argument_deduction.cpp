#include <iostream>
#include <string>
#include <vector>


/*
* 类模板参数推导，简写为CTAD
* 类模板参数推导是C++17的新特性，可以让我们在实例化类模板时不用显式指定模板参数。
* 类模板参数推导的规则如下：
* 1. 类模板参数推导只适用于类模板，不适用于函数模板。
* 2. 类模板参数推导只适用于构造函数，不适用于其他成员函数。
*/

template <typename T>
class MyClass {
public:
    MyClass(const T &val) : m_val(val) {}

private:
    T m_val;
};

int main() {
    
    std::vector ivec = { 1, 2, 3, 4, 5 };       // std::vector<int>，推导出int类型
    std::vector svec = { "hello", "world" };    // std::vector<std::string>，推导出std::string类型
    std::pair p(1, 3.14);                        // std::pair<int, double>，推导出int和double类型

    MyClass myInt(123);                         // MyClass<int>，推导出int类型
    MyClass myString("hello");                  // MyClass<const char*>，推导出const char*类型



    return 0;
}