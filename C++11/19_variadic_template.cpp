#include <iostream>
#include <ostream>

using std::ostream;

/*
* 可变参数模板
* 实现函数可变参数的另一种方式，其他方式见：18_initializer_list.cpp
*/

// Args：表示模板参数包，表示0个或多个模板参数
// args：表示函数参数包，表示0个或多个函数参数
template <typename T, typename...Args>
void foo(const T &t, const Args&...args) {
    std::cout << sizeof...(Args) << std::endl;  // 类型参数包的大小
    std::cout << sizeof...(args) << std::endl;  // 函数参数包的大小
}

// 示例
template <typename T>
ostream &print(ostream &os, const T &t) {
    return os << t;
}

template <typename T, typename...Args>
ostream &print(ostream &os, const T &t, const Args&...args) {
    os << t << ", ";
    return print(os, args...);
}

// 包扩展 示例
// 即模式后面加上...
template <typename T> std::string debug_rep(const T &t) {
    std::ostringstream ret;
    ret << t;
    return ret.str();
}

template <typename... Args>
std::ostream &errorMsg(std::ostream &os, const Args&... rest) {
    return print(os, debug_rep(rest)...);       // 包扩展，将rest中的每个元素都传递给debug_rep
}



int main() {
    int i = 0; double d = 3.14; std::string s = "how now brown cow";
    foo(i, s, 42, d);   // 包中有3个参数
    foo(s, 42, d);      // 包中有2个参数
    foo(d, s);          // 包中有1个参数
    foo("hi");          // 包中有0个参数

    /*****************************************************************/

    print(std::cout, i, s, 42, d) << std::endl;

    return 0;
}