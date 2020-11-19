--json = require "json"

print("hello from lua!")

print(overfunc(11))
print(overfunc("ABC"))
print(of2(22))
print(of2("XYZ"))

print(intval)   -- => '100'
print(pi)  -- => '3.14'
print(some_text)  -- => 'abcdef'

a = 100
b = 200
c = 300

a = A.new(100, "だみー")
print(a)
--print(json.encode(a))
print(a:f())  -- => '10000'
print(a:f(10))
print(a:f(11, 22))
print(a:g())  -- => '10000'
print(a:g(10))

a.val = 456
print(a.val)  -- => '456'
print(a:f())  -- => '45600'

a.x = 123
print(a.x)  -- => '123'

print(a:y(200))  -- => '24600'

a = 100

ary = {11, 22, 33}

print(ary[1])
print(ary)
print(json.encode(ary))

print(A.st_fun(100))
print(A.st_fun2(100))


x = A.new(100, "だみー2")
collectgarbage("collect")
