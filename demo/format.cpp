#include "strconv2.h"
#include <iostream>

using strconv::format;
using strconv::formatA;
using strconv::printA;
using strconv::utf8;

int main()
{
  std::string s = utf8(u8"abc");
  using namespace std::literals::chrono_literals;
  std::cout << format(utf8(u8"Default format: {} {}"), 42s, 100ms) << std::endl;
  std::cout << format("strftime-like format: {:%H:%M:%S}", 3h + 15min + 30s) << std::endl;
  std::wstring hello = L"ハロー";
  std::cout << formatA(L"this is(これは) {}", hello) << std::endl;
  printA(L"this is(これは) {}\n", hello);
  std::string goodby = "グッバイ";
  std::cout << formatA("that is(あれは) {}", goodby) << std::endl;
  printA("that is(あれは) {}\n", goodby);
  return 0;
}