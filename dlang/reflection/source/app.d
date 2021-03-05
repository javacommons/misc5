// https://github.com/nicolasjinchereau/d-reflection
module app;

import reflection;
import box;

import std.stdio;
import std.conv;
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
    void dump()
    {
        writeln("S::dump()");
    }
}

class C
{
    public int x;
    private int _y;
    @property int y() const
    {
        return _y;
    }

    @property void y(int v)
    {
        _y = v;
    }

    @property void y(string v)
    {
        _y = to!int(v);
    }

    int _z = 0;
    int   getZ()
    {
        writeln("hello reflection");
        return this._z;
    }

    void setZ(int value)
    {
        this._z = value;
    }
}

private void sub()
{
    Test1 t1 = new Test1();

    static const(Module) modRefl = reflect!test;
    static const(Class) classRefl = modRefl.getClass("Test1");

    writeln();
    writeln("Test1 methods:");

    foreach (const(Method) method; classRefl.methods)
    {
        writeln(method);
    }

    writeln(classRefl.getMethod("func1"));
    //classRefl.getMethod("func1").invoke(t1);
    const(Method) m = classRefl.getMethod("func1");
    m.invoke(t1);

    C c = new C;
    auto C_refl = reflect!C;
    writeln(C_refl.getProperty("y"));
    const(Method) C_setZ = C_refl.getMethod("setZ");
    C_setZ.invoke(c, 888);
    writefln("c._z=%d", c._z);
    const(Method) C_getZ = C_refl.getMethod("getZ");
    writeln(cast(int)C_getZ.invoke(c));
    const(Property) y = C_refl.getProperty("y");
    writeln(y.canGetValue());
    writeln(y.canSetValue());
    auto C_y_setters = y.setters();
    foreach(setter; C_y_setters) {
        writefln("setter=%s", setter);
    }
    C_y_setters[0].invoke(c, 7777);
    writeln(c.y);
    /*
    C_y_setters[1].invoke(c, 8888);
    */
    writeln(c.y);
    //writeln(y.getValue(c));
    const(Field) x = C_refl.getField("x");
    writeln(x);
    //x.setValue(c, 1234);

    foreach (const(Method) method; C_refl.methods)
    {
        writeln(method);
    }
    //C c;
    //reflect!C.getMethod("z").invoke(c);

    // works at runtime as long as 'reflect!C' has been instantiated
    //auto rt = cast(const(Class))reflect("app.C");
    //rt.getMethod("z").invoke(c);
}
