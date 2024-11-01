// inline_variables.h
#ifndef INLINE_VARIABLES_H
#define INLINE_VARIABLES_H

inline int global_value = 42;  // 定义一个 inline 变量

// 如果不加 inline 关键字，会报错：
// int global_value = 42; 
// error LNK2005 : "int global_value" (? global_value@@3HA) 已经在 04_inline_variable.cpp.obj 中定义

// 报错原因：
// #ifndef 只能确保再同一个编译单元（cpp文件）中，头文件的内容只会被处理一次。
// 但是，如果头文件被包含到多个编译单元中，那么每个编译单元都会生成一个 global_value 的实例。
// 在C++17之前，一般使用extern关键字来声明变量，定义变量时在一个编译单元中定义，其他编译单元中使用extern关键字声明。

#endif // INLINE_VARIABLES_H
