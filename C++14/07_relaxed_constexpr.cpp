#include <iostream>

constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

constexpr int sum(int a, int b) {
    int result = 0;
    for (int i = a; i <= b; ++i) {
        result += i;
    }
    return result;
}

int main() {
    
    constexpr int fact5 = factorial(5); // 在编译时计算
    constexpr int sumResult = sum(1, 5); // 在编译时计算

    std::cout << "Factorial of 5: " << fact5 << std::endl; // 输出: 120
    std::cout << "Sum from 1 to 5: " << sumResult << std::endl; // 输出: 15


    //int num;
    //std::cin >> num;
    //constexpr int fact5 = factorial(num); // 错误，无法在编译时计算

    return 0;
}
