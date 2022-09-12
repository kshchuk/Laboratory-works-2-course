// dllmain.h : Declaration of module class.

class CTask15Module : public ATL::CAtlDllModuleT< CTask15Module >
{
public :
	DECLARE_LIBID(LIBID_Task15Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TASK15, "{bb580ac9-afb2-4c1a-b6f1-cc22faaf6f0e}")
};

extern class CTask15Module _AtlModule;
