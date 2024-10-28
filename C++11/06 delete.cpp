#include <iostream>

/*
* 场景1：delete与普通函数
*/

void printInt(int x)
{
    std::cout << x << std::endl;
}

// 上面的函数本意是输出int类型的数据，但是实际上可以接受任意类型的数据，因为C++会自动进行类型转换
// 所以我们可以使用delete关键字来禁止这种隐式类型转换
//void printInt(char) = delete;
//void printInt(bool) = delete;
// 但是这样写会报错，因为delete只能用于函数的特定重载版本，而不能用于整个函数
// 所以我们可以使用函数模板来实现这个功能
template<typename T>
void printInt(T) = delete;


int main()
{
    printInt(5);            // 输出5
    //printInt('a');          // 输出97
    //printInt(true);         // 输出1  


    return 0;
}


/*
* 场景2：delete与类的成员函数
* delete可以用于类的成员函数，用于删除某个特定版本的成员函数
*/
// 下面定义了一个类，该类的拷贝构造函数和赋值运算符被delete了
// 这样就不能再使用拷贝构造函数和赋值运算符了
// 这样的类不能被拷贝，也不能被赋值
// 可以通过继承该类来实现单例模式
struct NoCopy
{
    NoCopy() = default;
    NoCopy(const NoCopy &) = delete;
    NoCopy &operator=(const NoCopy &) = delete;
    ~NoCopy() = default;
};

