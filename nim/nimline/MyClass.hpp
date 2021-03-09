#pragma once

#include <stdio.h>

class MyClass 
{
public:
  MyClass()
  {

  }

  MyClass(int n)
  {
    num = 7;
    nums[0] = 4;
    nums[1] = 5;
  }

  ~MyClass()
  {
    printf("~MyClass\n");
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

  }

  MyClass2(int n)
  {
  }

  ~MyClass2()
  {
    printf("~MyClass2\n");
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
  const char* myCstring;
};

extern int globalNumber;
