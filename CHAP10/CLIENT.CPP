//
// Client.cpp - client implementation
//
#include <objbase.h>
#include <iostream>
#include <sstream>
#include <assert.h>

#include "../CHAP10_InProc/UTIL.H"
#include "../CHAP10_InProc/Iface.h"

using namespace std;

static inline void trace(const wchar_t* msg)
	{ Util::Trace(L"Client", msg, S_OK) ;} 
static inline void trace(const wchar_t* msg, HRESULT hr)
	{ Util::Trace(L"Client", msg, hr) ;}

int main()
{
	cout << "To which server do you want to connect?\r\n"
	     << "1) In-proc Server\r\n" 
	     << "2) Local Server\r\n:" ;
	int i = 0 ;
	cin >> i ;

	DWORD clsctx ;
	if (i == 1)
	{
		clsctx = CLSCTX_INPROC_SERVER ;
		trace(L"Attempt to create in-proc component.") ;
	}
	else
	{
		clsctx = CLSCTX_LOCAL_SERVER ;
		trace(L"Attempt to create local component.") ;
	}

	// Initialize COM Library
	CoInitialize(NULL) ;

	IX* pIX = NULL; 
	HRESULT hr = CoCreateInstance(CLSID_Component1,
	                              NULL, clsctx, 
	                              IID_IX, (void**)&pIX) ;
	if (SUCCEEDED(hr))
	{
		trace(L"Successfully created component.") ;
		trace(L"Use interface IX.") ;
		wchar_t* szOut = NULL ;
		hr = pIX->FxStringIn((wchar_t*)L"This is the test.") ;
		assert(SUCCEEDED(hr)) ;
		hr = pIX->FxStringOut(&szOut) ;
		assert(SUCCEEDED(hr)) ;

		// Display returned string.
		wostringstream sout ;
		sout << "FxStringOut returned a string:  "
		     << szOut
		     << ends ;
		trace(sout.str().c_str()) ;

		// Free the returned string.
		::CoTaskMemFree(szOut) ;

		trace(L"Get interface IY.") ;
		IY* pIY = NULL ;
		hr = pIX->QueryInterface(IID_IY, (void**)&pIY) ;
		if (SUCCEEDED(hr))
		{
			// Send an array to the component. 
			long arrayIn[] = { 22, 44, 206, 76, 300, 500 } ;
			long sizeIn = sizeof(arrayIn) / sizeof(arrayIn[0]) ; 
			hr = pIY->FyArrayIn(sizeIn, arrayIn) ;
			assert(SUCCEEDED(hr)) ;

			// Get the array back from the component.

			// Get the size of the array.
			long sizeOut = 0 ;
			hr = pIY->FyCount(&sizeOut) ;
			assert(SUCCEEDED(hr)) ;

			// Allocate the array.
			long* arrayOut = new long[sizeOut] ;

			// Get the array.
			hr = pIY->FyArrayOut(&sizeOut, arrayOut) ;
			assert(SUCCEEDED(hr)) ;

			// Display the array returned from the function.
			wostringstream sout ;
			sout	<< "FyArray returned " 
			      << sizeOut
			      << " elements: " ;
			for (int i = 0 ; i < sizeOut ; i++)
			{
				sout << " " << arrayOut[i] ;
			}
			sout << "." << ends ;
			trace(sout.str().c_str()) ;

			// Cleanup
			trace(L"Release IY.") ;
			delete [] arrayOut ;

			pIY->Release() ;
		}
		else
		{
			trace(L"Could not get interface IY from IX.", hr) ;
		}

		trace(L"Get interface IZ.") ;
		IZ* pIZ = NULL ;
		hr = pIX->QueryInterface(IID_IZ, (void**)&pIZ) ;
		if (SUCCEEDED(hr))
		{
			// Pass a point to the component.
			Point3d ptIn ;
			ptIn.x = 3.14 ;
			ptIn.y = 2.81 ;
			ptIn.z = 9.8 ;
			hr = pIZ->FzStructIn(ptIn) ;
			assert(SUCCEEDED(hr)) ;

			// Get the point back from the component.
			Point3d ptOut ;
			hr = pIZ->FzStructOut(&ptOut) ;
			assert(SUCCEEDED(hr)) ;
			wostringstream sout ;
			sout << "FzStructOut returned ("
			     << ptOut.x << ", "
			     << ptOut.y << ", "
			     << ptOut.z << ")."
			     << ends ;
			trace(sout.str().c_str()) ;

			pIZ->Release() ;
		}
		else
		{
			trace(L"Could not get interface IZ from IX.", hr) ;
		}
		trace(L"Release IX.") ;
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
