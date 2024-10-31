#include <iostream>
#include <thread>
using namespace std;

void do_something(std::string &str) {
    str = "world";
}

int main() {
    std::string str = "hello";
    thread t(do_something, std::ref(str));
    t.join();
    std::cout << str << endl;
    return 0;
}



