import nimline

defineCppType(MyClass, "MyClass", "MyClass.hpp")
defineCppType(MyClass2, "MyClass2", "MyClass.hpp")
cppfiles("MyClass.cpp")
#var obj = cppinit(MyClass, 1)
#obj.someField = 42
#let res = obj.someMethod(1, 2.0).to(cint)

# or for an internal pointer, which is more flexible due to lack of constructors in nim
var
  myx = MyClass.new()
  myx2 = MyClass2.new()
myx.test3().to(void)
myx.num = 99
var x = myx2.test20(1234).to(cint)
echo x
#echo myx2.num.to(cint)
#let n = myx2.num().to(cint)
echo global.globalNumber.to(cint)
