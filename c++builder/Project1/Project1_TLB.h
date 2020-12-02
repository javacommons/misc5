// ************************************************************************ //
// 警告
// -------
// このファイルで宣言されている型はタイプ ライブラリから読み取られたデータから
// 生成されています。このタイプ ライブラリが明示的あるいは（このタイプ ライブラ
// リを参照しているほかのタイプ ライブラリ経由で）間接的に再インポートされた
// り、タイプ ライブライブラリの編集中にタイプ ライブラリ エディタの［更新］コマ
// ンドを実行した場合、このファイルの内容はすべて再生成され、手動で加えた変更
// はすべて失われます。
// ************************************************************************ //

// $Rev: 92848 $
// 下に説明されたタイプ ライブラリから 2020/12/01 11:48:12 に生成されたファイル。

// ************************************************************************  //
// タイプ ライブラリ: C:\Users\javac\misc5\c++builder\Project1\Project1 (1)
// LIBID: {AE49D51F-AFF3-41BA-9D66-C09D38754E77}
// LCID: 0
// ヘルプファイル:
// ヘルプ文字列:
// 依存関係リスト:
//   (1) v2.0 stdole, (C:\Windows\SysWOW64\stdole2.tlb)
// SYS_KIND: SYS_WIN32
// ************************************************************************ //
#ifndef   Project1_TLBH
#define   Project1_TLBH

#pragma option push -b -w-inl -w-8118
#pragma pack(push, 4)

#if !defined(__UTILCLS_H)
#include <utilcls.h>
#endif
#if !defined(__UTILCLS_H_VERSION) || (__UTILCLS_H_VERSION < 0x0700)
//
// C++ Builder のインポート|ActiveX とインポート|タイプ ライブラリ機能または TLIBIMP ユーティリティ
// より生成されるコードは INCLUDE\VCL ディレクトリにある
// UTILCLS.H ヘッダー ファイルの特定バージョンに依存します。ファイルの
// 以前のバージョンが検出された場合は、更新やパッチが必要になることがあります。
//
#error "このファイルでは新しいバージョンのヘッダー UTILCLS.H が必要です。" \
"C++ Builder を更新またはパッチを適用する必要があります"
#endif
#include <olectl.h>
#include <ocidl.h>
#if defined(USING_ATLVCL) || defined(USING_ATL)
#if !defined(__TLB_NO_EVENT_WRAPPERS)
#include <atl/atlmod.h>
#endif
#endif

#include <System.Win.StdVCL.hpp>

typedef TComInterface<System::Win::Stdvcl::IStrings> IStringsPtr;
typedef TComInterface<System::Win::Stdvcl::IStringsDisp> IStringsDispPtr;

namespace Project1_tlb
{

// *********************************************************************//
// ヘルプ文字列:
// バージョン: 1.0
// *********************************************************************//

// *********************************************************************//
// タイプ ライブラリで宣言された GUID次のプレフィックスが使用されます:
// タイプ ライブラリ      : LIBID_xxxx
//   CoClasses          : CLSID_xxxx
// ディスパッチ インターフェイス: DIID_xxxx
// 非ディスパッチ インターフェイス: IID_xxxx
// *********************************************************************//
extern __declspec (package) const GUID LIBID_Project1;
extern __declspec (package) const GUID CLSID_CoClass1;
extern __declspec (package) const GUID DIID_DispInterface1;
// *********************************************************************//
// タイプ ライブラリで宣言される前方参照
// *********************************************************************//
interface DECLSPEC_UUID("{CF2B8A63-94AC-42CA-B962-AC2C9C06F252}") DispInterface1;
typedef TComInterface<DispInterface1, &DIID_DispInterface1> DispInterface1Ptr;

// *********************************************************************//
// インターフェイス: DispInterface1
// フラグ: (0)
// GUID: {CF2B8A63-94AC-42CA-B962-AC2C9C06F252}
// *********************************************************************//
interface DispInterface1 : public TDispWrapper<IDispatch>
{
  HRESULT __fastcall Add2(double a/*[in]*/, double b/*[in]*/, double* retval/*[out,retval]*/)
  {
    _TDispID _dispid(/* Add2 */ DISPID(201));
    TAutoArgs<2> _args;
    _args[1] = a /*[VT_R8:0]*/;
    _args[2] = b /*[VT_R8:0]*/;
    return OutRetValSetterPtr(retval /*[VT_R8:1]*/, _args, OleFunction(_dispid, _args));
  }

  double __fastcall Add2(double a/*[in]*/, double b/*[in]*/)
  {
    double retval;
    this->Add2(a, b, (double*)&retval);
    return retval;
  }


};
#if !defined(__TLB_NO_INTERFACE_WRAPPERS)
// *********************************************************************//
// DispIntf:  DispInterface1
// フラグ:     (0)
// GUID:      {CF2B8A63-94AC-42CA-B962-AC2C9C06F252}
// *********************************************************************//
template<class T>
class DispInterface1DispT : public TAutoDriver<DispInterface1>
{
public:
  DispInterface1DispT(){}

  DispInterface1DispT(DispInterface1 *pintf)
  {
    TAutoDriver<DispInterface1>::Bind(pintf, false);
  }

  DispInterface1DispT(DispInterface1Ptr pintf)
  {
    TAutoDriver<DispInterface1>::Bind(pintf, true);
  }

  DispInterface1DispT& operator=(DispInterface1 *pintf)
  {
    TAutoDriver<DispInterface1>::Bind(pintf, false);
    return *this;
  }

  DispInterface1DispT& operator=(DispInterface1Ptr pintf)
  {
    TAutoDriver<DispInterface1>::Bind(pintf, true);
    return *this;
  }

  HRESULT         __fastcall Add2(double a/*[in]*/, double b/*[in]*/, double* retval/*[out,retval]*/);
  double          __fastcall Add2(double a/*[in]*/, double b/*[in]*/);

};
typedef DispInterface1DispT<DispInterface1> DispInterface1Disp;

// *********************************************************************//
// DispIntf:  DispInterface1
// フラグ:     (0)
// GUID:      {CF2B8A63-94AC-42CA-B962-AC2C9C06F252}
// *********************************************************************//
template <class T> HRESULT __fastcall
DispInterface1DispT<T>::Add2(double a/*[in]*/, double b/*[in]*/, double* retval/*[out,retval]*/)
{
  _TDispID _dispid(*this, OLETEXT("Add2"), DISPID(201));
  TAutoArgs<2> _args;
  _args[1] = a /*[VT_R8:0]*/;
  _args[2] = b /*[VT_R8:0]*/;
  return OutRetValSetterPtr(retval /*[VT_R8:1]*/, _args, OleFunction(_dispid, _args));
}

template <class T> double __fastcall
DispInterface1DispT<T>::Add2(double a/*[in]*/, double b/*[in]*/)
{
  double retval;
  this->Add2(a, b, (double*)&retval);
  return retval;
}

#endif  //   __TLB_NO_INTERFACE_WRAPPERS


};     // namespace Project1_tlb

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using  namespace Project1_tlb;
#endif

#pragma pack(pop)
#pragma option pop

#endif // Project1_TLBH

