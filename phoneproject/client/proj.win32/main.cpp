#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"

USING_NS_CC;

// uncomment below line, open debug console
//#define USE_WIN32_CONSOLE

char* g_SimulateFileName;

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
#else
    freopen("out.txt", "w", stdout);
    freopen("err.txt", "w", stderr);
#endif

	int nWidth = 1136;
	int nHeight = 640;
	float fFactor = 0.8f;
	int nShowFPS = 0;

	wchar_t szWChar[1024];

	g_SimulateFileName = new char[1024];

	swscanf( lpCmdLine, L"%d %d %f %s", &nWidth, &nHeight, &fFactor, &szWChar);
	int size = wcslen(szWChar);
	sprintf(g_SimulateFileName, "%s", cc_utf16_to_utf8((unsigned short*)szWChar, size, NULL, NULL));

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setFrameSize(nWidth, nHeight);

	eglView->setFrameZoomFactor(fFactor);

	// ÊÇ·ñÏÔÊ¾fps
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->setDisplayStats((nShowFPS == 1));

    int ret = CCApplication::sharedApplication()->run();

#ifdef USE_WIN32_CONSOLE
    FreeConsole();
#endif

    return ret;
}
