﻿// dllmain.cpp : DllMain の実装です。

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "ATLProject1_i.h"
#include "dllmain.h"

CATLProject1Module _AtlModule;

// DLL エントリ ポイント
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
	return _AtlModule.DllMain(dwReason, lpReserved);
}
