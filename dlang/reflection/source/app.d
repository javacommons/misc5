// https://github.com/nicolasjinchereau/d-reflection
module app;

import std.stdio;
import std.conv;
import reflection;
import test;

int main(string[] args)
{
    static const(Module) modRefl = reflect!test;
    static const(Class) classRefl = modRefl.getClass("Test1");

    writeln("Test1 fields:");

    foreach (const(Field) field; classRefl.fields)
    {
        writeln(field);
    }

    writeln();
    writeln("Test1 methods:");

    foreach (const(Method) method; classRefl.methods)
    {
        writeln(method);
    }

    writeln();
    writeln("Test1 properties:");

    foreach (const(Property) property; classRefl.properties)
    {
        writeln(property);
    }

    sub();

    return 0;
}

struct S
{
    float x;
}

class C
{
    private int _y;
    @property int y() const
    {
        return _y;
    }

    @property void y(int v)
    {
        _y = v;
    }

    void z()
    {
        writeln("hello reflection");
    }
}

private void sub()
{
    Test1 t1;

    static const(Module) modRefl = reflect!test;
    static const(Class) classRefl = modRefl.getClass("Test1");

    writeln();
    writeln("Test1 methods:");

    foreach (const(Method) method; classRefl.methods)
    {
        writeln(method);
    }

    writeln(classRefl.getMethod("func1"));
    classRefl.getMethod("func1").invoke(t1);

    //C c;
    //reflect!C.getMethod("z").invoke(c);

    // works at runtime as long as 'reflect!C' has been instantiated
    //auto rt = cast(const(Class))reflect("app.C");
    //rt.getMethod("z").invoke(c);
}
