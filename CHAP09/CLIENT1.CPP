//
// Client1.cpp - Client implementation without smart pointers
//
#include <iostream>
#include <objbase.h>

#include "Iface.h"
#include "Util.h"   // Traces with labels for our output

using namespace std;

static inline void trace(const wchar_t* msg)
	{ Util::Trace(L"Client 1", msg, S_OK) ;} 
static inline void trace(const wchar_t* msg, HRESULT hr)
	{ Util::Trace(L"Client 1", msg, hr) ;}

int main()
{
	// Initialize COM Library
	CoInitialize(NULL) ;

	trace(L"Create Component 1") ;
	IX* pIX = NULL ; 
	HRESULT hr = CoCreateInstance(CLSID_Component1,
	                              NULL,
	                              CLSCTX_INPROC_SERVER,
	                              IID_IX,
	                              (void**)&pIX) ;
	if (SUCCEEDED(hr))
	{
		trace(L"Succeeded creating component.") ;
		pIX->Fx() ;

		trace(L"Get interface IY.") ;
		IY* pIY = NULL ;
		hr = pIX->QueryInterface(IID_IY, (void**)&pIY) ;
		if (SUCCEEDED(hr))
		{
			pIY->Fy() ;

			trace(L"Get interface IX from IY.") ;
			IX* pIX2 = NULL ;
			hr = pIY->QueryInterface(IID_IX, (void**)&pIX2) ;
			if (SUCCEEDED(hr))
			{
				pIX2->Fx() ;
				pIX2->Release();
			}
			else
			{
				trace(L"Could not get interface IX from IY.", hr) ;
			}
			pIY->Release() ;
		}

		trace(L"Get interface IZ.") ;
		IZ* pIZ = NULL ;
		hr = pIX->QueryInterface(IID_IZ, (void**)&pIZ) ;
		if (SUCCEEDED(hr))
		{
			pIZ->Fz() ;

			trace(L"Get interface IX from IZ.") ;
			IX* pIX2 = NULL ;
			hr = pIZ->QueryInterface(IID_IX, (void**)&pIX2) ;
			if (SUCCEEDED(hr))
			{
				pIX2->Fx() ;
				pIX2->Release() ;
			}
			else
			{
				trace(L"Could not get interface IX from IZ.", hr) ;
			}
			pIZ->Release() ;
		}
		pIX->Release() ;
	}
	else
	{
		trace(L"Could not create component.", hr) ;
	}

	// Uninitialize COM Library
	CoUninitialize() ;

	return 0 ;
}
