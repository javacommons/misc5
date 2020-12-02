// dllmain.h : モジュール クラスの宣言です。

class CATLProject1Module : public ATL::CAtlDllModuleT< CATLProject1Module >
{
public :
	DECLARE_LIBID(LIBID_ATLProject1Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLPROJECT1, "{2a0532b1-93da-4572-8aa4-b03e77857167}")
};

extern class CATLProject1Module _AtlModule;
