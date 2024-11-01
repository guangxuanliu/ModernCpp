#include <iostream>

/*
* 嵌套命名空间简化
* 本质上是语法糖
*/

// C++17支持以下语法，直接定义嵌套命名空间
namespace Math::Geometry
{
    void draw() {
        std::cout << "Drawing Geometry" << std::endl;
    }
}

// C++17之前的写法
namespace Math
{
    namespace Geometry
    {
        void draw2() {
            std::cout << "Drawing Geometry" << std::endl;
        }
    }
}

int main()
{
    Math::Geometry::draw();

    return 0;
}