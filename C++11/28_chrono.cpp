#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>

/*
* chrono
* 是一个时间库，提供了一些用于时间测量的类和函数
* 常见的用法：
*  1. 计算程序运行时间
*  2. 获取当前时间
* 
*/

void someFunction() {
    // 模拟一些耗时的操作
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
    // 记录开始时间
    auto start = std::chrono::high_resolution_clock::now();

    // 执行函数
    someFunction();

    // 记录结束时间
    auto end = std::chrono::high_resolution_clock::now();

    // 计算耗时
    std::chrono::duration<double, std::milli> duration = end - start; // 毫秒

    std::cout << "Function execution time: " << duration.count() << " ms" << std::endl;

    
    /************************************************************************************************************************/

    // 获取当前时间
    auto now = std::chrono::system_clock::now();                        // 当前时间
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);      // 转换为time_t
    std::tm* now_tm = std::localtime(&now_c);                           // 转换为tm结构

    // 分别输出当前时间的年月日时分秒
    std::cout << "Current time: " 
              << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S") 
              << std::endl;

    return 0;
}
