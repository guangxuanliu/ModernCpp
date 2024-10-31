#include <iostream>

/*
* 数字分隔符
* C++14引入了数字分隔符，允许在数字中使用单引号来增加可读性。
* 例如，可以将1000000写为1'000'000。
*/

int main() {
    int million = 1'000'000;        // 1 million
    double pi = 3.141'592'653;      // Value of pi

    long decval = 1'048'576;                    // 十进制
    long hexval = 0x10'0000;                    // 十六进制
    long octval = 00'04'00'00'00;               // 八进制
    long binval = 0b100'000000'000000'000000;   // 二进制

    //int invalid = '1000'; // 错误：不能在开头使用分隔符
    //double invalid2 = 1.'000'; // 错误：小数点后不能有分隔符

    std::cout << "million: " << million << std::endl;
    std::cout << "pi: " << pi << std::endl;
    std::cout << "decval: " << decval << std::endl;
    std::cout << "hexval: " << hexval << std::endl;
    std::cout << "octval: " << octval << std::endl;
    std::cout << "binval: " << binval << std::endl;

    return 0;
}