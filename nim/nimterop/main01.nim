import nimterop/cimport
import nimterop/paths

static:
  cDisableCaching()
  cAddSearchDir "."

cIncludeDir "."
cCompile(cSearchPath "test2.cpp", mode="cpp")
cImport(cSearchPath "test2.hpp", mode="cpp")


echo TEST_INT
echo TEST_FLOAT
echo TEST_HEX
echo test_call_int()
var foo: Foo
echo foo.bar
