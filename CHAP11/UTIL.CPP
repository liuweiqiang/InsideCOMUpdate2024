//
//
// util.cpp - Common utilities for printing out messages
//
//
#include <objbase.h>
#include <stdio.h>    //sprintf
#include <stdlib.h>
#include <assert.h>
// #include <twchar_t.h>

#include "util.h"

#ifdef _OUTPROC_SERVER_ 
// We are building a local or remote server.
	// Listbox window handle
	extern HWND g_hWndListBox ;

	static inline void output(const wchar_t* sz)
	{
		::SendMessage(g_hWndListBox, LB_ADDSTRING, 0, (LPARAM)sz) ;
	}

#else
// We are building an in-proc server.
#include <iostream>
using namespace std;

	static inline void output(const wchar_t* sz)
	{
		wcout << sz << endl ;
	}
#endif //_OUTPROC_SERVER_

//
// Utilities
//
namespace Util
{

//
// Print out a message with a label.
//
void Trace(const wchar_t* szLabel, const wchar_t* szText, HRESULT hr)
{
	wchar_t buf[256] ;
	wsprintf(buf, L"%s: \t%s", szLabel, szText) ;
	output(buf) ;

	if (FAILED(hr))
	{
		ErrorMessage(hr) ;
	}
}

//
// Print out the COM/OLE error string for an HRESULT.
//
void ErrorMessage(HRESULT hr)
{
	void* pMsgBuf ;
 
	::FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR)&pMsgBuf,
		0,
		NULL 
	) ;

	wchar_t buf[256] ;
	wsprintf(buf, L"Error (%x): %s", hr, (wchar_t*)pMsgBuf) ;
	output(buf) ;
		
	// Free the buffer.
	LocalFree(pMsgBuf) ;
}

} ; // End Namespace Util

