#include <iostream>

/*
* noexcept
* 1、要么出现在该函数所有的声明语句和定义语句中，要么都不出现
* 2、编译器并不会检查noexcept说明。如果一个函数被声明为noexcept，但是在函数体内抛出了异常，编译器也可以顺便编译通过
* 3、之前的方法是在同样的位置添加throw()，但是这个方法已经被弃用了
* 4、noexcept说明符可以接受一个可选的实参，表示该函数是否可能会抛出异常
*    noexcept(true)表示该函数不会抛出异常
*    noexcept(false)表示该函数可能会抛出异常
* 
*/

void foo() noexcept(false)
{
    throw 1;
}

int main()
{
    foo();
    return 0;
}