//
// Client.cpp - client implementation
//
#include <iostream>
#include <objbase.h>

#include "Iface.h"
using namespace std;

void trace(const char* msg) { cout << "Client: \t\t" << msg << endl ;}
typedef IUnknown* (*CREATEFUNCPTR)();
typedef HRESULT (*REGSERVER)();
//
// main function
//
int main()
{
	// Initialize COM Library
	HRESULT hr0 = CoInitialize(NULL) ;
	if (FAILED(hr0))
	{
		cout << "Client: \t\tCould not CoInitialize. hr = "
			<< hex << hr0 << endl;
	}

	trace("Call CoCreateInstance to create") ;
	trace("  component and get interface IX.") ;
	IX* pIX = NULL ; 
	HRESULT hr = ::CoCreateInstance( CLSID_Component1,
	                                NULL, 
	                                CLSCTX_INPROC_SERVER,
	                                IID_IX, 
	                                (void**)&pIX) ;
	if (SUCCEEDED(hr))
	{
		trace("Succeeded getting IX.") ;
		pIX->Fx() ;          // Use interface IX.

		trace("Ask for interface IY.") ;
		IY* pIY = NULL ;
		hr = pIX->QueryInterface(IID_IY, (void**)&pIY) ;
		if (SUCCEEDED(hr))
		{
			trace("Succeeded getting IY.") ;
			pIY->Fy() ;       // Use interface IY.
			pIY->Release() ;
			trace("Release IY interface.") ;
		}
		else
		{
			trace("Could not get interface IY.") ;
		}

		trace("Ask for interface IZ.") ;

		IZ* pIZ = NULL ;
		hr = pIX->QueryInterface(IID_IZ, (void**)&pIZ) ;
		if (SUCCEEDED(hr))
		{
			trace("Succeeded in getting interface IZ.") ;
			pIZ->Fz() ;
			pIZ->Release() ;
			trace("Release IZ interface.") ;
		}
		else
		{
			trace("Could not get interface IZ.") ;
		}

		trace("Release IX interface.") ;
		pIX->Release() ;
	}
	else
	{
		cout << "Client: \t\tCould not create component. hr = "
		     << hex << hr << endl ;    
	}

	// Uninitialize COM Library
 	CoUninitialize() ;

	return 0 ;
}
