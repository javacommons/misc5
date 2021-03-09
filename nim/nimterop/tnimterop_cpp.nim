import unittest
import nimterop/cimport
import nimterop/paths

static:
  cDisableCaching()
  cAddSearchDir "." # testsIncludeDir()

cIncludeDir "." # testsIncludeDir()
cCompile(cSearchPath "test2.cpp", mode="cpp")
cImport(cSearchPath "test2.hpp", mode="cpp")

check TEST_INT == 512
check TEST_FLOAT == 5.12
check TEST_HEX == 0x512
check test_call_int() == 5

var foo: Foo
check foo.bar == 0
