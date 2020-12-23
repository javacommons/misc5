#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ole2.h> // OLE2 Definitions
#include "strconv.h"

// AutoWrap() - Automation helper function...
HRESULT AutoWrap(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPCOLESTR ptName, int cArgs...)
{
    // Begin variable-argument list...
    va_list marker;
    va_start(marker, cArgs);

    if (!pDisp)
    {
        MessageBoxA(NULL, "NULL IDispatch passed to AutoWrap()", "Error", 0x10010);
        _exit(0);
    }

    // Variables used...
    DISPPARAMS dp = {NULL, NULL, 0, 0};
    DISPID dispidNamed = DISPID_PROPERTYPUT;
    DISPID dispID;
    HRESULT hr;
    char buf[200];
    char szName[200];

    // Convert down to ANSI
    WideCharToMultiByte(CP_ACP, 0, ptName, -1, szName, sizeof szName, NULL, NULL);

    // Get DISPID for name passed...
    hr = pDisp->GetIDsOfNames(IID_NULL, (LPOLESTR *)&ptName, 1, LOCALE_USER_DEFAULT, &dispID);
    if (FAILED(hr))
    {
        sprintf(buf, "IDispatch::GetIDsOfNames(\"%s\") failed w/err 0x%08lx", szName, hr);
        MessageBoxA(NULL, buf, "AutoWrap()", 0x10010);
        _exit(0);
        return hr;
    }

    // Allocate memory for arguments...
    VARIANT *pArgs = new VARIANT[cArgs + 1];
    // Extract arguments...
    for (int i = 0; i < cArgs; i++)
    {
        pArgs[i] = va_arg(marker, VARIANT);
    }

    // Build DISPPARAMS
    dp.cArgs = cArgs;
    dp.rgvarg = pArgs;

    // Handle special-case for property-puts!
    if (autoType & DISPATCH_PROPERTYPUT)
    {
        dp.cNamedArgs = 1;
        dp.rgdispidNamedArgs = &dispidNamed;
    }

    // Make the call!
    hr = pDisp->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, autoType, &dp, pvResult, NULL, NULL);
    if (FAILED(hr))
    {
        sprintf(buf, "IDispatch::Invoke(\"%s\"=%08lx) failed w/err 0x%08lx", szName, dispID, hr);
        MessageBoxA(NULL, buf, "AutoWrap()", 0x10010);
        _exit(0);
        return hr;
    }
    // End variable-argument section...
    va_end(marker);

    delete[] pArgs;

    return hr;
}

int main()
{
    // Initialize COM for this thread...
    (void)CoInitialize(NULL);

    // Get CLSID for our server...
    CLSID clsid;
    HRESULT hr = CLSIDFromProgID(L"WScript.Shell", &clsid);

    if (FAILED(hr))
    {

        ::MessageBoxA(NULL, "CLSIDFromProgID() failed", "Error", 0x10010);
        return -1;
    }

    // Start server and get IDispatch...
    IDispatch *pShell;
    hr = CoCreateInstance(clsid, NULL, /*CLSCTX_LOCAL_SERVER*/ CLSCTX_INPROC_SERVER, IID_IDispatch, (void **)&pShell);
    formatA(std::cout, "hr=%x\n", hr);
    if (FAILED(hr))
    {
        ::MessageBoxA(NULL, "WScript.Shell not registered properly", "Error", 0x10010);
        return -2;
    }

    IDispatch *pEnv;
    {
        VARIANT parm;
        parm.vt = VT_BSTR;
        parm.bstrVal = ::SysAllocString(L"USER");

        VARIANT result;
        VariantInit(&result);
        hr = AutoWrap(DISPATCH_PROPERTYGET, &result, pShell, L"Environment", 1, parm);
        formatA(std::cout, "hr=%x\n", hr);
        VariantClear(&parm);

        pEnv = result.pdispVal;
    }

    {
        VARIANT parm;
        parm.vt = VT_BSTR;
        parm.bstrVal = ::SysAllocString(L"PATH");

        VARIANT result;
        VariantInit(&result);
        hr = AutoWrap(DISPATCH_PROPERTYGET, &result, pEnv, L"Item", 1, parm);
        formatA(std::cout, "hr=%x\n", hr);
        formatA(std::cout, "result.vt=%u\n", result.vt);
        formatA(std::cout, L"result.bstrVal=%s\n", result.bstrVal);
        VariantClear(&parm);
    }

    {
        VARIANT parm;
        parm.vt = VT_BSTR;
        parm.bstrVal = ::SysAllocString(L"xyz漢字©");
        VARIANT parm2;
        parm2.vt = VT_BSTR;
        parm2.bstrVal = ::SysAllocString(L"PATH2");

        VARIANT result;
        VariantInit(&result);
        hr = AutoWrap(DISPATCH_PROPERTYPUT, NULL, pEnv, L"Item", 2, parm, parm2);
        formatA(std::cout, "hr=%x\n", hr);
        VariantClear(&parm);
        VariantClear(&parm2);
    }

    pEnv->Release();
    pShell->Release();

    // Uninitialize COM for this thread...
    CoUninitialize();
}