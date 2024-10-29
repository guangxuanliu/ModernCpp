#include <iostream>
#include "09_extern_template.h"


/*
* 外部模板
* 为了避免模板实例化的代码重复，可以使用extern关键字声明一个模板实例化
* 此处仅有一处实例化，在09_extern_template.cpp中
* 
* 作用：
* 仅仅是为了减少代码量，提高编译速度，无他。
* 其实，如果不适用extern关键字，也不会有什么问题，只是会导致编译时，模板实例化的代码重复。
* 随后在链接时，链接器会自动去重。
*/

int main()
{

    MyClass<int> obj;
    obj.set(10);

    return 0;
}