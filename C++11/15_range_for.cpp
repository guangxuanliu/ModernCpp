#include <iostream>
#include <string>

int main()
{
    const std::string name = "Liu Guangxuan";
    for (auto c : name)
    {
        std::cout << c << std::endl;
    }
    return 0;
}