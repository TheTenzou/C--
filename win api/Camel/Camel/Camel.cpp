// Camel.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Camel.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
int f = 1;
UINT_PTR Timer;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CAMEL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CAMEL));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CAMEL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CAMEL);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   
   return TRUE;
} 

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_LBUTTONDOWN:
		f = !f;
		InvalidateRect(hWnd, NULL, true);
		break;
//	case WM_RBUTTONDOWN:
//		SetTimer(hWnd, Timer, 10000, NULL);
//		break;
	case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                //DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				SetTimer(hWnd, Timer, 1000, NULL);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_TIMER:
		f = !f;
		InvalidateRect(hWnd, NULL, true);
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
			POINT a[60];
			int t = 0;
			double k = 0.6;
			HBRUSH brush;
			brush = CreateSolidBrush(RGB(205,132,50));
			SelectObject(hdc, brush);

			if (f == 1)
			{
				a[t].x = long(180 * k); a[t].y = long(224 * k); t++;
				a[t].x = long(180 * k); a[t].y = long(184 * k); t++;
				a[t].x = long(220 * k); a[t].y = long(164 * k); t++;
				a[t].x = long(330 * k); a[t].y = long(164 * k); t++;
				a[t].x = long(367 * k); a[t].y = long(124 * k); t++;
				a[t].x = long(367 * k); a[t].y = long(164 * k); t++;
				a[t].x = long(400 * k); a[t].y = long(200 * k); t++;
				a[t].x = long(400 * k); a[t].y = long(288 * k); t++;
				a[t].x = long(510 * k); a[t].y = long(395 * k); t++;
				a[t].x = long(580 * k); a[t].y = long(395 * k); t++;
				a[t].x = long(635 * k); a[t].y = long(270 * k); t++;
				a[t].x = long(700 * k); a[t].y = long(270 * k); t++;
				a[t].x = long(740 * k); a[t].y = long(385 * k); t++;
				a[t].x = long(765 * k); a[t].y = long(385 * k); t++;
				a[t].x = long(815 * k); a[t].y = long(270 * k); t++;
				a[t].x = long(885 * k); a[t].y = long(270 * k); t++;
				a[t].x = long(940 * k); a[t].y = long(450 * k); t++;
				a[t].x = long(970 * k); a[t].y = long(450 * k); t++;
				a[t].x = long(1050 * k); a[t].y = long(550 * k); t++;
				a[t].x = long(1050 * k); a[t].y = long(570 * k); t++;
				a[t].x = long(1035 * k); a[t].y = long(570 * k); t++;
				a[t].x = long(1035 * k); a[t].y = long(555 * k); t++;
				a[t].x = long(970 * k); a[t].y = long(470 * k); t++;
				a[t].x = long(940 * k); a[t].y = long(470 * k); t++;
				a[t].x = long(885 * k); a[t].y = long(590 * k); t++;
				a[t].x = long(860 * k); a[t].y = long(690 * k); t++;
				a[t].x = long(885 * k); a[t].y = long(715 * k); t++;
				a[t].x = long(885 * k); a[t].y = long(765 * k); t++;
				a[t].x = long(860 * k); a[t].y = long(790 * k); t++;
				a[t].x = long(850 * k); a[t].y = long(880 * k); t++;
				a[t].x = long(835 * k); a[t].y = long(880 * k); t++;
				a[t].x = long(835 * k); a[t].y = long(910 * k); t++;
				a[t].x = long(765 * k); a[t].y = long(910 * k); t++;
				a[t].x = long(765 * k); a[t].y = long(880 * k); t++;
				a[t].x = long(800 * k); a[t].y = long(880 * k); t++;
				a[t].x = long(835 * k); a[t].y = long(790 * k); t++;
				a[t].x = long(800 * k); a[t].y = long(765 * k); t++;
				a[t].x = long(800 * k); a[t].y = long(715 * k); t++;
				a[t].x = long(830 * k); a[t].y = long(690 * k); t++;
				a[t].x = long(815 * k); a[t].y = long(600 * k); t++;
				a[t].x = long(635 * k); a[t].y = long(590 * k); t++;
				a[t].x = long(610 * k); a[t].y = long(690 * k); t++;
				a[t].x = long(635 * k); a[t].y = long(715 * k); t++;
				a[t].x = long(635 * k); a[t].y = long(765 * k); t++;
				a[t].x = long(610 * k); a[t].y = long(790 * k); t++;
				a[t].x = long(600 * k); a[t].y = long(880 * k); t++;
				a[t].x = long(585 * k); a[t].y = long(880 * k); t++;
				a[t].x = long(585 * k); a[t].y = long(910 * k); t++;
				a[t].x = long(515 * k); a[t].y = long(910 * k); t++;
				a[t].x = long(515 * k); a[t].y = long(880 * k); t++;
				a[t].x = long(550 * k); a[t].y = long(880 * k); t++;
				a[t].x = long(585 * k); a[t].y = long(790 * k); t++;
				a[t].x = long(550 * k); a[t].y = long(765 * k); t++;
				a[t].x = long(550 * k); a[t].y = long(715 * k); t++;
				a[t].x = long(585 * k); a[t].y = long(690 * k); t++;
				a[t].x = long(560 * k); a[t].y = long(570 * k); t++;
				a[t].x = long(330 * k); a[t].y = long(355 * k); t++;
				a[t].x = long(330 * k); a[t].y = long(290 * k); t++;
				a[t].x = long(290 * k); a[t].y = long(245 * k); t++;
				a[t].x = long(220 * k); a[t].y = long(245 * k); t++;
				Polygon(hdc, a, 60);
			}
			else if (f == 0)
			{
				a[t].x = long(180 * k); a[t].y = long(224 * k); t++;
				a[t].x = long(180 * k); a[t].y = long(184 * k); t++;
				a[t].x = long(220 * k); a[t].y = long(164 * k); t++;
				a[t].x = long(330 * k); a[t].y = long(164 * k); t++;
				a[t].x = long(367 * k); a[t].y = long(124 * k); t++;
				a[t].x = long(367 * k); a[t].y = long(164 * k); t++;
				a[t].x = long(400 * k); a[t].y = long(200 * k); t++;
				a[t].x = long(400 * k); a[t].y = long(288 * k); t++;
				a[t].x = long(510 * k); a[t].y = long(395 * k); t++;
				a[t].x = long(580 * k); a[t].y = long(395 * k); t++;
				a[t].x = long(700 * k); a[t].y = long(290 * k); t++;					//				a[t].x = long(635 * k); a[t].y = long(270 * k); t++;
				a[t].x = long(800 * k); a[t].y = long(290 * k); t++;					//				a[t].x = long(700 * k); a[t].y = long(270 * k); t++;
				a[t].x = long(875 * k); a[t].y = long(360 * k); t++;					//				a[t].x = long(740 * k); a[t].y = long(385 * k); t++;
				a[t].x = long(925 * k); a[t].y = long(395 * k); t++;						//			a[t].x = long(765 * k); a[t].y = long(385 * k); t++;
																								//		a[t].x = long(815 * k); a[t].y = long(270 * k); t++;
																									//	a[t].x = long(885 * k); a[t].y = long(270 * k); t++;
				a[t].x = long(940 * k); a[t].y = long(450 * k); t++;
				a[t].x = long(970 * k); a[t].y = long(450 * k); t++;
				a[t].x = long(1050 * k); a[t].y = long(550 * k); t++;
				a[t].x = long(1050 * k); a[t].y = long(570 * k); t++;
				a[t].x = long(1035 * k); a[t].y = long(570 * k); t++;
				a[t].x = long(1035 * k); a[t].y = long(555 * k); t++;
				a[t].x = long(970 * k); a[t].y = long(470 * k); t++;
				a[t].x = long(940 * k); a[t].y = long(470 * k); t++;
				a[t].x = long(885 * k); a[t].y = long(590 * k); t++;
				a[t].x = long(860 * k); a[t].y = long(690 * k); t++;
				a[t].x = long(885 * k); a[t].y = long(715 * k); t++;
				a[t].x = long(885 * k); a[t].y = long(765 * k); t++;
				a[t].x = long(860 * k); a[t].y = long(790 * k); t++;
				a[t].x = long(850 * k); a[t].y = long(880 * k); t++;
				a[t].x = long(835 * k); a[t].y = long(880 * k); t++;
				a[t].x = long(835 * k); a[t].y = long(910 * k); t++;
				a[t].x = long(765 * k); a[t].y = long(910 * k); t++;
				a[t].x = long(765 * k); a[t].y = long(880 * k); t++;
				a[t].x = long(800 * k); a[t].y = long(880 * k); t++;
				a[t].x = long(835 * k); a[t].y = long(790 * k); t++;
				a[t].x = long(800 * k); a[t].y = long(765 * k); t++;
				a[t].x = long(800 * k); a[t].y = long(715 * k); t++;
				a[t].x = long(830 * k); a[t].y = long(690 * k); t++;
				a[t].x = long(815 * k); a[t].y = long(600 * k); t++;
				a[t].x = long(635 * k); a[t].y = long(590 * k); t++;
				a[t].x = long(610 * k); a[t].y = long(690 * k); t++;
				a[t].x = long(635 * k); a[t].y = long(715 * k); t++;
				a[t].x = long(635 * k); a[t].y = long(765 * k); t++;
				a[t].x = long(610 * k); a[t].y = long(790 * k); t++;
				a[t].x = long(600 * k); a[t].y = long(880 * k); t++;
				a[t].x = long(585 * k); a[t].y = long(880 * k); t++;
				a[t].x = long(585 * k); a[t].y = long(910 * k); t++;
				a[t].x = long(515 * k); a[t].y = long(910 * k); t++;
				a[t].x = long(515 * k); a[t].y = long(880 * k); t++;
				a[t].x = long(550 * k); a[t].y = long(880 * k); t++;
				a[t].x = long(585 * k); a[t].y = long(790 * k); t++;
				a[t].x = long(550 * k); a[t].y = long(765 * k); t++;
				a[t].x = long(550 * k); a[t].y = long(715 * k); t++;
				a[t].x = long(585 * k); a[t].y = long(690 * k); t++;
				a[t].x = long(560 * k); a[t].y = long(570 * k); t++;
				a[t].x = long(330 * k); a[t].y = long(355 * k); t++;
				a[t].x = long(330 * k); a[t].y = long(290 * k); t++;
				a[t].x = long(290 * k); a[t].y = long(245 * k); t++;
				a[t].x = long(220 * k); a[t].y = long(245 * k); t++;
				Polygon(hdc, a, 58);
			}
			

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
