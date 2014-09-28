#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"

USING_NS_CC;

char* g_SimulateFileName;


// uncomment below line, open debug console
// #define USE_WIN32_CONSOLE

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef USE_WIN32_CONSOLE
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
#endif

	int nWidth = 768 * 2;
	int nHeight = 1024 * 2;
	float fFactor = 0.4f;

	wchar_t szWChar[1024];

	g_SimulateFileName = new char[1024];

	swscanf( lpCmdLine, L"%d %d %f %s", &nWidth, &nHeight, &fFactor, &szWChar);
	int size = wcslen(szWChar);
	sprintf(g_SimulateFileName, "%s", cc_utf16_to_utf8((unsigned short*)szWChar, size, NULL, NULL));

	// create the application instance
	AppDelegate app;
	CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	eglView->setFrameSize(nWidth, nHeight);

	// The resolution of ipad3 is very large. In general, PC's resolution is smaller than it.
	// So we need to invoke 'setFrameZoomFactor'(only valid on desktop(win32, mac, linux)) to make the window smaller.
	eglView->setFrameZoomFactor(fFactor);

    int ret = CCApplication::sharedApplication()->run();

#ifdef USE_WIN32_CONSOLE
    FreeConsole();
#endif

    return ret;
}
