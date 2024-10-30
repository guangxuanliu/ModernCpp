#include <iostream>

// S 类型的对象可以在任何地址上分配
// 因为 S.a 和 S.b 都可以在任何地址上分配
struct S
{
    char a; // 大小：1，对齐：1
    char b; // 大小：1，对齐：1
}; // 大小：2，对齐：1

// X 类型的对象只能在 4 字节边界上分配
// 因为 X.n 必须在 4 字节边界上分配
// 因为 int 的对齐要求（通常）就是 4
struct X
{
    int n;  // 大小：4，对齐：4
    char c; // 大小：1，对齐：1
    // 三个字节的填充位
}; // 大小：8，对齐：4

struct Foo
{
    int   i;
    float f;
    char  c;
};

// 注：下面的 `alignas(alignof(long double))`
// 如果需要可以简化为 `alignas(long double)`
struct alignas(alignof(long double)) Foo2
{
    // Foo2 成员的定义...
};

struct Empty {};

struct alignas(64) Empty64 {};

int main()
{
    std::cout << "alignof(S) = " << alignof(S) << '\n'  // 输出 1
        << "sizeof(S)  = " << sizeof(S) << '\n'         // 输出 2
        << "alignof(X) = " << alignof(X) << '\n'        // 输出 4
        << "sizeof(X)  = " << sizeof(X) << '\n';        // 输出 8



    std::cout << "对齐字节数\n" << 
        "- char                ：" << alignof(char) << ", " << sizeof(char) << "\n"      // 输出 1
        "- 指针                ：" << alignof(int *) << ", " << sizeof(int *) << "\n"       // 输出 8
        "- Foo 类              ：" << alignof(Foo) << ", " << sizeof(Foo) << "\n"        // 输出 4
        "- Foo2 类             ：" << alignof(Foo2) << ", " << sizeof(Foo2) << "\n"       // 输出 16
        "- 空类                ：" << alignof(Empty) << ", " << sizeof(Empty) << "\n"       // 输出 1
        "- 带 alignas(64) 的空类：" << alignof(Empty64) << ", " << sizeof(Empty64) << "\n";     // 输出 64
}