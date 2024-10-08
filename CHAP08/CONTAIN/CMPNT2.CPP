//
// Cmpnt2.cpp - Component 2
//
#include <iostream>
#include <objbase.h>

#include "Iface.h"
#include "Registry.h"

using namespace std;

void trace(const wchar_t* msg) { cout << "Component 2:\t" << msg << endl ;}

///////////////////////////////////////////////////////////
//
// Global variables
//

// Static variables
static HMODULE g_hModule = NULL ;  // DLL module handle
static long g_cComponents = 0 ;    // Count of active components
static long g_cServerLocks = 0 ;   // Count of locks

// Friendly name of component
const wchar_t g_szFriendlyName[]
	= L"Inside COM, Chapter 8 Example 1, Component 2" ;

// Version-independent ProgID
const wchar_t g_szVerIndProgID[] = L"InsideCOM.Chap08.Ex1.Cmpnt2" ;

// ProgID
const wchar_t g_szProgID[] = L"InsideCOM.Chap08.Ex1.Cmpnt2.1" ;

///////////////////////////////////////////////////////////
//
// Component B
//
class CB : public IY
{
public:
	// IUnknown
	virtual HRESULT __stdcall QueryInterface(const IID& iid, void** ppv) ;			
	virtual ULONG   __stdcall AddRef() ;
	virtual ULONG   __stdcall Release() ;

	// Interface IY
	virtual void __stdcall Fy() { cout << L"Fy" << endl ;}

	// Constructor
	CB() ;

	// Destructor
	~CB() ;

private:
	// Reference count
	long m_cRef ;
} ;

//
// IUnknown implementation
//
HRESULT __stdcall CB::QueryInterface(const IID& iid, void** ppv)
{ 	
	if (iid == IID_IUnknown)
	{
		*ppv = this ;
	}
	else if (iid == IID_IY)
	{
		*ppv = static_cast<IY*>(this) ;
	}
	else
	{
		*ppv = NULL ;
		return E_NOINTERFACE ;
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef() ;
	return S_OK ;
}

ULONG __stdcall CB::AddRef()
{
	return ::InterlockedIncrement(&m_cRef) ;
}

ULONG __stdcall CB::Release() 
{
	if (::InterlockedDecrement(&m_cRef) == 0)
	{
		delete this ;
		return 0 ;
	}
	return m_cRef ;
}

//
// Constructor
//
CB::CB() : m_cRef(1) 
{ 
	::InterlockedIncrement(&g_cComponents) ; 
}

//
// Destructor
//
CB::~CB() 
{ 
	::InterlockedDecrement(&g_cComponents) ; 
	trace(L"Destroy self.") ;
}


///////////////////////////////////////////////////////////
//
// Class factory
//
class CFactory : public IClassFactory
{
public:
	// IUnknown
	virtual HRESULT __stdcall QueryInterface(const IID& iid, void** ppv) ;
	virtual ULONG   __stdcall AddRef() ;
	virtual ULONG   __stdcall Release() ;
	
	// Interface IClassFactory
	virtual HRESULT __stdcall CreateInstance(IUnknown* pUnknownOuter,
	                                         const IID& iid,
	                                         void** ppv) ;
	virtual HRESULT __stdcall LockServer(BOOL bLock) ; 

	// Constructor
	CFactory() : m_cRef(1) {}

	// Destructor
	~CFactory() {}

private:
	long m_cRef ;
} ;

//
// Class factory IUnknown implementation
//
HRESULT __stdcall CFactory::QueryInterface(const IID& iid, void** ppv)
{ 	
	if ((iid == IID_IUnknown) || (iid == IID_IClassFactory))
	{
		*ppv = static_cast<IClassFactory*>(this) ; 
	}
	else
	{
		*ppv = NULL ;
		return E_NOINTERFACE ;
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef() ;
	return S_OK ;
}

ULONG __stdcall CFactory::AddRef()
{
	return ::InterlockedIncrement(&m_cRef) ;
}

ULONG __stdcall CFactory::Release() 
{
	if (::InterlockedDecrement(&m_cRef) == 0)
	{
		delete this ;
		return 0 ;
	}
	return m_cRef ;
}

//
// IClassFactory implementation
//
HRESULT __stdcall CFactory::CreateInstance(IUnknown* pUnknownOuter,
                                           const IID& iid,
                                           void** ppv) 
{
	// Cannot aggregate
	if (pUnknownOuter != NULL)
	{
		return CLASS_E_NOAGGREGATION ;
	}

	// Create component.
	CB* pB = new CB ;
	if (pB == NULL)
	{
		return E_OUTOFMEMORY ;
	}
	// Get the requested interface.
	HRESULT hr = pB->QueryInterface(iid, ppv) ;
	pB->Release() ;
	return hr ;   
}

HRESULT __stdcall CFactory::LockServer(BOOL bLock) 
{
	if (bLock)
	{
		::InterlockedIncrement(&g_cServerLocks) ;
	}
	else
	{
		::InterlockedDecrement(&g_cServerLocks) ;
	}
	return S_OK ;
}


///////////////////////////////////////////////////////////
//
// Exported functions
//

STDAPI DllCanUnloadNow()
{
	if ((g_cComponents == 0) && (g_cServerLocks == 0))
	{
		return S_OK ;
	}
	else
	{
		return S_FALSE ;
	}
}

//
// Get class factory.
//
STDAPI DllGetClassObject(const CLSID& clsid,
                         const IID& iid,
                         void** ppv) 
{
	// Can we create this component?
	if (clsid != CLSID_Component2)
	{
		return CLASS_E_CLASSNOTAVAILABLE ;
	}
	// Create class factory.
	CFactory* pFactory = new CFactory ;
	if (pFactory == NULL)
	{
		return E_OUTOFMEMORY ;
	}
	// Get requested interface.
	HRESULT hr = pFactory->QueryInterface(iid, ppv) ;
	pFactory->Release() ;
	return hr ;	   
}

//
// Server registration
//
STDAPI DllRegisterServer()
{
	return RegisterServer(g_hModule, 
	                      CLSID_Component2, 
	                      g_szFriendlyName,
	                      g_szVerIndProgID,
	                      g_szProgID) ;
}


STDAPI DllUnregisterServer()
{
	return UnregisterServer(CLSID_Component2,
	                        g_szVerIndProgID,
	                        g_szProgID) ;
}


///////////////////////////////////////////////////////////
//
// DLL module information
//
BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD dwReason, 
                      void* lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		g_hModule = hModule ;
	}
	return TRUE ;
}
