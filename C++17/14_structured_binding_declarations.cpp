#include <iostream>
#include <tuple>

int main() {

    // 元组
    std::tuple<int, double, std::string> myTuple(1, 3.14, "Hello");
    auto [a, b, c] = myTuple;
    std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;

    // 数组
    int arr[] = { 1, 2, 3, 4, 5 };
    auto [x, y, z, w, v] = arr;
    std::cout << "x: " << x << ", y: " << y << ", z: " << z << ", w: " << w << ", v: " << v << std::endl;

    // 结构体
    struct MyStruct {
        int x;
        double y;
        std::string z;
    };
    MyStruct myStruct{ 1, 3.14, "Hello" };
    auto [m, n, o] = myStruct;
    std::cout << "m: " << m << ", n: " << n << ", o: " << o << std::endl;

    // 注意
    // 默认情况下，结构化绑定是通过值进行的，因此如果要修改原始对象的值，需要使用引用
    auto &[p, q, r] = myStruct;
    p = 10;
    std::cout << "myStruct.x: " << myStruct.x << std::endl;

    // 忽略某些元素
    // 使用占位符 _ 忽略不需要的元素
    // 使用_只是一种惯例，实际上，可以使用任何合法的标识符，但使用下划线通常被视为更清晰的意图表达
    auto [s, _, t] = myStruct;
    std::cout << "s: " << s << ", t: " << t << std::endl;

    return 0;
}
