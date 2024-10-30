#include <iostream>  
#include <cstdlib>  
#include <locale>  
#include <codecvt>  
#include <string>  

/*
* utf-8和宽字符之间的转换
* 注意：
* 1、仅仅是utf-8和宽字符之间的转换，不支持code page，如果需要支持code page，需要使用Windows API
* 2、C++11引入了std::codecvt，但是C++17已经废弃了。
* 3、关于字符编码的转换，最好使用第三方库，如ICU，Boost.Local等。
*/


void utf8ToWide(const char *utf8, wchar_t *wide, size_t wideSize) {  
   mbstowcs(wide, utf8, wideSize);  
}  

void wideToUtf8(const wchar_t *wide, char *utf8, size_t utf8Size) {  
   wcstombs(utf8, wide, utf8Size);  
}  

int main() {  
   const char8_t *utf8Str = u8"Hello, Unicode World!";  
   std::string utf8StrConverted(reinterpret_cast<const char*>(utf8Str));  

   // 计算所需宽字符数组的大小  
   size_t wideSize = mbstowcs(nullptr, utf8StrConverted.c_str(), 0) + 1; // +1 for null terminator  
   wchar_t *wideStr = new wchar_t[wideSize];  

   utf8ToWide(utf8StrConverted.c_str(), wideStr, wideSize);  
   std::wcout << L"Wide String: " << wideStr << std::endl;  

   // 转换回 UTF-8  
   size_t utf8Size = wcstombs(nullptr, wideStr, 0) + 1;  
   char *newUtf8Str = new char[utf8Size];  

   wideToUtf8(wideStr, newUtf8Str, utf8Size);  
   std::cout << "UTF-8 String: " << newUtf8Str << std::endl;  

   delete[] wideStr;  
   delete[] newUtf8Str;  
   return 0;  
}
