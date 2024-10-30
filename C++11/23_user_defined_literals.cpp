#include <iostream>

/*
* 用户自定义字面量
* 语法：return_type operator "" _user_defined_literal_name (parameter)
* 用户定义字面量通常用于需要特定单位的量，如时间、长度、温度等，或者在需要提高代码可读性的场景中。
*/


long double operator"" _km(long double x) {
    return x * 1000.0; // 将公里转换为米
}

int operator"" _times(unsigned long long x) {
    return x * 2; // 将字面量乘以 2
}

std::string operator"" _s(const char *str, size_t sz) {
    return std::string(str); // 返回 std::string
}

int main()
{
    long double distance = 5.0_km; // 使用自定义字面量
    std::cout << distance << " meters" << std::endl; // 输出：5000 meters

    int result = 3_times; // result = 6
    std::cout << result << std::endl;

    std::string myString = "Hello"_s; // 使用自定义字面量
    std::cout << myString << std::endl; // 输出：Hello


    return 0;
}