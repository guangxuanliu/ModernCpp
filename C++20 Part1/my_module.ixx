// 模块接口单元：my_module.ixx
// 后缀cppm在vs2022中无法编译，所以此处使用后缀ixx

// 导入标准库
import std.core;  // 在vs2022中无法编译，所以使用下面的来代替
//#include <iostream>     

export module myModule;  // module关键字指明这是一个模块，export关键字指明这是一个模块接口单元

//这是一个只在该模块内部可见的函数，不可导出
void internal_function() 
{ 
    std::cout << "internal_function()" << std::endl;
}

//export关键字指明本模块导出函数say_hello()
export void say_hello() 
{  
    std::cout << "say_hello()" << std::endl;
    internal_function();

    return;
}

// 导出函数say_world, 函数在此处只提供声明
export void say_world();  

//当需要导出的C++实体太多时，不必一一指定，可以在下面的大括号中统一指定
export
{
    int var;
    void i_am_export_function() 
    { 
        std::cout << "i_am_export_function()" << std::endl;
        //other export entity
    }
}