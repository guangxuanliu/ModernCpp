#include <iostream>
using namespace std;

/*
* 二进制字面量
* 二进制字面量是C++14的新特性，可以使用0b或0B前缀来表示二进制数。
*/

int main()
{
    // Binary literals
    int a = 0b1010;                     // 10
    int b = 0b1111;                     // 15
    int c = 0b1010'1111;                // 175 分隔符功能，方便阅读
    int d = 0b1010'1111'1010'1111;      // 44975
    //int e = 0b'1010'1111;             // error: 分隔符不能放在前缀之后

    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << d << endl;

    return 0;
}