#include <iostream>

/*
* 委托构造函数
* 即一个构造函数可以调用另一个构造函数来初始化自己
* 语法：构造函数名(参数列表):构造函数名(参数列表){}
*/

class Student
{
public:
	Student(int id, std::string name) : id(id), name(name) {}	// 其他的构造函数都委托给这个构造函数
	Student() : Student(0, "") {}
	Student(int id) : Student(id, "") {}
	Student(std::string name) : Student(0, name) {}

private:
	int id;
	std::string name;
};
	

int main()
{
	Student s1(1, "Tom");
	Student s2;
	Student s3(2);
	Student s4("Jerry");

	return 0;
}