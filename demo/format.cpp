#include "format.h"
#include <iostream>

int main()
{
  fmt::print("Hello, {}!\n", "world");  // uses Python-like format string syntax
  fmt::printf("Hello, %s!\n", "world"); // uses printf format string syntax
  std::string s = fmt::format("{0}{1}{0}", "abra", "cad");
  std::cout << s << std::endl;
  return 0;
}