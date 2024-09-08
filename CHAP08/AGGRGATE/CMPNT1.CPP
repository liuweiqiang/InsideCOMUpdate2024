//
// Cmpnt1.cpp - Component 1
//
//   Interesting bits of code marked with @N.
//
#include <iostream>
#include <objbase.h>

#include "Iface.h"
#include "Registry.h"

using namespace std;

// Trace function
void trace(const wchar_t* msg) { cout << L"Component 1:\t" << msg << endl ;}

///////////////////////////////////////////////////////////
//
// Global variables
//

// Static variables
static HMODULE g_hModule = NULL ;   // DLL module handle
static long g_cComponents = 0 ;     // Count of active components
static long g_cServerLocks = 0 ;    // Count of locks

// Friendly name of component
const wchar_t g_szFriendlyName[]
	= L"Inside COM, Chapter 8 Example 2, Component 1" ;

// Version-independent ProgID
const wchar_t g_szVerIndProgID[] = L"InsideCOM.Chap08.Ex2.Cmpnt1" ;

// ProgID
const wchar_t g_szProgID[] = L"InsideCOM.Chap08.Ex2.Cmpnt1.1" ;

///////////////////////////////////////////////////////////
//
// Component A
//
class CA : public IX
        // public IY @N
{
public:
	// IUnknown
	virtual HRESULT __stdcall QueryInterface(const IID& iid, void** ppv) ;
	virtual ULONG   __stdcall AddRef() ;
	virtual ULONG   __stdcall Release() ;
	
	// Interface IX
	virtual void __stdcall Fx() { cout << "Fx" << endl ;}
	
	/* @N Component1 aggregates instead of implementing interface IY.
	// Interface IY
	virtual void __stdcall Fy() { m_pIY->Fy() ;}
	*/
	
	// Constructor
	CA() ;
	
	// Destructor
	~CA() ;
	
	// Initialization function called by the class factory
	// to create the contained component
	HRESULT __stdcall Init() ;  // @N

private:
	// Reference count
	long m_cRef ;
	
	// Pointer to the aggregated component's IY interface
	// (We do not have to retain an IY pointer. However, we
	// can use it in QueryInterface.)
	IY* m_pIY ;                 // @N
	
	// Pointer to inner component's IUnknown
	IUnknown* m_pUnknownInner ; // point to NondelegatingIunknown
	// used once in Init, then in queryInterface
} ;


//
// Constructor
//
CA::CA() 
: m_cRef(1), 
  m_pUnknownInner(NULL) //@N
{ 
	::InterlockedIncrement(&g_cComponents) ; 
}

//
// Destructor
//
CA::~CA() 
{ 
	::InterlockedDecrement(&g_cComponents) ; 
	trace(L"Destroy self.") ;

	// Prevent recursive destruction on next AddRef/Release pair.
	m_cRef = 2;            
	// set to 1 is no good because m_pIY->Release() will make come
	// back here;
	
	// Counter the pUnknownOuter->Release in the Init method.
	//IUnknown* pUnknownOuter = this ;
	//pUnknownOuter->AddRef() ;			// because added a reference

	// Properly release the pointer; there might be per-interface
	// reference counts.
	if (m_pIY != NULL)
	{
		m_pIY->Release() ;
	}

	// Release contained component.
	if (m_pUnknownInner != NULL)   // @N
	{
		m_pUnknownInner->Release() ;
	}
}

// Initialize the component by creating the contained component.
HRESULT __stdcall CA::Init()
{
	// Get the pointer to the outer unknown.
	// Since this component is not aggregated, the outer unknown
	// is the same as the this pointer. 
	IUnknown* pUnknownOuter = this ;
	
	trace(L"Create inner component.") ;
	HRESULT hr =
		::CoCreateInstance(CLSID_Component2, 		 
		                   pUnknownOuter, // Outer component's IUnknown @N
		                   CLSCTX_INPROC_SERVER,
		                   IID_IUnknown,  // IUnknown when aggregating  @N
		                   (void**)&m_pUnknownInner) ; 
	if (FAILED(hr))
	{
		trace(L"Could not create contained component.") ;
		return E_FAIL ;
	}
	
	// This call will increment the reference count on the outer component.
	// because it has a member of m_IUnknownOuter
	
	trace(L"Get the IY interface from the inner component.") ;
	hr = m_pUnknownInner->QueryInterface(IID_IY, (void**)&m_pIY) ; //@N
	if (FAILED(hr))
	{
		trace(L"Inner component does not support interface IY.") ;
		m_pUnknownInner->Release() ;
		m_pUnknownInner = NULL ;
		m_pIY = NULL ; // Just to be safe
		return E_FAIL ;
	}
	// do not add a ref because constructor set it to 1
	
	// We need to release the reference count added to the
	// outer component in the above call.  So call Release
	// on the pointer you passed to CoCreateInstance.
	// without this call, we'll not go into the destructor to delete m_pIY
	pUnknownOuter->Release() ; //@N
	return S_OK ;
}

//
// IUnknown implementation
//
HRESULT __stdcall CA::QueryInterface(const IID& iid, void** ppv)
{ 	
	if (iid == IID_IUnknown)
	{
		*ppv = static_cast<IUnknown*>(this) ; 
	}
	else if (iid == IID_IX)
	{
		*ppv = static_cast<IX*>(this) ;
	}
	else if (iid == IID_IY)
	{
		trace(L"Return inner component's IY interface.") ;
#if 1
		// You can query for the interface.
		return m_pUnknownInner->QueryInterface(iid,ppv) ; //@N
#else
		// Or you can return a cached pointer.
		*ppv = m_pIY ;   //@N
		// Fall through so it will get AddRef'ed
#endif
	}
	else
	{
		*ppv = NULL ;
		return E_NOINTERFACE ;
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef() ;
	return S_OK ;
}

ULONG __stdcall CA::AddRef()
{
  	return ::InterlockedIncrement(&m_cRef) ;
}

ULONG __stdcall CA::Release() 
{
	if (::InterlockedDecrement(&m_cRef) == 0)
	{
		delete this ;
		return 0 ;
	}
	return m_cRef ;
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
HRESULT __stdcall CFactory::QueryInterface(REFIID iid, void** ppv)
{ 	
	IUnknown* pI ;
	if ((iid == IID_IUnknown) || (iid == IID_IClassFactory))
	{
		pI = static_cast<IClassFactory*>(this) ; 
	}
	else
	{
		*ppv = NULL ;
		return E_NOINTERFACE ;
	}
	pI->AddRef() ;
	*ppv = pI ;
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
	CA* pA = new CA ;
	if (pA == NULL)
	{
		return E_OUTOFMEMORY ;
	}
	
	// Initialize the component. @N
	HRESULT hr = pA->Init() ;
	if (FAILED(hr))
	{
		// Initialization failed. Delete component.
		pA->Release() ;
		return hr ;
	}
	
	// Get the requested interface.
	hr = pA->QueryInterface(iid, ppv) ;
	pA->Release() ;
	return hr ;   
}

// LockServer
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
	if (clsid != CLSID_Component1)
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
	                      CLSID_Component1, 
	                      g_szFriendlyName,
	                      g_szVerIndProgID,
	                      g_szProgID) ;
}


STDAPI DllUnregisterServer()
{
	return UnregisterServer(CLSID_Component1,
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
