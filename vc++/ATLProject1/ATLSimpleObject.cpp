// ATLSimpleObject.cpp : CATLSimpleObject の実装

#include "pch.h"
#include "ATLSimpleObject.h"


// CATLSimpleObject



STDMETHODIMP CATLSimpleObject::Add2(DOUBLE a, DOUBLE b, DOUBLE* retval)
{
    // TODO: ここに実装コードを追加します
    *retval = a + b;

    return S_OK;
}
