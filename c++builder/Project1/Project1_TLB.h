// ************************************************************************ //
// �x��
// -------
// ���̃t�@�C���Ő錾����Ă���^�̓^�C�v ���C�u��������ǂݎ��ꂽ�f�[�^����
// ��������Ă��܂��B���̃^�C�v ���C�u�����������I���邢�́i���̃^�C�v ���C�u��
// �����Q�Ƃ��Ă���ق��̃^�C�v ���C�u�����o�R�Łj�ԐړI�ɍăC���|�[�g���ꂽ
// ��A�^�C�v ���C�u���C�u�����̕ҏW���Ƀ^�C�v ���C�u���� �G�f�B�^�́m�X�V�n�R�}
// ���h�����s�����ꍇ�A���̃t�@�C���̓��e�͂��ׂčĐ�������A�蓮�ŉ������ύX
// �͂��ׂĎ����܂��B
// ************************************************************************ //

// $Rev: 92848 $
// ���ɐ������ꂽ�^�C�v ���C�u�������� 2020/12/01 11:48:12 �ɐ������ꂽ�t�@�C���B

// ************************************************************************  //
// �^�C�v ���C�u����: C:\Users\javac\misc5\c++builder\Project1\Project1 (1)
// LIBID: {AE49D51F-AFF3-41BA-9D66-C09D38754E77}
// LCID: 0
// �w���v�t�@�C��:
// �w���v������:
// �ˑ��֌W���X�g:
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
// C++ Builder �̃C���|�[�g|ActiveX �ƃC���|�[�g|�^�C�v ���C�u�����@�\�܂��� TLIBIMP ���[�e�B���e�B
// ��萶�������R�[�h�� INCLUDE\VCL �f�B���N�g���ɂ���
// UTILCLS.H �w�b�_�[ �t�@�C���̓���o�[�W�����Ɉˑ����܂��B�t�@�C����
// �ȑO�̃o�[�W���������o���ꂽ�ꍇ�́A�X�V��p�b�`���K�v�ɂȂ邱�Ƃ�����܂��B
//
#error "���̃t�@�C���ł͐V�����o�[�W�����̃w�b�_�[ UTILCLS.H ���K�v�ł��B" \
"C++ Builder ���X�V�܂��̓p�b�`��K�p����K�v������܂�"
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
// �w���v������:
// �o�[�W����: 1.0
// *********************************************************************//

// *********************************************************************//
// �^�C�v ���C�u�����Ő錾���ꂽ GUID���̃v���t�B�b�N�X���g�p����܂�:
// �^�C�v ���C�u����      : LIBID_xxxx
//   CoClasses          : CLSID_xxxx
// �f�B�X�p�b�` �C���^�[�t�F�C�X: DIID_xxxx
// ��f�B�X�p�b�` �C���^�[�t�F�C�X: IID_xxxx
// *********************************************************************//
extern __declspec (package) const GUID LIBID_Project1;
extern __declspec (package) const GUID CLSID_CoClass1;
extern __declspec (package) const GUID DIID_DispInterface1;
// *********************************************************************//
// �^�C�v ���C�u�����Ő錾�����O���Q��
// *********************************************************************//
interface DECLSPEC_UUID("{CF2B8A63-94AC-42CA-B962-AC2C9C06F252}") DispInterface1;
typedef TComInterface<DispInterface1, &DIID_DispInterface1> DispInterface1Ptr;

// *********************************************************************//
// �C���^�[�t�F�C�X: DispInterface1
// �t���O: (0)
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
// �t���O:     (0)
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
// �t���O:     (0)
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

