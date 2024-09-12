//
// Cmpnt2.cpp - Component 2
//
#include <objbase.h>
#include <iostream>
#include <sstream>

#include "Iface.h"
#include "Util.h"
#include "CUnknown.h"
#include "Cmpnt2.h"

using namespace std;

static inline void trace(const wchar_t* msg)
	{ Util::Trace(L"Component 2", msg, S_OK) ;}
static inline void trace(const wchar_t* msg, HRESULT hr)
	{ Util::Trace(L"Component 2", msg, hr) ;}

///////////////////////////////////////////////////////////
//
// Interface IY
//

HRESULT __stdcall CB::FyCount(long* sizeArray)
{
	*sizeArray = m_sizeArray ;
	return S_OK ;
}

HRESULT __stdcall CB::FyArrayIn(long sizeIn, long arrayIn[])
{
	// Display the array passed in.
	wostringstream sout ;
	sout << L"FyArrayIn received " 
	     << sizeIn
	     << L" elements: " ;
	for (int i = 0 ; i < sizeIn ; i++)
	{
		sout << " " << arrayIn[i] ;
	}
	sout << L"." << ends ;
	trace(sout.str().c_str()) ;

	// Delete the internal array.
	delete [] m_array ;

	// Create a new array
	m_array = new long[sizeIn] ;
	m_sizeArray = sizeIn ;

	// Copy the array passed in into the internal array.
	for (int i = 0 ; i < sizeIn ; i++)
	{
		m_array[i] = arrayIn[i];
	}

	return S_OK ;
}

HRESULT __stdcall CB::FyArrayOut(long* psizeInOut, long arrayOut[])
{
	if (*psizeInOut < m_sizeArray )
	{
		return E_OUTOFMEMORY ;
	}

	// Copy the array to the out parameter.
	for (int i = 0 ; i < m_sizeArray ; i++)
	{
		arrayOut[i] = m_array[i] ;
	}

	// Return the size of the array in the in/out parameter
	*psizeInOut = m_sizeArray ;

	return S_OK ;
}


//
// Constructor
//
CB::CB(IUnknown* pUnknownOuter)
: CUnknown(pUnknownOuter),
  m_pUnknownInner(NULL),
  m_pIZ(NULL)
{
	m_sizeArray = 0 ;
	m_array = NULL ;
}

//
// Destructor
//
CB::~CB()
{
	if ( m_array != NULL)
	{
		delete [] m_array ;
	}

	trace(L"Destroy self.") ;
}

//
// NondelegatingQueryInterface implementation
//
HRESULT __stdcall CB::NondelegatingQueryInterface(const IID& iid,
                                                  void** ppv)
{ 	
	if (iid == IID_IY)
	{
		return FinishQI(static_cast<IY*>(this), ppv) ;
	}
	else if (iid == IID_IZ)
	{
		return m_pUnknownInner->QueryInterface(iid, ppv) ;
	}
	else
	{
		return CUnknown::NondelegatingQueryInterface(iid, ppv) ;
	}
}


//
// Initialize the component by creating the contained component.
//
HRESULT CB::Init()
{
	trace(L"Create Component 3, which is aggregated.") ;
	HRESULT hr = CoCreateInstance(CLSID_Component3,
	                              GetOuterUnknown(),
	                              CLSCTX_INPROC_SERVER,
	                              //CLSCTX_ALL, //@Multi
	                              IID_IUnknown,
	                              (void**)&m_pUnknownInner) ;
	if (FAILED(hr))
	{
		trace(L"Could not create inner component.", hr) ;
		return E_FAIL ;
	}

	trace(L"Get pointer to interface IZ to cache.") ;
	hr = m_pUnknownInner->QueryInterface(IID_IZ, (void**)&m_pIZ) ;
	if (FAILED(hr))
	{
		trace(L"Inner component does not support IZ.", hr) ;
		m_pUnknownInner->Release() ;
		m_pUnknownInner = NULL ;
		return E_FAIL ;
	}

	// Decrement the reference count caused by the QI call.
	trace(L"Got IZ interface pointer. Release reference.") ;
	GetOuterUnknown()->Release() ;

	return S_OK ;
}

//
// FinalRelease - called by Release before it deletes the component
//
void CB::FinalRelease()
{
	// Call base class to incremement m_cRef to prevent recusion.
	CUnknown::FinalRelease() ;

	// Counter the GetOuterUnknown()->Release in the Init method.
	GetOuterUnknown()->AddRef() ;

	// Properly release the pointer; there may be per-interface
	// reference counts.
	m_pIZ->Release() ;

	// Release the aggregated component.
	if (m_pUnknownInner != NULL)
	{
		m_pUnknownInner->Release() ;
	}
}


///////////////////////////////////////////////////////////
//
// Creation function used by CFactory
//
HRESULT CB::CreateInstance(IUnknown* pUnknownOuter,
                           CUnknown** ppNewComponent)
{
	*ppNewComponent = new CB(pUnknownOuter) ;
	return S_OK ;
}
