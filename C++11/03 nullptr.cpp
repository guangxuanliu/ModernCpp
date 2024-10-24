#include <iostream>

void foo(int x)
{
	std::cout << "foo(int x)" << std::endl;
}

void foo(char *x)
{
	std::cout << "foo(char* x)" << std::endl;
}

int main() 
{
	NULL;					// 可以点进去看一下NULL的定义，在C中，被定义成了空指针(void *)0
	int *p = NULL;			// 在C中，这句话为int *p = (void*)0;
	// int *p = (void *)0;	// 这句话在C中是合法的，但是在C++中是不合法的，因为C++是强类型语言
	int *p1 = 0;			// 这句话在C++中是合法的，因为0是一个整数，可以隐式转换为指针类型，所以C++中NULL的定义为0
	
	// 但是这样的定义会引起一些问题，比如下面的函数调用
	foo(NULL);		// Ambiguous call, will call foo(int x)

	// 所以C++11中引入了nullptr，nullptr是一个空指针常量，可以隐式转换为任意指针类型
	// 这样可以解决上面的二义性的问题
	foo(nullptr);	// Calls foo(char* x)

	return 0;
}

// 总结
// 在Modern cpp中，nullptr是一个新的关键字，用来代替NULL，它是一个空指针常量，
// 可以隐式转换为任意指针类型。但是不能隐式转换为整数类型。
// 尽量使用nullptr代替NULL，因为nullptr的类型安全性更好。