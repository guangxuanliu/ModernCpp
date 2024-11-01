// another_file.cpp
#include <iostream>
#include "04_inline_variable.h"

void change_value() {
    std::cout << "Global value from another file, before change: " << global_value << std::endl;
    global_value = 100;
    std::cout << "Global value from another file, after change: " << global_value << std::endl;
}
