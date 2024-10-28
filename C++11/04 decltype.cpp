#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;

    int *p = NULL;
    free(p);


    alloca(10);

    return 0;
}
