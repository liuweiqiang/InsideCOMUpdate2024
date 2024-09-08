//
// Cmpnt3.cpp - Component 3
//
#include <objbase.h>

#include "Iface.h"
#include "Util.h"
#include "CUnknown.h" // Base class for IUnknown
#include "Cmpnt3.h"

static inline void trace(const wchar_t* msg)
	{Util::Trace(L"Component 3", msg, S_OK) ;} 
static inline void trace(const wchar_t* msg, HRESULT hr)
	{Util::Trace(L"Component 3", msg, hr) ;}

///////////////////////////////////////////////////////////
//
// Interface IZ implementation
//
void __stdcall CC::Fz() 
{ 
	trace(L"Fz") ;
}

//
// Constructor
//
CC::CC(IUnknown* pUnknownOuter)
: CUnknown(pUnknownOuter)
{
	// Empty
}

//
// Destructor
//
CC::~CC() 
{
	trace(L"Destroy self.") ;
}

//
// NondelegatingQueryInterface implementation
//
HRESULT __stdcall
	CC::NondelegatingQueryInterface(const IID& iid, void** ppv)
{ 	
	if (iid == IID_IZ)
	{
		return FinishQI(static_cast<IZ*>(this), ppv) ;
	}
	else
	{
		return CUnknown::NondelegatingQueryInterface(iid, ppv) ;
	}
}


///////////////////////////////////////////////////////////
//
// Creation function used by CFactory
//
HRESULT CC::CreateInstance(IUnknown* pUnknownOuter,
                           CUnknown** ppNewComponent)
{
	*ppNewComponent = new CC(pUnknownOuter) ;
	return S_OK ;
}
