#ifndef __Util_h__
#define __Util_h__
#include <iostream>
using namespace std;

//
// Util.h - Shared utilities
//
namespace Util
{
	void Trace(const wchar_t* szLabel, const wchar_t* szText, HRESULT hr) ;

	void ErrorMessage(HRESULT hr) ;
} ;


//
// Overloaded insertion operator for converting from
// Unicode (wchar_t) to non-Unicode.
//
ostream& operator<< ( ostream& os, const wchar_t* wsz ) ;

#endif // __Util_h__