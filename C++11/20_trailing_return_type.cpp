#include <iostream>
#include <vector>
#include <algorithm>

/*
* 尾置返回类型
* 任何函数的返回类型都可以放在函数名之后，用 -> 指定
* 
*/

int main() {
    auto add = [](int a, int b) -> int {
        return a + b;
        };

    std::cout << add(1, 2) << std::endl;

    // 当我们为lambda表达式指定返回类型时，必须使用尾置返回类型
    std::vector<int> v1{ -1, 2, -3, 4, -5 };
    std::transform(v1.begin(), v1.end(), v1.begin(), 
        [](int i) -> int 
        { if (i < 0) return -i; else return i; });

    return 0;
}

