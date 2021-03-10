import nimline

defineCppType(MyClass, "MyClass", "MyClass.hpp")
defineCppType(MyClass2, "MyClass2", "MyClass.hpp")
cppfiles("MyClass.cpp")

var
  myx2 = MyClass2.new()
  myx = MyClass.new(555)
myx.test3().to(void)
myx.num = 99
var x = myx2.test20(1234).to(cint)
echo x
#echo myx2.num.to(cint)
#let n = myx2.num().to(cint)
echo global.globalNumber.to(cint)
let msg: StdString = "HelloWorld"
myx.say(msg).to(void)
let gr = myx.greeting(msg).to(StdString)
echo gr.c_str().to(cstring)
echo myx.z().to(cint)
myx.z(222).to(void)
echo myx.z().to(cint)
#echo myx2.class1.z().to(cint)

