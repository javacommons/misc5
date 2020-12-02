
#include <vcl.h>
#pragma hdrstop
#include <System.Win.ComServ.hpp>
#include <axbase.h>

#pragma package(smart_init)
#pragma link "System.Win.ComServ"



// -----------------------------------------------------------------------------
// 初期化または終了されたスレッドやプロセスに対して Windows によって
// 呼び出されたサーバーのエントリ ポイント。
//
// -----------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
    return TRUE;
}


// -----------------------------------------------------------------------------
// DLL が使用されなくなり、読み込み解除が必要かどうかを
// 問い合わせるために呼び出されたサーバーのエントリ ポイント。
// -----------------------------------------------------------------------------
STDAPI __export DllCanUnloadNow(void)
{
    Comserv::TComServer* comserver = Comserv::GetComServer();
    return (!comserver ||
            ((comserver->ObjectCount /* + comserver->FactoryCount */) == 0)) ?
            S_OK : S_FALSE;
}

// -----------------------------------------------------------------------------
// ユーザーのサーバーからクラス オブジェクトを取得することを OLE に許可した
// サーバーのエントリ ポイント。
// -----------------------------------------------------------------------------
STDAPI __export DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    Comobj::TComObjectFactory* Factory = Comobj::ComClassManager()->GetFactoryFromClassID(rclsid);
    if (Factory)
    {
      if (Factory->GetInterface(riid, ppv))
        return S_OK;
      else
        return E_NOINTERFACE;
    }
    else
    {
      *ppv = 0;
      return CLASS_E_CLASSNOTAVAILABLE;
    }
}

// -----------------------------------------------------------------------------
// モジュールでサポートされたすべてのクラスに対するレジストリ エントリ
// を作成するようにサーバーに指示するため呼び出されたサーバーのエントリ ポイント。
// -----------------------------------------------------------------------------
STDAPI __export DllRegisterServer(void)
{
    Comserv::TComServer* comserver = Comserv::GetComServer();
    if (comserver)
    {
        try
        {
            comserver->LoadTypeLib();
            comserver->UpdateRegistry(true);
            return S_OK;
        }
        catch(...)
        {
            return E_FAIL;
        }
    }
    else
    {
        return E_FAIL;
    }
}

// -----------------------------------------------------------------------------
// DllRegisterServer を通じて作成されたすべてのレジストリ エントリを
// 削除するようにサーバーに指示するため呼び出されたサーバーのエントリ ポイント。
// -----------------------------------------------------------------------------
STDAPI __export DllUnregisterServer(void)
{
    Comserv::TComServer* comserver = Comserv::GetComServer();
    if (comserver)
    {
        try
        {
            comserver->LoadTypeLib();
            comserver->UpdateRegistry(false);
            return S_OK;
        }
        catch(...)
        {
            return E_FAIL;
        }
    }
    else
    {
        return E_FAIL;
    }
}

// ------------------------------------------------------------------------------
// サーバー インストール/セットアップのエントリ ポイント。'ユーザーごとの' 登録に使用
// "regsvr32 /n /i:user [/u] axlibrary.dll" の呼び出しを通じて起動
// ------------------------------------------------------------------------------
STDAPI __export DllInstall(BOOL bInstall, LPCWSTR pszCmdLine)
{
    Comserv::TComServer* comserver = Comserv::GetComServer();
    if (comserver)
    {
        bool savePerUser = comserver->PerUserRegistration;
        if (pszCmdLine && !Sysutils::StrIComp(pszCmdLine, L"user"))
            comserver->PerUserRegistration = true;
        else
            comserver->PerUserRegistration = false;
        HRESULT result = E_FAIL;
        if (bInstall)
        {
            result = DllRegisterServer();
            if (result == E_FAIL)
                DllUnregisterServer();
        }
        else
            result = DllUnregisterServer();
        comserver->PerUserRegistration = savePerUser;
        return result;
    }
    else
    {
        return E_FAIL;
    }
}



