#include <windows.h>
#include <stdlib.h>

#include "../CHAP10_InProc/CUNKNOWN.H"
#include "../CHAP10_InProc/CFactory.h"
#include "../CHAP10_InProc/UTIL.H"

#include <iostream>
using namespace std;


///////////////////////////////////////////////////////////
//
// Outproc.cpp
//   - the component server
//   - window not working, so run it in a shell supporting "cat":
//               Server.exe "Embedding" | cat 
//   -   to pipe the console output 
HWND g_hWndListBox = NULL ;

BOOL InitWindow(int nCmdShow) ;
extern "C" LONG APIENTRY MainWndProc(HWND hWnd,
                                     UINT message,
                                     UINT wParam,
                                     LONG lParam) ;


//
// WinMain procedure
//
extern "C" int WINAPI WinMain(HINSTANCE hInstance, 
                              HINSTANCE hPrevInstance,
                              LPSTR lpCmdLine, 
                              int nCmdShow)
{
	// Controls whether UI is shown or not
	BOOL bUI = TRUE ;

	// If TRUE, don't loop.
	BOOL bExit = FALSE ;

	// Initialize the COM Library.
	HRESULT hr = CoInitialize(NULL) ;
	if (FAILED(hr))
	{

		return 0 ;
	}
   
	cout << "cmd arg: " << lpCmdLine << endl;
   
	// Get Thread ID.
	CFactory::s_dwThreadID = ::GetCurrentThreadId() ;
	CFactory::s_hModule = hInstance ;

	// Read the command line.
	const char szTokens[] = "-/" ;
	char* nextToken;
	// char* szToken = strtok(lpCmdLine, szTokens) ; 
	char* szToken = strtok_s(lpCmdLine, szTokens, &nextToken);
	while (szToken != NULL)
	{
		if (_stricmp(szToken, "UnregServer") == 0)
		{
			CFactory::UnregisterAll() ;
			// We are done, so exit.
			bExit = TRUE ;
			bUI = FALSE ;
		}
		else if (_stricmp(szToken, "RegServer") == 0)
		{
			CFactory::RegisterAll() ;
			// We are done, so exit.
			bExit = TRUE ;
			bUI = FALSE ;
		}
		else if (_stricmp(szToken, "Embedding") == 0)
		{
			// Don't display a window if we are embedded.
			bUI = FALSE ;
			break ;
		}
		// szToken = strtok(NULL, szTokens) ;
		szToken = strtok_s(NULL, szTokens, &nextToken);
	}

	// If the user started us, then show UI.
	if (bUI)
	{
		if (!InitWindow(nCmdShow))
		{
			// Exit since we can't show UI.
			bExit = TRUE ;
		}
		else
		{
			::InterlockedIncrement(&CFactory::s_cServerLocks) ;
		}
	}

	if (!bExit)
	{
		// Register all of the class factories.
		CFactory::StartFactories() ;

		// Wait for shutdown.
		MSG msg ;
		while (::GetMessage(&msg, 0, 0, 0))
		{
			::DispatchMessage(&msg) ;
		}

		// Unregister the class factories.
		CFactory::StopFactories() ;
	}

	// Uninitialize the COM Library.
	CoUninitialize() ;
	return 0 ;
}


//
// Initialize window
//
BOOL InitWindow(int nCmdShow) 
{
	// Fill in window class structure with parameters
	// that describe the main window.
	WNDCLASS wcListview ;
	wcListview.style = 0 ;                     
	wcListview.lpfnWndProc = (WNDPROC)MainWndProc ; 
	wcListview.cbClsExtra = 0 ;              
	wcListview.cbWndExtra = 0 ;              
	wcListview.hInstance = CFactory::s_hModule ;
	wcListview.hIcon = ::LoadIcon(CFactory::s_hModule,
	                              MAKEINTRESOURCE(IDC_ICON)) ;
	wcListview.hCursor = ::LoadCursor(NULL, IDC_ARROW) ;
	wcListview.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
	wcListview.lpszMenuName = NULL ;  
	wcListview.lpszClassName = L"MyServerWinClass" ;

	BOOL bResult = ::RegisterClass(&wcListview) ;
	if (!bResult)
	{
		return bResult ;
	}

	HWND hWndMain ;

	hWndMain = ::CreateWindow(
		L"MyServerWinClass",
		L"Component Server", 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,               
		NULL,               
		CFactory::s_hModule,          
		NULL) ;

	// If window could not be created, return "failure".
	if (!hWndMain)
	{
		return FALSE ;
	}

	// Make the window visible; update its client area;
	// and return "success".
	::ShowWindow(hWndMain, nCmdShow) ;
	::UpdateWindow(hWndMain) ;
	return TRUE ;
}

//
// Main window procedure
//
extern "C" LONG APIENTRY MainWndProc(
	HWND hWnd,                // window handle
	UINT message,             // type of message
	UINT wParam,              // additional information
	LONG lParam)              // additional information
{
	DWORD dwStyle ;

	switch (message) 
	{
	case WM_CREATE:
		{
			// Get size of main window
			CREATESTRUCT* pcs = (CREATESTRUCT*) lParam ;

			// Create a listbox for output.
			g_hWndListBox = ::CreateWindow(
				L"LISTBOX",
				NULL, 
				WS_CHILD | WS_VISIBLE | LBS_USETABSTOPS
					| WS_VSCROLL | LBS_NOINTEGRALHEIGHT,
				0, 0, pcs->cx, pcs->cy,
				hWnd,               
				NULL,               
				CFactory::s_hModule,          
				NULL) ;
			if (g_hWndListBox  == NULL)
			{
				// Listbox not created.
				::MessageBox(NULL,
				             L"Listbox not created!",
				             NULL,
				             MB_OK) ;
				return -1 ;
			}
		}
		break ;

	case WM_SIZE:
		::MoveWindow(g_hWndListBox, 0, 0,
			LOWORD(lParam), HIWORD(lParam), TRUE) ;
		break;

	case WM_DESTROY:          // message: window being destroyed
		if (CFactory::CanUnloadNow() == S_OK)
		{
			// Only post the quit message, if there is
			// no one using the program.
			::PostQuitMessage(0) ;
		}
		break ;

	case WM_CLOSE:
		// Decrement the lock count.
		::InterlockedDecrement(&CFactory::s_cServerLocks) ;

		// The list box is going away.
		g_hWndListBox = NULL ;

		//Fall through 
	default:
		return (DefWindowProc(hWnd, message, wParam, lParam)) ;
	}
	return 0 ;
}
