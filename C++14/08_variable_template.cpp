#include <iostream>
#include <type_traits>

template<typename T>
constexpr T pi = T(3.14159265358979323846);

int main() {
    std::cout << "pi as double: " << pi<double> << " (size: " << sizeof(pi<double>) << " bytes)" << std::endl;  // 输出3.14159 (size: 8 bytes)
    std::cout << "pi as float: " << pi<float> << " (size: " << sizeof(pi<float>) << " bytes)" << std::endl;     // 输出3.14159 (size: 4 bytes)
    std::cout << "pi as long double: " << pi<long double> << " (size: " << sizeof(pi<long double>) << " bytes)" << std::endl;  // 输出3.14159 (size: 8 bytes)

    // 使用 std::is_integral 来展示类型特性
    std::cout << std::boolalpha;
    std::cout << "Is pi<double> integral? " << std::is_integral<decltype(pi<double>)>::value << std::endl;  // 输出 false

    return 0;
}
