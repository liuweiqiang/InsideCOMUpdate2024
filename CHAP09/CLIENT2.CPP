//
// Client2.cpp - Client implementation with smart pointers
//
#include <objbase.h>

#include "Iface.h"
#include "Util.h"   // Traces with labels for our output
#include "Ptr.h"    // Smart pointer classes

static inline void trace(const wchar_t* msg)
	{ Util::Trace(L"Client 2", msg, S_OK) ;} 
static inline void trace(const wchar_t* msg, HRESULT hr)
	{ Util::Trace(L"Client 2", msg, hr) ;}

void Think() 
{
	trace(L"Create Component 1.") ;
	IPtr<IX, &IID_IX> spIX ; 
	HRESULT hr = CoCreateInstance(CLSID_Component1,
	                              NULL,
	                              CLSCTX_INPROC_SERVER, 
	                              spIX.iid(),
	                              (void**)&spIX) ;
	if (SUCCEEDED(hr))
	{
		trace(L"Succeeded creating component.") ;
		spIX->Fx() ;

		trace(L"Get interface IY.") ;
		IPtr<IY, &IID_IY> spIY ;
		spIY = spIX ;		// Use Assignment.
		if (spIY)
		{
			spIY->Fy() ;

			trace(L"Get interface IX from IY.") ;
			IPtr<IX, &IID_IX> spIX2(spIY) ; // Use Constructor.
			if (!spIX2)
			{
				trace(L"Could not get interface IX from IY.") ;
			}
			else
			{
				spIX2->Fx() ;
			}
		}

		trace(L"Get interface IZ.") ;
		IPtr<IZ, &IID_IZ> spIZ ;
		spIZ = spIX ;
		if (spIZ)
		{
			spIZ->Fz() ;

			trace(L"Get interface IX from IZ.") ;
			IPtr<IX, &IID_IX> spIX2(spIZ) ;
			if (!spIX2)
			{
				trace(L"Could not get interface IX from IZ.") ;
			}
			else
			{
				spIX2->Fx() ;
			}
		}
	}
	else
	{
		trace(L"Could not create component.", hr) ;
	}

}

int main()
{
	// Initialize COM Library.
	CoInitialize(NULL) ;

	// Exercise the smart pointers.
	Think() ;

	// Uninitialize COM Library.
	CoUninitialize() ;

	return 0 ;
}
