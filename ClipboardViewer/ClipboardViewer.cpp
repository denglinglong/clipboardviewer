// ClipboardViewer.cpp : main source file for ClipboardViewer.exe
//

#include "stdafx.h"

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>

#include "resource.h"

#include "aboutdlg.h"
#include "MainDlg.h"

CAppModule _Module;

int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMainDlg dlgMain;

	if(dlgMain.Create(NULL) == NULL)
	{
		ATLTRACE(_T("Main dialog creation failed!\n"));
		return 0;
	}

	dlgMain.ShowWindow(nCmdShow);

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	HRESULT hRes = ::CoInitialize(NULL);
	// If you are running on NT 4.0 or higher you can use the following call instead to 
	// make the EXE free threaded. This means that calls come in on a random RPC thread.
	//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	HMODULE hInstRichEdit = ::LoadLibrary(CRichEditCtrl::GetLibraryName());

	AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls
	GdiplusStartupInput		m_gdiplusStartupInput;
	ULONG_PTR				m_gdiplusToken;
	Status sta = GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);		//GDI+��ʼ��


	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	int nRet = Run(lpstrCmdLine, nCmdShow);

	GdiplusShutdown(m_gdiplusToken);

	if( hInstRichEdit != NULL )
	{
		FreeLibrary( hInstRichEdit );
	}

	_Module.Term();
	::CoUninitialize();

	return nRet;
}
