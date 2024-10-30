#include <iostream>
#include <string>

/*
* 字符串字面量
* C++11 新增了几种字符串字面量
* 备注：代码中尽量避免使用中文。
*/

int main() {
    // 普通字符串字面量
    const char *normalStr = "Hello, World!";
    std::cout << normalStr << std::endl;

    // 宽字符串字面量
    const wchar_t *wideStr = L"Hello, Wide World!";
    std::wcout << wideStr << std::endl; // 使用 wcout 输出

    // 原始字符串字面量
    const char *rawStr = R"(This is a raw string: \n No escape needed)";
    std::cout << rawStr << std::endl;

    // UTF-8 字符串字面量
    const char8_t *utf8Str = u8"Hello, UTF-8 World!";
    std::cout << reinterpret_cast<const char*>(utf8Str) << std::endl;

    // UTF-16 字符串字面量
    const char16_t *utf16Str = u"Hello, UTF-16 World!";
    // 注意：输出 UTF-16 字符串需要转换
    std::wcout << reinterpret_cast<const wchar_t *>(utf16Str) << std::endl;

    // UTF-32 字符串字面量
    const char32_t *utf32Str = U"Hello, UTF-32 World!";
    // 注意：输出 UTF-32 字符串需要转换
    std::wcout << reinterpret_cast<const wchar_t *>(utf32Str) << std::endl;

    return 0;
}
