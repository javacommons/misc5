#pragma once

#include <stdio.h>
#include <string>
#include <iostream>

class MyClass
{
  int _z = 777;
public:
  MyClass()
  {
    printf("MyClass(1)\n");
  }

  MyClass(int n)
  {
    printf("MyClass(2)\n");
    num = 7;
    nums[0] = 4;
    nums[1] = 5;
  }

  ~MyClass()
  {
    printf("~MyClass(): _z=%d\n", this->_z);
  }

  void z(int value)
  {
    this->_z = value;
  }

  int z()
  {
    return this->_z;
  }

  void say(const std::string &msg)
  {
    std::cout << "Say: " << msg << std::endl;
  }

  std::string greeting(const std::string &name)
  {
    return std::string("Hello ") + name;
  }

  double test(int x)
  {
    return (double)x;
  }

  void test3()
  {
    printf("Hello mondo\n");
  }

  void test4(int x, int y)
  {
    printf("Hello mondo %d %d\n", x, y);
  }

  int test2(int x)
  {
    return x;
  }

  int num = 77;
  int nums[2];
};

class MyClass2
{
public:
  MyClass2()
  {
    printf("MyClass2(1)\n");
  }

  MyClass2(int n)
  {
    printf("MyClass2(2)\n");
  }

  ~MyClass2()
  {
    printf("~MyClass2()\n");
  }

  int test20(int x)
  {
    return x;
  }

  virtual int testVir()
  {
    return 0;
  }

  virtual int testVir2(int i)
  {
    return i;
  }

  virtual void testVir4(int i)
  {
    printf("AAAL %d\n", i);
  }

  virtual void testVir3(int i)
  {
    printf("AAAL %d\n", i);
  }

  int num = 78;
  double myDouble = 7.7;
  MyClass class1;
  const char *myCstring;
};

extern int globalNumber;
