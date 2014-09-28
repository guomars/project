#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include <string>

USING_NS_CC;

extern LRESULT my_win_proc(UINT message, WPARAM wParam, LPARAM lParam, BOOL* pProcessed);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	wchar_t szWChar[1024];
	char szChar[1024];
	if (std::wcslen(lpCmdLine) != 0) {
		swscanf(lpCmdLine, L"%s", &szWChar);
		sprintf(szChar, "%s", cc_utf16_to_utf8((unsigned short*)szWChar, std::wcslen(lpCmdLine), NULL, NULL));
		g_plistFileName = (char*)szChar;
	}
	
    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	eglView->setWndProc(my_win_proc);
    eglView->setViewName("PListViewer");
	
	if (g_plistFileName.size() > 0) {
		eglView->setFrameSize(768, 1024);
		eglView->setFrameZoomFactor(0.8f);
	} else {
		eglView->setFrameSize(1024, 1024);
	}
    return CCApplication::sharedApplication()->run();

}
