// Lab 2.0.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Lab 2.0.h"
#include <math.h>
#include <commdlg.h>


#define MAX_LOADSTRING 100
#define PI 3.14


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

CHOOSECOLOR CC_BORDER;
static COLORREF arcCustClrBorder[16];
static DWORD rgbCurentBorder;

CHOOSECOLOR CC_FILL;
static COLORREF arcCustClrFill[16];
static DWORD rgbCurentFill;

int shapeType = 0;
int borderType = 0;
int fillType = 0;
int angle = 0;
int thickness = 1;
HWND  hComboBorder;
HWND  hComboFill;
CHAR BorderName1[] = { "Solid" };
CHAR BorderName2[] = { "Dash" };
CHAR BorderName3[] = { "Dot" };
CHAR BorderName4[] = { "Dash dot" };
CHAR BorderName5[] = { "Dash dot dot" };
CHAR FillName1[] = { "Solid" };
CHAR FillName2[] = { "Horizontal" };
CHAR FillName3[] = { "Vertical" };
CHAR FillName4[] = { "Cross" };
CHAR FillName5[] = { "Bdiagonal" };
CHAR FillName6[] = { "Fdiagonal" };
CHAR FillName7[] = { "Dia Cors" };
HPEN hPen;
HBRUSH hBrush;


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	DlgProc(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_LAB20, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB20));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB20));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCEW(IDR_MENU1);
	//wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB20);
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
            case ID_INPUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);
                break;
            
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
			InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
			hPen = CreatePen(borderType, thickness, CC_BORDER.rgbResult);
			if (fillType == 0) 
			{
				hBrush = CreateSolidBrush(CC_FILL.rgbResult);
			}
			else
			{
				hBrush = CreateHatchBrush(fillType-1, CC_FILL.rgbResult);
			}
			
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			if (shapeType == 1) {
				int rectCentreX = 250;
				int rectCentreY = 250;
				int rectRad = 100;
				POINT rect[4];
				rect[0].x = rectCentreX + LONG(rectRad * cos(PI / 180 * (45 + angle)));
				rect[0].y = rectCentreY + LONG(rectRad * sin(PI / 180 * (45 + angle)));
				rect[1].x = rectCentreX + LONG(rectRad * cos(PI / 180 * (135 + angle)));
				rect[1].y = rectCentreY + LONG(rectRad * sin(PI / 180 * (135 + angle)));
				rect[2].x = rectCentreX + LONG(rectRad * cos(PI / 180 * (225 + angle)));
				rect[2].y = rectCentreY + LONG(rectRad * sin(PI / 180 * (225 + angle)));
				rect[3].x = rectCentreX + LONG(rectRad * cos(PI / 180 * (315 + angle)));
				rect[3].y = rectCentreY + LONG(rectRad * sin(PI / 180 * (315 + angle)));
				Polygon(hdc, rect, 4);
			}
			else if (shapeType == 2)
			{
				int triagCentreX = 250;
				int triagCentreY = 250;
				int triagRad = 100;
				POINT triag[4];
				triag[0].x = triagCentreX + LONG(triagRad * cos(PI / 180 * (90 + angle)));
				triag[0].y = triagCentreY + LONG(triagRad * sin(PI / 180 * (90 + angle)));
				triag[1].x = triagCentreX + LONG(triagRad * cos(PI / 180 * (210 + angle)));
				triag[1].y = triagCentreY + LONG(triagRad * sin(PI / 180 * (210 + angle)));
				triag[2].x = triagCentreX + LONG(triagRad * cos(PI / 180 * (330 + angle)));
				triag[2].y = triagCentreY + LONG(triagRad * sin(PI / 180 * (330 + angle)));
				Polygon(hdc, triag, 3);
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


INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		hComboBorder = GetDlgItem(hDlg, IDC_BORDERTYPE);
		SendMessage(hComboBorder, CB_ADDSTRING, 0, /*(LPARAM)*/BorderName1);
		SendMessage(hComboBorder, CB_ADDSTRING, 0, (LPARAM)BorderName2);
		SendMessage(hComboBorder, CB_ADDSTRING, 0, (LPARAM)BorderName3);
		SendMessage(hComboBorder, CB_ADDSTRING, 0, (LPARAM)BorderName4);
		SendMessage(hComboBorder, CB_ADDSTRING, 0, (LPARAM)BorderName5);
		SendMessage(hComboBorder, CB_SETCURSEL, 0, 0);
		hComboFill = GetDlgItem(hDlg, IDC_FILL_TYPE);
		SendMessage(hComboFill, CB_ADDSTRING, 0, (LPARAM)FillName1);
		SendMessage(hComboFill, CB_ADDSTRING, 0, (LPARAM)FillName2);
		SendMessage(hComboFill, CB_ADDSTRING, 0, (LPARAM)FillName3);
		SendMessage(hComboFill, CB_ADDSTRING, 0, (LPARAM)FillName4);
		SendMessage(hComboFill, CB_ADDSTRING, 0, (LPARAM)FillName5);
		SendMessage(hComboFill, CB_ADDSTRING, 0, (LPARAM)FillName6);
		SendMessage(hComboFill, CB_ADDSTRING, 0, (LPARAM)FillName7);
		SendMessage(hComboFill, CB_SETCURSEL, 0, 0);
		break;

	case WM_COMMAND:
		{
		switch (LOWORD(wParam))
		{
		case IDOK:
			if (IsDlgButtonChecked(hDlg, IDC_RECT))
			{
				shapeType = 1;
			}
			if (IsDlgButtonChecked(hDlg, IDC_TRIAG))
			{
				shapeType = 2;
			}
			thickness = GetDlgItemInt(hDlg, IDC_THICK, NULL, NULL);
			borderType = SendMessage(hComboBorder, CB_GETCURSEL, 0, 0);
			fillType = SendMessage(hComboFill, CB_GETCURSEL, 0, 0);
			angle = GetDlgItemInt(hDlg, IDC_ANG, NULL, NULL);
			break;
		case IDC_COLOR1:
			ZeroMemory(&CC_BORDER, sizeof(CHOOSECOLOR));
			CC_BORDER.lStructSize = sizeof(CHOOSECOLOR);
			CC_BORDER.hwndOwner = hDlg;
			CC_BORDER.lpCustColors = (LPDWORD)arcCustClrBorder;
			CC_BORDER.rgbResult = rgbCurentBorder;
			CC_BORDER.Flags = CC_FULLOPEN | CC_RGBINIT;
			ChooseColor(&CC_BORDER);
			break;
		case IDC_COLOR2:
			ZeroMemory(&CC_FILL, sizeof(CHOOSECOLOR));
			CC_FILL.lStructSize = sizeof(CHOOSECOLOR);
			CC_FILL.hwndOwner = hDlg;
			CC_FILL.lpCustColors = (LPDWORD)arcCustClrFill;
			CC_FILL.rgbResult = rgbCurentFill;
			CC_FILL.Flags = CC_FULLOPEN | CC_RGBINIT;
			ChooseColor(&CC_FILL);
			break;
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			break;
		}
		break;
		}
	}
	return (INT_PTR)FALSE;
}