//
// Registry.cpp
//

#include <objbase.h>
#include <assert.h>

#include "Registry.h"

////////////////////////////////////////////////////////
//
// Internal helper functions prototypes
//

// Set the given key and its value.
BOOL setKeyAndValue(const wchar_t* pszPath,
                    const wchar_t* szSubkey,
                    const wchar_t* szValue) ;

// Convert a CLSID into a wchar_t string.
void CLSIDtowchar_t(const CLSID& clsid, 
                 wchar_t* szCLSID,
                 int length) ;

// Delete szKeyChild and all of its descendents.
LONG recursiveDeleteKey(HKEY hKeyParent, const wchar_t* szKeyChild) ;

////////////////////////////////////////////////////////
//
// Constants
//

// Size of a CLSID as a string
const int CLSID_STRING_SIZE = 39 ;

/////////////////////////////////////////////////////////
//
// Public function implementation
//

//
// Register the component in the registry.
//
HRESULT RegisterServer(HMODULE hModule,            // DLL module handle
                       const CLSID& clsid,         // Class ID
                       const wchar_t* szFriendlyName, // Friendly Name
                       const wchar_t* szVerIndProgID, // Programmatic
                       const wchar_t* szProgID)       //   IDs
{
	// Get server location.
	wchar_t szModule[512];
	DWORD dwResult =
		::GetModuleFileNameW(hModule, 
		                    szModule,
		                    sizeof(szModule)/sizeof(wchar_t)) ;
	assert(dwResult != 0) ;

	// Convert the CLSID into a wchar_t.
	wchar_t szCLSID[CLSID_STRING_SIZE] ;
	CLSIDtowchar_t(clsid, szCLSID, sizeof(szCLSID) / sizeof(wchar_t)) ;

	// Build the key CLSID\\{...}
	wchar_t szKey[128] ;
	wcscpy_s(szKey, sizeof(szKey) / sizeof(wchar_t), L"CLSID\\");
	wcscat_s(szKey, sizeof(szKey) / sizeof(wchar_t), szCLSID);
  
	// Add the CLSID to the registry.
	setKeyAndValue(szKey, NULL, szFriendlyName) ;

	// Add the server filename subkey under the CLSID key.
	setKeyAndValue(szKey, L"InprocServer32", szModule) ;

	// Add the ProgID subkey under the CLSID key.
	setKeyAndValue(szKey, L"ProgID", szProgID) ;

	// Add the version-independent ProgID subkey under CLSID key.
	setKeyAndValue(szKey, L"VersionIndependentProgID",
	               szVerIndProgID) ;

	// Add the version-independent ProgID subkey under HKEY_CLASSES_ROOT.
	setKeyAndValue(szVerIndProgID, NULL, szFriendlyName) ; 
	setKeyAndValue(szVerIndProgID, L"CLSID", szCLSID) ;
	setKeyAndValue(szVerIndProgID, L"CurVer", szProgID) ;

	// Add the versioned ProgID subkey under HKEY_CLASSES_ROOT.
	setKeyAndValue(szProgID, NULL, szFriendlyName) ; 
	setKeyAndValue(szProgID, L"CLSID", szCLSID) ;

	return S_OK ;
}

//
// Remove the component from the registry.
//
LONG UnregisterServer(const CLSID& clsid,         // Class ID
                      const wchar_t* szVerIndProgID, // Programmatic
                      const wchar_t* szProgID)       //   IDs
{
	// Convert the CLSID into a wchar_t.
	wchar_t szCLSID[CLSID_STRING_SIZE] ;
	CLSIDtowchar_t(clsid, szCLSID, sizeof(szCLSID) / sizeof(wchar_t)) ;

	// Build the key CLSID\\{...}
	wchar_t szKey[64] ;
	wcscpy_s(szKey, sizeof szKey / sizeof(wchar_t), L"CLSID\\");
	wcscat_s(szKey, sizeof szKey / sizeof(wchar_t), szCLSID);

	// Delete the CLSID Key - CLSID\{...}
	LONG lResult = recursiveDeleteKey(HKEY_CLASSES_ROOT, szKey) ;
	assert((lResult == ERROR_SUCCESS) ||
	       (lResult == ERROR_FILE_NOT_FOUND)) ; // Subkey may not exist.

	// Delete the version-independent ProgID Key.
	lResult = recursiveDeleteKey(HKEY_CLASSES_ROOT, szVerIndProgID) ;
	assert((lResult == ERROR_SUCCESS) ||
	       (lResult == ERROR_FILE_NOT_FOUND)) ; // Subkey may not exist.

	// Delete the ProgID key.
	lResult = recursiveDeleteKey(HKEY_CLASSES_ROOT, szProgID) ;
	assert((lResult == ERROR_SUCCESS) ||
	       (lResult == ERROR_FILE_NOT_FOUND)) ; // Subkey may not exist.

	return S_OK ;
}

