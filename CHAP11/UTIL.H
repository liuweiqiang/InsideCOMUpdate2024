#ifndef __Util_h__
#define __Util_h__

//
// Util.h - Shared utilities
//
#include <iostream>

namespace Util
{
	void Trace(const wchar_t* szLabel, const wchar_t* szText, HRESULT hr) ;

	void ErrorMessage(HRESULT hr) ;
} ;

#endif // __Util_h__