#include "strconv2.h"
#include <iostream>

using strconv2::format;
using strconv2::formatA;
using strconv2::printA;

static inline std::wstring utf8t_to_wide(const std::u8string &s)
{
  int in_length = (int)s.length();
  int out_length = MultiByteToWideChar(CP_UTF8, 0, (const char *)s.c_str(), in_length, 0, 0);
  std::wstring result(out_length, L'\0');
  if (out_length)
    MultiByteToWideChar(CP_UTF8, 0, (const char *)s.c_str(), in_length, &result[0], out_length);
  return result;
}

static inline std::u8string wide_to_utf8t(const std::wstring &s)
{
  int in_length = (int)s.length();
  int out_length = WideCharToMultiByte(CP_UTF8, 0, s.c_str(), in_length, 0, 0, 0, 0);
  std::u8string result(out_length, '\0');
  if (out_length)
    WideCharToMultiByte(CP_UTF8, 0, s.c_str(), in_length, (char *)&result[0], out_length, 0, 0);
  return result;
}

int main()
{
  char8_t c = 0;
  using namespace std::literals::chrono_literals;
  std::cout << format("Default format: {} {}", 42s, 100ms) << std::endl;
  std::cout << format("strftime-like format: {:%H:%M:%S}", 3h + 15min + 30s) << std::endl;
  std::wstring hello = L"ハロー";
  std::cout << formatA(L"this is(これは) {}", hello) << std::endl;
  printA(L"this is(これは) {}\n", hello);
  std::string goodby = "グッバイ";
  std::cout << formatA("that is(あれは) {}", goodby) << std::endl;
  printA("that is(あれは) {}\n", goodby);
  return 0;
}