///////////////////////////////////////////////////////////
//
// Internal helper functions
//

// Convert a CLSID to a wchar_t string.
void CLSIDtowchar_t(const CLSID& clsid,
                 wchar_t* szCLSID,
                 int length)
{
	assert(length >= CLSID_STRING_SIZE) ;
	// Get CLSID
	LPOLESTR wszCLSID = NULL ;
	HRESULT hr = StringFromCLSID(clsid, &wszCLSID) ;
	assert(SUCCEEDED(hr)) ;

	wcscpy_s(szCLSID, length, wszCLSID);

	// Free memory.
	//CoTaskMemFree(szCLSID) ;
}

//
// Delete a key and all of its descendents.
//
LONG recursiveDeleteKey(HKEY hKeyParent,           // Parent of key to delete
                        const wchar_t* lpszKeyChild)  // Key to delete
{
	// Open the child.
	HKEY hKeyChild ;
	LONG lRes = RegOpenKeyEx(hKeyParent, lpszKeyChild, 0,
	                         KEY_ALL_ACCESS, &hKeyChild) ;
	if (lRes != ERROR_SUCCESS)
	{
		return lRes ;
	}

	// Enumerate all of the decendents of this child.
	FILETIME time ;
	wchar_t szBuffer[256];
	DWORD dwSize = 256 ;
	while (RegEnumKeyEx(hKeyChild, 0, szBuffer, &dwSize, NULL,
	                    NULL, NULL, &time) == S_OK)
	{
		// Delete the decendents of this child.
		lRes = recursiveDeleteKey(hKeyChild, szBuffer) ;
		if (lRes != ERROR_SUCCESS)
		{
			// Cleanup before exiting.
			RegCloseKey(hKeyChild) ;
			return lRes;
		}
		dwSize = 256 ;
	}

	// Close the child.
	RegCloseKey(hKeyChild) ;

	// Delete this child.
	return RegDeleteKey(hKeyParent, lpszKeyChild) ;
}

//
// Create a key and set its value.
//   - This helper function was borrowed and modifed from
//     Kraig Brockschmidt's book Inside OLE.
//
BOOL setKeyAndValue(const wchar_t* szKey,
                    const wchar_t* szSubkey,
                    const wchar_t* szValue)
{
	HKEY hKey;
	wchar_t szKeyBuf[1024];

	// Copy keyname into buffer.
	wcscpy_s(szKeyBuf, sizeof szKeyBuf / sizeof(wchar_t), szKey) ;

	// Add subkey name to buffer.
	if (szSubkey != NULL)
	{
		wcscat_s(szKeyBuf, sizeof szKeyBuf / sizeof(wchar_t), L"\\");
		wcscat_s(szKeyBuf, sizeof szKeyBuf / sizeof(wchar_t), szSubkey);
	}

	// Create and open key and subkey.
	long lResult = RegCreateKeyEx(HKEY_CLASSES_ROOT,
	                              szKeyBuf, 
	                              0, NULL, REG_OPTION_NON_VOLATILE,
	                              KEY_ALL_ACCESS, NULL, 
	                              &hKey, NULL) ;
	if (lResult != ERROR_SUCCESS)
	{
		return FALSE ;
	}

	// Set the Value.
	if (szValue != NULL)
	{
		RegSetValueEx(hKey, NULL, 0, REG_SZ, 
		              (BYTE *)szValue, 
		              (wcslen(szValue)+1)*sizeof(wchar_t)) ;
	}

	RegCloseKey(hKey) ;
	return TRUE ;
}
