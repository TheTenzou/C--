// WindowsProject1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

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
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(RGB(230, 230, 230));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
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
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...

			HPEN WihtPen;
			HBRUSH YelowBrush;
			HBRUSH BlackBrush;
			HBRUSH WhihtBrush;
			
			WihtPen = CreatePen(PS_SOLID,0.5,RGB(204, 204, 204));
			SelectObject(hdc, WihtPen);

			YelowBrush = CreateSolidBrush(RGB(244, 202, 37));
			SelectObject(hdc, YelowBrush);

			BlackBrush = CreateSolidBrush(RGB(0, 0, 0));
			
			int k = 20;
			Rectangle(hdc, 1*k, 1*k, 26*k, 34*k);

			//////////////////////
			HPEN GrayPen;
			HBRUSH GrayBrush;

			GrayPen = CreatePen(PS_SOLID, 0.5, RGB(166, 166, 166));
			SelectObject(hdc, GrayPen);

			GrayBrush = CreateSolidBrush(RGB(166, 166, 166));
			SelectObject(hdc, GrayBrush);

			Rectangle(hdc, 8 * k, 11 * k, 9 * k, 12 * k);
			Rectangle(hdc, 17 * k, 11 * k, 18 * k, 12 * k);
			Rectangle(hdc, 8 * k, 12 * k, 18 * k, 13 * k);
			Rectangle(hdc, 6 * k, 13 * k, 20 * k, 17 * k);
			Rectangle(hdc, 4 * k, 17 * k, 22 * k, 22 * k);
			Rectangle(hdc, 3 * k, 22 * k, 23 * k, 27 * k);
			Rectangle(hdc, 4 * k, 27 * k, 21 * k, 29 * k);
			Rectangle(hdc, 6 * k, 29 * k, 20 * k, 32 * k);

			//////////////////////////

			HPEN bluePen;
			HBRUSH blueBrush;

			bluePen = CreatePen(PS_SOLID, 0.5, RGB(51, 102, 204));
			SelectObject(hdc, bluePen);

			blueBrush = CreateSolidBrush(RGB(51, 102, 204));
			SelectObject(hdc, blueBrush);

			Rectangle(hdc, 8 * k, 4 * k, 20 * k, 8 * k);
			Rectangle(hdc, 5 * k, 8 * k, 24 * k, 11 * k);
			Rectangle(hdc, 20 * k, 6 * k, 22 * k, 8 * k);

			HPEN blue2Pen;
			HBRUSH blue2Brush;

			blue2Pen = CreatePen(PS_SOLID, 0.5, RGB(128, 179, 255));
			SelectObject(hdc, blue2Pen);

			blue2Brush = CreateSolidBrush(RGB(128, 179, 255));
			SelectObject(hdc, blue2Brush);

			Rectangle(hdc, 10 * k, 4 * k, 11 * k, 5 * k);
			Rectangle(hdc, 16 * k, 4 * k, 17 * k, 5 * k);

			Rectangle(hdc, 8 * k, 5 * k, 10 * k, 6 * k);
			Rectangle(hdc, 13 * k, 5 * k, 14 * k, 6 * k);
			Rectangle(hdc, 17 * k, 5 * k, 18 * k, 6 * k);

			Rectangle(hdc, 7 * k, 6 * k, 9 * k, 7 * k);
			Rectangle(hdc, 12 * k, 6 * k, 14 * k, 8 * k);
			Rectangle(hdc, 18 * k, 6 * k, 19 * k, 8 * k);

			Rectangle(hdc, 6 * k, 7 * k, 8 * k, 8 * k);
			
			Rectangle(hdc, 5 * k, 8 * k, 7 * k, 9 * k);
			Rectangle(hdc, 11 * k, 8 * k, 13 * k, 9 * k);
			Rectangle(hdc, 19 * k, 8 * k, 20 * k, 10 * k);

			Rectangle(hdc, 4 * k, 9 * k, 6 * k, 10 * k);
			Rectangle(hdc, 10 * k, 9 * k, 13 * k, 10 * k);

			Rectangle(hdc, 3 * k, 10 * k, 5 * k, 11 * k);

			////////////// eyes and whight

			WhihtBrush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, WhihtBrush);

			WihtPen = CreatePen(PS_SOLID, 0.5, RGB(255, 255, 255));
			SelectObject(hdc, WihtPen);

			Rectangle(hdc, 7 * k, 14 * k, 10 * k, 17 * k);

			Rectangle(hdc, 16 * k, 14 * k, 19 * k, 17 * k);

			Rectangle(hdc, 11 * k, 18 * k, 14 * k, 19 * k);
			Rectangle(hdc, 9 * k, 19 * k, 14 * k, 20 * k);
			Rectangle(hdc, 8 * k, 20 * k, 14 * k, 21 * k);
			Rectangle(hdc, 7 * k, 21 * k, 14 * k, 22 * k);
			Rectangle(hdc, 6 * k, 22 * k, 15 * k, 23 * k);
			Rectangle(hdc, 6 * k, 23 * k, 17 * k, 24 * k);

			Rectangle(hdc, 4 * k, 24 * k, 8 * k, 25 * k);
			Rectangle(hdc, 9 * k, 24 * k, 12 * k, 25 * k);
			Rectangle(hdc, 13 * k, 24 * k, 16 * k, 25 * k);

			Rectangle(hdc, 5 * k, 25 * k, 7 * k, 26 * k);

			Rectangle(hdc, 8 * k, 25 * k, 9 * k, 26 * k);

			Rectangle(hdc, 10 * k, 25 * k, 11 * k, 26 * k);

			Rectangle(hdc, 12 * k, 25 * k, 13 * k, 26 * k);

			Rectangle(hdc, 14 * k, 25 * k, 15 * k, 26 * k);

			Rectangle(hdc, 16 * k, 25 * k, 17 * k, 26 * k);

			Rectangle(hdc, 18* k, 25 * k, 21 * k, 26 * k);

			Rectangle(hdc, 5 * k, 26 * k, 21 * k, 30 * k);

			Rectangle(hdc, 11 * k, 30 * k, 15 * k, 31 * k);

			/////////////

			WihtPen = CreatePen(PS_SOLID, 0.5, RGB(204, 204, 204));
			SelectObject(hdc, WihtPen);
			

			SelectObject(hdc, BlackBrush);
			Rectangle(hdc, 13 * k, 2 * k, 14 * k, 3 * k);	//line 2 black
			Rectangle(hdc, 14 * k, 2 * k, 15 * k, 3 * k);

			Rectangle(hdc, 10 * k, 3 * k, 11 * k, 4 * k);	//line 3 black
			Rectangle(hdc, 11 * k, 3 * k, 12 * k, 4 * k);
			Rectangle(hdc, 12 * k, 3 * k, 13 * k, 4 * k);
			Rectangle(hdc, 13 * k, 3 * k, 14 * k, 4 * k);
			Rectangle(hdc, 14 * k, 3 * k, 15 * k, 4 * k);
			Rectangle(hdc, 15 * k, 3 * k, 16 * k, 4 * k);
			Rectangle(hdc, 16 * k, 3 * k, 17 * k, 4 * k);
			Rectangle(hdc, 17 * k, 3 * k, 18 * k, 4 * k);

			Rectangle(hdc, 8 * k, 4 * k, 9 * k, 5 * k);		//line 4 black
			Rectangle(hdc, 9 * k, 4 * k, 10 * k, 5 * k);
			Rectangle(hdc, 18 * k, 4 * k, 19 * k, 5 * k);
			Rectangle(hdc, 19 * k, 4 * k, 20 * k, 5 * k);

			Rectangle(hdc, 12 * k, 4 * k, 13 * k, 5 * k);
			Rectangle(hdc, 15 * k, 4 * k, 16 * k, 5 * k);

			Rectangle(hdc, 7 * k, 5 * k, 8 * k, 6 * k);		//line 5 black
			Rectangle(hdc, 20 * k, 5 * k, 21 * k, 6 * k);

			Rectangle(hdc, 11 * k, 5 * k, 12 * k, 6 * k);
			Rectangle(hdc, 16 * k, 5 * k, 17 * k, 6 * k);

			Rectangle(hdc, 6 * k, 6 * k, 7 * k, 7 * k);		//line 6 black
			Rectangle(hdc, 21 * k, 6 * k, 22 * k, 7 * k);

			Rectangle(hdc, 10 * k, 6 * k, 11 * k, 7 * k);
			Rectangle(hdc, 17 * k, 6 * k, 18 * k, 7 * k);

			Rectangle(hdc, 5 * k, 7 * k, 6 * k, 8 * k);		//line 7 black
			Rectangle(hdc, 22 * k, 7 * k, 23 * k, 8 * k);

			Rectangle(hdc, 10 * k, 7 * k, 11 * k, 8 * k);
			Rectangle(hdc, 17 * k, 7 * k, 18 * k, 8 * k);

			Rectangle(hdc, 4 * k, 8 * k, 5 * k, 9 * k);		//line 8 black
			Rectangle(hdc, 23 * k, 8 * k, 24 * k, 9 * k);

			Rectangle(hdc, 9 * k, 8 * k, 10 * k, 9 * k);
			Rectangle(hdc, 18 * k, 8 * k, 19 * k, 9 * k);

			Rectangle(hdc, 4 * k, 9 * k, 5 * k, 10 * k);	//line 9 black
			Rectangle(hdc, 23 * k, 9 * k, 24 * k, 10 * k);

			Rectangle(hdc, 9 * k, 9 * k, 10 * k, 10 * k);
			Rectangle(hdc, 18 * k, 9 * k, 19 * k, 10 * k);	

			Rectangle(hdc, 3 * k, 10 * k, 4 * k, 11 * k);	//line 10 black

			Rectangle(hdc, 6 * k, 10 * k, 7 * k, 11 * k);
			Rectangle(hdc, 7 * k, 10 * k, 8 * k, 11 * k);
			Rectangle(hdc, 8 * k, 10 * k, 9 * k, 11 * k);
			Rectangle(hdc, 9 * k, 10 * k, 10 * k, 11 * k);
			Rectangle(hdc, 10 * k, 10 * k, 11 * k, 11 * k);
			Rectangle(hdc, 11 * k, 10 * k, 12 * k, 11 * k);
			Rectangle(hdc, 12 * k, 10 * k, 13 * k, 11 * k);
			Rectangle(hdc, 13 * k, 10 * k, 14 * k, 11 * k);
			Rectangle(hdc, 14 * k, 10 * k, 15 * k, 11 * k);
			Rectangle(hdc, 15 * k, 10 * k, 16 * k, 11 * k);
			Rectangle(hdc, 16 * k, 10 * k, 17 * k, 11 * k);
			Rectangle(hdc, 17 * k, 10 * k, 18 * k, 11 * k);
			Rectangle(hdc, 18 * k, 10 * k, 19 * k, 11 * k);
			Rectangle(hdc, 19 * k, 10 * k, 20 * k, 11 * k);
			Rectangle(hdc, 20 * k, 10 * k, 21 * k, 11 * k);

			Rectangle(hdc, 24 * k, 10 * k, 25 * k, 11 * k);

			Rectangle(hdc, 3 * k, 11 * k, 4 * k, 12 * k);	//line 11 black
			Rectangle(hdc, 4 * k, 11 * k, 5 * k, 12 * k);
			Rectangle(hdc, 5 * k, 11 * k, 6 * k, 12 * k);

			Rectangle(hdc, 7 * k, 11 * k, 8 * k, 12 * k);
			Rectangle(hdc, 9 * k, 11 * k, 10 * k, 12 * k);

			Rectangle(hdc, 14 * k, 11 * k, 15 * k, 12 * k);

			Rectangle(hdc, 16 * k, 11 * k, 17 * k, 12 * k);
			Rectangle(hdc, 18 * k, 11 * k, 19 * k, 12 * k);

			Rectangle(hdc, 21 * k, 11 * k, 22 * k, 12 * k);
			Rectangle(hdc, 22 * k, 11 * k, 23 * k, 12 * k);
			Rectangle(hdc, 23 * k, 11 * k, 24 * k, 12 * k);
			Rectangle(hdc, 24 * k, 11 * k, 25 * k, 12 * k);

			Rectangle(hdc, 3 * k, 12 * k, 4 * k, 13 * k);	//line 12 black

			Rectangle(hdc, 7 * k, 12 * k, 8 * k, 13 * k);

			Rectangle(hdc, 10 * k, 12 * k, 11 * k, 13 * k);
			Rectangle(hdc, 11 * k, 12 * k, 12 * k, 13 * k);
			Rectangle(hdc, 12 * k, 12 * k, 13 * k, 13 * k);
			Rectangle(hdc, 13 * k, 12 * k, 14 * k, 13 * k);
			Rectangle(hdc, 14 * k, 12 * k, 15 * k, 13 * k);
			Rectangle(hdc, 15 * k, 12 * k, 16 * k, 13 * k);

			Rectangle(hdc, 18 * k, 12 * k, 19 * k, 13 * k);

			Rectangle(hdc, 24 * k, 12 * k, 25 * k, 13 * k);

			Rectangle(hdc, 6 * k, 13 * k, 7 * k, 14 * k);	//line 13 black
			Rectangle(hdc, 14 * k, 13 * k, 15 * k, 14 * k);
			Rectangle(hdc, 19 * k, 13 * k, 20 * k, 14 * k);


			Rectangle(hdc, 3 * k, 14 * k, 4 * k, 15 * k);	//line 14 black
			Rectangle(hdc, 6 * k, 14 * k, 7 * k, 15 * k);
			Rectangle(hdc, 14 * k, 14 * k, 15 * k, 15 * k);
			Rectangle(hdc, 19 * k, 14 * k, 20 * k, 15 * k);
			Rectangle(hdc, 22 * k, 14 * k, 23 * k, 15 * k);

			Rectangle(hdc, 4 * k, 15 * k, 5 * k, 16 * k);	//line 15 black
			Rectangle(hdc, 5 * k, 15 * k, 6 * k, 16 * k);

			Rectangle(hdc, 8 * k, 15 * k, 9 * k, 16 * k);

			Rectangle(hdc, 12 * k, 15 * k, 13 * k, 16 * k);
			Rectangle(hdc, 13 * k, 15 * k, 14 * k, 16 * k);
			Rectangle(hdc, 14 * k, 15 * k, 15 * k, 16 * k);

			Rectangle(hdc, 17 * k, 15 * k, 18 * k, 16 * k);

			Rectangle(hdc, 20 * k, 15 * k, 21 * k, 16 * k);
			Rectangle(hdc, 21 * k, 15 * k, 22 * k, 16 * k);

			Rectangle(hdc, 5 * k, 16 * k, 6 * k, 17 * k);	//line 16 black

			Rectangle(hdc, 14 * k, 16 * k, 15 * k, 17 * k);

			Rectangle(hdc, 20 * k, 16 * k, 21 * k, 17 * k);

			Rectangle(hdc, 2 * k, 17 * k, 3 * k, 18 * k);	//line 17 black
			Rectangle(hdc, 3 * k, 17 * k, 4 * k, 18 * k);
			Rectangle(hdc, 4 * k, 17 * k, 5 * k, 18 * k);

			Rectangle(hdc, 14 * k, 17 * k, 15 * k, 18 * k);

			Rectangle(hdc, 21 * k, 17 * k, 22 * k, 18 * k);
			Rectangle(hdc, 22 * k, 17 * k, 23 * k, 18 * k);
			Rectangle(hdc, 23 * k, 17 * k, 24 * k, 18 * k);

			Rectangle(hdc, 4 * k, 18 * k, 5 * k, 19 * k);	//line 18 black

			Rectangle(hdc, 14 * k, 18 * k, 15 * k, 19 * k);
			Rectangle(hdc, 15 * k, 18 * k, 16 * k, 19 * k);
			Rectangle(hdc, 16 * k, 18 * k, 17 * k, 19 * k);

			Rectangle(hdc, 21 * k, 18 * k, 22 * k, 19 * k);

			Rectangle(hdc, 4 * k, 19 * k, 5 * k, 20 * k);	//line 19 black

			Rectangle(hdc, 14 * k, 19 * k, 15 * k, 20 * k);

			Rectangle(hdc, 17 * k, 19 * k, 18 * k, 20 * k);

			Rectangle(hdc, 21 * k, 19 * k, 22 * k, 20 * k);

			Rectangle(hdc, 3 * k, 20 * k, 4 * k, 21 * k);	//line 20 black 

			Rectangle(hdc, 14 * k, 20 * k, 15 * k, 21 * k);

			Rectangle(hdc, 18 * k, 20 * k, 19 * k, 21 * k);
			Rectangle(hdc, 19 * k, 20 * k, 20 * k, 21 * k);

			Rectangle(hdc, 22 * k, 20 * k, 23 * k, 21 * k);

			Rectangle(hdc, 3 * k, 21 * k, 4 * k, 22 * k);	//line 21 black 

			Rectangle(hdc, 11 * k, 21 * k, 12 * k, 22 * k);

			Rectangle(hdc, 14 * k, 21 * k, 15 * k, 22 * k);

			Rectangle(hdc, 22 * k, 21 * k, 23 * k, 22 * k);

			Rectangle(hdc, 2 * k, 22 * k, 3 * k, 23 * k);	//line 22 black

			Rectangle(hdc, 12 * k, 22 * k, 13 * k, 23 * k);
			Rectangle(hdc, 13 * k, 22 * k, 14 * k, 23 * k);

			Rectangle(hdc, 15 * k, 22 * k, 16 * k, 23 * k);

			Rectangle(hdc, 22 * k, 22 * k, 23 * k, 23 * k);

			Rectangle(hdc, 2 * k, 23 * k, 3 * k, 24 * k);	//line 23 black

			Rectangle(hdc, 4 * k, 23 * k, 5 * k, 24 * k);

			Rectangle(hdc, 16 * k, 23 * k, 17 * k, 24 * k);

			Rectangle(hdc, 22 * k, 23 * k, 23 * k, 24 * k);

			Rectangle(hdc, 2 * k, 24 * k, 3 * k, 25 * k);	//line 24 black

			Rectangle(hdc, 4 * k, 24 * k, 5 * k, 25 * k);

			Rectangle(hdc, 17 * k, 24 * k, 18 * k, 25 * k);
			Rectangle(hdc, 18 * k, 24 * k, 19 * k, 25 * k);
			Rectangle(hdc, 19 * k, 24 * k, 20 * k, 25 * k);

			Rectangle(hdc, 22 * k, 24 * k, 23 * k, 25 * k);


			Rectangle(hdc, 2 * k, 25 * k, 3 * k, 26 * k);	//line 25 black
			Rectangle(hdc, 3 * k, 25 * k, 4 * k, 26 * k);

			Rectangle(hdc, 22 * k, 25 * k, 23 * k, 26 * k); 

			Rectangle(hdc, 2 * k, 26 * k, 3 * k, 27 * k);	//line 26 black
			Rectangle(hdc, 3 * k, 26 * k, 4 * k, 27 * k);

			Rectangle(hdc, 22 * k, 26 * k, 23 * k, 27 * k); 

			Rectangle(hdc, 3 * k, 27 * k, 4 * k, 28 * k);	//line 27 black
			Rectangle(hdc, 4 * k, 27 * k, 5 * k, 28 * k);

			Rectangle(hdc, 21 * k, 27 * k, 22 * k, 28 * k);

			Rectangle(hdc, 4 * k, 28 * k, 5 * k, 29 * k);	//line 28 black

			Rectangle(hdc, 21 * k, 28 * k, 22 * k, 29 * k);	

			Rectangle(hdc, 5 * k, 29 * k, 6 * k, 30 * k);	//line 29 black

			Rectangle(hdc, 20 * k, 29 * k, 21 * k, 30 * k);

			Rectangle(hdc, 6 * k, 30 * k, 7 * k, 31 * k);	//line 30 black

			Rectangle(hdc, 19 * k, 30 * k, 20 * k, 31 * k);

			Rectangle(hdc, 6 * k, 31 * k, 7 * k, 32 * k);	//line 31 black

			Rectangle(hdc, 19 * k, 31 * k, 20 * k, 32 * k);

			Rectangle(hdc, 7 * k, 31 * k, 8 * k, 32 * k);	//line 32 black

			Rectangle(hdc, 12 * k, 31 * k, 13 * k, 32 * k);
			Rectangle(hdc, 13 * k, 31 * k, 14 * k, 32 * k);

			Rectangle(hdc, 18 * k, 31 * k, 19 * k, 32 * k);

			Rectangle(hdc, 8 * k, 32 * k, 9 * k, 33 * k);	//line 33 black
			Rectangle(hdc, 9 * k, 32 * k, 10 * k, 33 * k);
			Rectangle(hdc, 10 * k, 32 * k, 11 * k, 33 * k);
			Rectangle(hdc, 11 * k, 32 * k, 12 * k, 33 * k);
			Rectangle(hdc, 12 * k, 32 * k, 13 * k, 33 * k);
			Rectangle(hdc, 13 * k, 32 * k, 14 * k, 33 * k);
			Rectangle(hdc, 14 * k, 32 * k, 15 * k, 33 * k);
			Rectangle(hdc, 15 * k, 32 * k, 16 * k, 33 * k);
			Rectangle(hdc, 16 * k, 32 * k, 17 * k, 33 * k);
			Rectangle(hdc, 17 * k, 32 * k, 18 * k, 33 * k);


			

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
