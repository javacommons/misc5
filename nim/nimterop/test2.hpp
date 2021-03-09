#include <stdint.h>
#include <iostream>

#define TEST_INT 512
#define TEST_FLOAT 5.12
#define TEST_HEX 0x512

extern "C" {
  int test_call_int();

  struct Foo{
    int bar;
  };
}

class Foo1{
  int bar1;
  void hello()
  {
    std::cout << "hello " << this->bar1 << std::endl;
  }
};

template<typename T>
struct Foo2{
  int bar2;
};

typedef Foo2<int> Foo2_int;


