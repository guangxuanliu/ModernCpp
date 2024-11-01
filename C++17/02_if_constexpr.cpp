#include <iostream>
#include <type_traits>

/*
* 编译时条件语句
* 在C++17中，引入了if constexpr语句，它是一种编译时条件语句，可以根据编译时的条件来选择不同的代码分支。
* if constexpr语句的语法与if语句类似，但是条件表达式必须是一个常量表达式，且在编译时求值。
* if constexpr语句的主要用途是在模板元编程中，可以根据模板参数的类型或值来选择不同的代码分支。
*/

template <typename T>
void print_type_info(const T &t) {
    if constexpr (std::is_integral<T>::value) {
        std::cout << "Integral type\n";
    }
    else if constexpr (std::is_floating_point<T>::value) {
        std::cout << "Floating point type\n";
    }
    else if constexpr (std::is_pointer<T>::value) {
        std::cout << "Pointer type\n";
    }
    else if constexpr (std::is_null_pointer<T>::value) {
        std::cout << "Null pointer type\n";
    }
    else if constexpr (std::is_array<T>::value && std::is_same_v<std::remove_extent_t<T>, char>) {
        std::cout << "String literal type\n";
    }
    else {
        std::cout << "Unknown type\n";
    }
}

int main() {
    print_type_info(5);
    print_type_info(5.0);
    print_type_info("Hello");
    print_type_info(nullptr);

    return 0;
}