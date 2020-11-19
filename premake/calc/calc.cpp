#include "calc.exp.hpp"

#include <string>

int add(int x, int y)
{
  return x + y;
}

int sub(int x, int y)
{
  return x - y;
}

void ref1(int *ret) {
    *ret = 1234;
}

const char* ret_str() {
  return "helloハロー";
}

const char *hello(const char *name) {
  std::string msg = "こんにちは ";
  msg += name;
  return msg.c_str();
}
