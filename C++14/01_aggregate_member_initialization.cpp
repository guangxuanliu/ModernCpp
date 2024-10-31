#include <iostream>
#include <string>

/*
* 聚合体成员初始化
*/

// 当一个类满足以下条件时，它被称为聚合体：
// 1. 所有成员都是 public
// 2. 没有用户提供的构造函数
// 3. 没有基类，没有虚函数
// 4. 没有类内初始值

struct Student {
    int id;
    std::string name;
    int age;
};

int main() {
    Student s1 = { 1, "Alice", 20 }; // 正确的聚合初始化
    Student s2 = { 2 };              // id = 2, name 和 age 将按值初始化

    std::cout << "Student 1: " << s1.id << ", " << s1.name << ", " << s1.age << std::endl;      // Student 1: 1, Alice, 20
    std::cout << "Student 2: " << s2.id << ", " << s2.name << ", " << s2.age << std::endl;      // Student 2: 2, , 0

    return 0;
}