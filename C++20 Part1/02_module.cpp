// import string_view; // 在vs2022中无法编译，所以使用下面的来代替
#include <string_view>

import myModule;

/*
* 模块，是C++20新增的一个特性，用于替代传统的头文件和库文件的方式。
* 模块的引入，可以避免头文件的重复包含，提高编译速度。
* vs2022中，需要先安装组件："适用于v143 生成工具的C++模块（x64/x86）- 实验性"
* 使用vs2022 + CMake构建项目，vs2022支持的不够完善，还有很多问题，比如经常会出现"错误 C3474	无法打开输出文件“myModule.ifc"
* 最好使用vs2022在传统项目（解决方案项目）中进行测试，并且设置属性->C/C++->语言->启用实验性C++ 标准库模块，设置为（/experimental：module）
*/

int main() 
{
    say_hello();
    say_world();
    i_am_export_function();
    
    //internal_function(); //error, 此函数没有被导出，不能访问
    
    return 0;
}
