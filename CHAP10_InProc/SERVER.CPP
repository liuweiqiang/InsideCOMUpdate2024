#include "CFactory.h"
#include "Iface.h"
#include "Cmpnt1.h"
#include "Cmpnt2.h"
#include "Cmpnt3.h"

///////////////////////////////////////////////////////////
//
// Server.cpp
//
// This file contains the component server code.
// The FactoryDataArray contains the components that 
// can be served.
//

// Each component derived from CUnknown defines a static function
// for creating the component with the following prototype. 
// HRESULT CreateInstance(IUnknown* pUnknownOuter, 
//                        CUnknown** ppNewComponent) ;
// This function is used to create the component.
//

//
// The following array contains the data used by CFactory
// to create components. Each element in the array contains
// the CLSID, the pointer to the creation function, and the name
// of the component to place in the Registry.
//
CFactoryData g_FactoryDataArray[] =
{
	{&CLSID_Component1, CA::CreateInstance, 
		L"Inside COM, Chapter 10 Example, Component 1", // Friendly Name
		L"InsideCOM.Chap10.Cmpnt1.1",     // ProgID
		L"InsideCOM.Chap10.Cmpnt1",       // Version-independent ProgID
		NULL, 0},	
	{&CLSID_Component2, CB::CreateInstance, 
		L"Inside COM, Chapter 10 Example, Component 2",
		L"InsideCOM.Chap10.Cmpnt2.1",
		L"InsideCOM.Chap10.Cmpnt2",
		NULL, 0},	
	{&CLSID_Component3, CC::CreateInstance, 
		L"Inside COM, Chapter 10 Example, Component 3",
		L"InsideCOM.Chap10.Cmpnt3.1",
		L"InsideCOM.Chap10.Cmpnt3",
		NULL, 0}
} ;
int g_cFactoryDataEntries
	= sizeof(g_FactoryDataArray) / sizeof(CFactoryData) ;
