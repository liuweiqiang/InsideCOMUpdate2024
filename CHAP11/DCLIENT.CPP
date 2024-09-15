//
// DClient.cpp - Dispatch client implementation
//
//   This client connects to the IX dual interface
//   through the dispinterface.
//
#include <windows.h>
#include <iostream>
#include <sstream>
#include "Util.h"
using namespace std;

static inline void trace(const wchar_t* msg)
	{ Util::Trace(L"DClient", msg, S_OK) ;}
static inline void trace(const wchar_t* msg, HRESULT hr)
	{ Util::Trace(L"DClient", msg, hr) ;}

int main()
{
	cout << "To which server do you want to connect?\r\n"
	     << "1) In-proc Server\r\n" 
	     << "2) Local Server.\r\n:" ;
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

	HRESULT hr = OleInitialize(NULL) ;
	if (FAILED(hr))
	{
		trace(L"Failed to initialize.", hr) ;
		return 1 ;
	}

	// Get the CLSID for the application.
	wchar_t progid[] = L"InsideCOM.Chap11" ;
	CLSID clsid ;
 	hr = ::CLSIDFromProgID(progid, &clsid) ;
	if(FAILED(hr))
	{
		trace(L"Failed to get CLSID.", hr) ;
		return 1 ;
	}

	// Create the component.
	IDispatch* pIDispatch = NULL ;
	hr = ::CoCreateInstance(clsid,
	                        NULL,
	                        clsctx,
	                        IID_IDispatch,
	                        (void**)&pIDispatch) ;
	if (FAILED(hr))
	{
		trace(L"Create instance failed.", hr) ;
		OleUninitialize() ;
		return 1 ;
	}
	trace(L"CoCreateInstance succeeded.") ;

	// First we need to get the IDs for the function names.
	trace(L"Get DispID for function \"Fx\".") ;

	DISPID dispid ;	
	const OLECHAR* name = L"Fx" ;
	hr = pIDispatch->GetIDsOfNames(IID_NULL,
	                                (LPOLESTR*) & name,
	                               1,
	                               GetUserDefaultLCID(),
	                               &dispid) ;
	if (FAILED(hr))
	{
		trace(L"Query GetIDsOfNames failed.", hr) ;
		pIDispatch->Release() ;
		return 1 ;
	}
	
	// Prepare the arguments for Fx.
	DISPPARAMS dispparamsNoArgs = {
		NULL, 
		NULL, 
		0,    // Zero arguments
		0     // Zero named arguments
	} ;

	trace(L"Invoke the function \"Fx\".") ;
	hr = pIDispatch->Invoke(dispid,
	                        IID_NULL,
	                        GetUserDefaultLCID(),
	                        DISPATCH_METHOD,
	                        &dispparamsNoArgs,
	                        NULL, 
	                        NULL, 
	                        NULL) ;
	if (FAILED(hr))
	{
		trace(L"Invoke call failed.", hr) ;
		pIDispatch->Release() ;
		return 1 ;
	}

	//
	// Now pass a BSTR to the component.
	//
	trace(L"Get DispID for function \"FxStringIn\".") ;
	name = L"FxStringIn" ;
	hr = pIDispatch->GetIDsOfNames(IID_NULL,
	                               (LPOLESTR*) & name,
	                               1,
	                               GetUserDefaultLCID(),
	                               &dispid) ;
	if (FAILED(hr))
	{
		trace(L"Query GetIDsOfNames failed.", hr) ;
		pIDispatch->Release() ;
		return 1 ;
	}
	
	// Pass the following string to the component.
	wchar_t wszIn[] = L"This is the test." ;

	// Convert the wide-character string to a BSTR.
	BSTR bstrIn ;
	bstrIn = ::SysAllocString(wszIn) ;

	// Build up the parameters for the invoke call.

	// Allocate and initialize a VARIANT argument.
	VARIANTARG varg ;
	::VariantInit(&varg) ;     // Initialize the VARIANT.
	varg.vt = VT_BSTR ;        // Type of VARIANT data
	varg.bstrVal = bstrIn ;    // Data for the VARIANT

	// Fill in the DISPPARAMS structure.
	DISPPARAMS param ;
	param.cArgs = 1 ;                 // Number of arguments
	param.rgvarg = &varg ;            // Arguments
	param.cNamedArgs = 0 ;            // Number of named args
	param.rgdispidNamedArgs = NULL ;  // Named arguments


	trace(L"Invoke the function \"FxStringIn\".") ;
	hr = pIDispatch->Invoke(dispid,
	                        IID_NULL,
	                        GetUserDefaultLCID(),
	                        DISPATCH_METHOD,
	                        &param,
	                        NULL,
	                        NULL,
	                        NULL) ;
	if (FAILED(hr))
	{
		trace(L"Invoke call failed.", hr) ;
		pIDispatch->Release() ;
		return 1 ;
	}

	// Clean up
	::SysFreeString(bstrIn) ;

	//
	// Now get a BSTR back from the component.
	//

	// Get the dispid.
	trace(L"Get DispID for function \"FxStringOut\".") ;
	name = L"FxStringOut" ;
	hr = pIDispatch->GetIDsOfNames(IID_NULL,
	                               (LPOLESTR*) & name,
	                               1,
	                               GetUserDefaultLCID(),
	                               &dispid) ;
	if (FAILED(hr))
	{
		trace(L"Query GetIDsOfNames failed.", hr) ;
		pIDispatch->Release() ;
		return 1 ;
	}

	// Allocate a variant for the returned parameter.
	VARIANT varResult ;
	::VariantInit(&varResult) ;

	// Invoke the function.
	trace(L"Invoke the function \"FxStringOut\".") ;
	hr = pIDispatch->Invoke(dispid,
	                        IID_NULL,
	                        GetUserDefaultLCID(),
	                        DISPATCH_METHOD,
	                        &dispparamsNoArgs, //&param,
	                        &varResult,
	                        NULL,
	                        NULL) ;
	if (FAILED(hr))
	{
		trace(L"Invoke call failed.", hr) ;
		pIDispatch->Release() ;
		return 1 ;
	}

	// Display the returned string.
	if (varResult.vt == VT_BSTR)
	{
		wostringstream sout ;
		sout << L"String returned from component: "
		     << varResult.bstrVal
		     << ends ;
		trace(sout.str().c_str()) ;

		// Free the string.
		::SysFreeString(varResult.bstrVal) ;
	}

	//
	// Show how to handle a function which returns an EXCEPINFO.
	//
	trace(L"Get DispID for function \"FxFakeError\"") ;
	name = L"FxFakeError" ;
	hr = pIDispatch->GetIDsOfNames(IID_NULL,
	                               (LPOLESTR*) & name,
	                               1,
	                               GetUserDefaultLCID(),
	                               &dispid) ;
	if (FAILED(hr))
	{
		trace(L"Query GetIDsOfNames failed.", hr) ;
		pIDispatch->Release() ;
		return 1 ;
	}

	EXCEPINFO excepinfo ;

	trace(L"Invoke the function \"FxFakeError\".") ;
	hr = pIDispatch->Invoke(dispid,
	                        IID_NULL,
	                        GetUserDefaultLCID(),
	                        DISPATCH_METHOD,
	                        &dispparamsNoArgs,
	                        NULL,
	                        &excepinfo,
	                        NULL) ;

	if (FAILED(hr))
	{
		trace(L"FxFakeError failed.", hr) ;
		if (hr == DISP_E_EXCEPTION)
		{
			trace(L"We have error information from the component.") ;

			if (excepinfo.pfnDeferredFillIn != NULL)
			{
				(*(excepinfo.pfnDeferredFillIn))(&excepinfo) ;
			}

			wostringstream sout ;
			sout << L"Information from component:  "
			     << excepinfo.bstrSource
			     << ends ;
			trace(sout.str().c_str()) ;
		}
	}

	// Release the dispatch interface.
	pIDispatch->Release() ;

	// Uninitialize the OLE library.
	OleUninitialize() ;
	return 0 ;
}
