#include <stdio.h>

typedef int (*intfunc)(int);

//extern "C" __declspec(dllexport) int callTwice(int (*f)(int))
extern "C" __declspec(dllexport) int callTwice(intfunc f)
{
    return f(f(42));
}

static intfunc s_func = 0;
extern "C" __declspec(dllexport) void setFunc(intfunc f)
{
    s_func = f;
}

extern "C" __declspec(dllexport) int callTriple()
{
    intfunc f = s_func;
    if(!f) return -1;
    return f(f(f(42)));
}
