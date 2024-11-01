#include <iostream>
#include <new>

struct A {
    int value;
};

struct B {
    int value;
};

int main() {
    // 分配内存并构造A对象
    void *memory = operator new(sizeof(A));
    new(memory) A{ 42 };

    // 销毁A对象并在同一内存位置构造B对象
    static_cast<A *>(memory)->~A();
    new(memory) B{ 100 };

    // 使用std::launder来安全访问B对象
    B *bPtr = std::launder(static_cast<B *>(memory));
    std::cout << "Value: " << bPtr->value << std::endl; // 输出: Value: 100

    // 记得清理分配的内存
    bPtr->~B();
    operator delete(memory);

    return 0;
}
