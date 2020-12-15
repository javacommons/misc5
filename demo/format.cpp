#include "strconv2.h"
#include <iostream>

using strconv2::format;
using strconv2::formatA;
using strconv2::printA;

int main()
{
  using namespace std::literals::chrono_literals;
  std::cout << format(u8"Default format: {} {}", 42s, 100ms) << std::endl;
  std::cout << format(u8"strftime-like format: {:%H:%M:%S}", 3h + 15min + 30s) << std::endl;
  std::wstring hello = L"ハロー";
  std::cout << formatA(L"this is(これは) {}", hello) << std::endl;
  printA(L"this is(これは) {}\n", hello);
  std::string goodby = u8"グッバイ";
  std::cout << formatA(u8"that is(あれは) {}", goodby) << std::endl;
  printA(u8"that is(あれは) {}\n", goodby);
  return 0;
}