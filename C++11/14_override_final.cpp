#include <iostream>

/*
* override:
* 派生类中的虚函数覆盖基类中的虚函数时，可以使用override关键字，这样可以让编译器帮助检查是否真的覆盖成功。
* 
* final:
* final关键字可以用于类、虚函数和成员函数，表示该类不能被继承，虚函数不能被覆盖，成员函数不能被重载。
*/

class Base
{
public:
    virtual void func() const
    {
        std::cout << "Base::func()" << std::endl;
    }

    virtual void func(int) const final
    {
        std::cout << "Base::func(int)" << std::endl;
    }
};

class Derived : public Base
{
public:
    void func() const override
    {
        std::cout << "Derived::func()" << std::endl;
    }

    // void func(int) const // error: cannot override final function
};


int main()
{
    Derived d;
    Base *pb = &d;
    pb->func();


    return 0;
}