#include <iostream>
#include <memory>
#include <string>

/*
* std::make_unique 是 C++14 新增的函数，用于创建一个 unique_ptr 对象
* 与 std::make_shared 类似，std::make_unique 也是一个模板函数，可以自动推导类型
*/

struct MyStruct {
    MyStruct(int x) : value(x) {}
    int value;
};

int main() {
    auto ptr = std::make_unique<MyStruct>(42); // 创建一个 MyStruct 的 unique_ptr

    std::cout << "Value: " << ptr->value << std::endl; // 输出: Value: 42

    // 不需要手动 delete，ptr 超出作用域后会自动释放内存

    return 0;
}
