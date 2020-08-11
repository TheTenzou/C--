// Files.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Files.h"
#include "Windows.h"
#include "direct.h"
#include "iostream"
#include "fstream"
#include "Shlwapi.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND hEdit;
HWND hButtonCreateFolder;
HWND hButtonRename;
HWND hButtonCreateFile;
HWND hButtonInputN;
HWND hButtonInput;
HWND hButtonGetNewFile;
HWND hButtonClear;
HANDLE hFile;
HANDLE hFile2;
int ycor = 0;
int n;
int k;
int min = 0;
int lust2dg;
int lust2dgmin;
int num;
char text[255];
char newLine[] = { "\r\n" };
LPTSTR text2 = {};

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
    LoadStringW(hInstance, IDC_FILES, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FILES));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FILES));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_FILES);
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
	case WM_CREATE:
		hEdit = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 20, 200, 20, hWnd, NULL, NULL, NULL);
		hButtonCreateFolder = CreateWindow(L"BUTTON", L"Create Folder", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 60, 200, 50, hWnd, (HMENU)1, NULL, NULL);
		hButtonRename = CreateWindow(L"BUTTON", L"Rename Folder", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 60, 200, 50, hWnd, (HMENU)2, NULL, NULL);
		hButtonCreateFile = CreateWindow(L"BUTTON", L"Create File", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 60, 200, 50, hWnd, (HMENU)3, NULL, NULL);
		hButtonInputN = CreateWindow(L"BUTTON", L"Input N", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 60, 200, 50, hWnd, (HMENU)4, NULL, NULL);
		hButtonInput = CreateWindow(L"BUTTON", L"Input", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 60, 200, 50, hWnd, (HMENU)5, NULL, NULL);
		hButtonGetNewFile = CreateWindow(L"BUTTON", L"Get New File", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 60, 200, 50, hWnd, (HMENU)6, NULL, NULL);
		hButtonClear = CreateWindow(L"BUTTON", L"Clear", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 60, 200, 50, hWnd, (HMENU)7, NULL, NULL);
		SetFocus(hEdit);
		//ShowWindow(hButtonCreateFolder, SW_HIDE);
		ShowWindow(hButtonRename, SW_HIDE);
		ShowWindow(hButtonCreateFile, SW_HIDE);
		ShowWindow(hButtonInputN, SW_HIDE);
		ShowWindow(hButtonInput, SW_HIDE);
		ShowWindow(hButtonGetNewFile, SW_HIDE);
		ShowWindow(hButtonClear, SW_HIDE);
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case 1:
			ShowWindow(hButtonCreateFolder, SW_HIDE);
			ShowWindow(hButtonRename, SW_SHOW);
			if (!CreateDirectory(L"Temp", NULL))
			{
				MessageBox(hWnd, L"doesnt work", L"test", NULL);
			}
			break;
		case 2:

			ShowWindow(hButtonRename, SW_HIDE);
			ShowWindow(hButtonCreateFile, SW_SHOW);
			//ShowWindow(hButtonInput, SW_SHOW);
			//ShowWindow(hButtonClear, SW_SHOW);
			if (!MoveFile(L"Temp", L"folder2"))
			{
				MessageBox(hWnd, L"doesnt work", L"test", NULL);
			}
			;

			break;
		case 3:
			ShowWindow(hButtonCreateFile, SW_HIDE);
			ShowWindow(hButtonInputN, SW_SHOW);
			SetCurrentDirectory(L"folder2");
			hFile = CreateFile(L"input.txt",
				GENERIC_READ | GENERIC_WRITE,
				NULL,
				NULL,
				CREATE_NEW,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
			//MessageBeep(MB_ICONERROR);
			SetFocus(hEdit);
			break;
		case 4:
			ShowWindow(hButtonInputN, SW_HIDE);
			ShowWindow(hButtonInput, SW_SHOW);
			GetWindowText(hEdit, (LPTSTR)text, 255);
			n = atoi(text);
			k = n;
			break;
		case 5:
			GetWindowTextA(hEdit, text, 255);
			WriteFile(hFile, text, 16, NULL, NULL);
			WriteFile(hFile, &newLine, 2, NULL, NULL);
			n--;
			if (n == 0)
			{
				ShowWindow(hButtonInput, SW_HIDE);
				ShowWindow(hButtonGetNewFile, SW_SHOW);
				CloseHandle(hFile);
				/*hFile = CreateFile(	L"input.txt",
									GENERIC_READ | GENERIC_WRITE,
									NULL,
									NULL,
									CREATE_NEW,
									FILE_ATTRIBUTE_NORMAL,
									NULL);

				for (int i = 0; i < k; i++)
				{
					ReadFile(hFile, text, 16, NULL, NULL);
					InvalidateRect(hWnd, NULL, FALSE);
					//y = y + 20;
					//_itoa_s(ycor, text, 10);
					//MessageBoxA(hWnd, text, "Test", NULL);

					ReadFile(hFile, text, 2, NULL, NULL);
				}
				CloseHandle(hFile);
			}
			SetFocus(hEdit);*/
				break;
		case 6:
			hFile = CreateFile(L"input.txt",
				GENERIC_READ | GENERIC_WRITE,
				NULL,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);

			for (int i = 0; i < k; i++)
			{
				ReadFile(hFile, text, 16, NULL, NULL);
				//MessageBoxA(hWnd, text, "Test", NULL);
				num = atoi(text);
				if ((num < 10000)&(num > 999)&((num < min) || (min == 0))) min = num;
				ReadFile(hFile, text, 2, NULL, NULL);
			}
			/*_itoa_s(min, text, 10);
			MessageBoxA(hWnd, text, "Test", NULL);*/
			lust2dgmin = min % 10 + (min % 100) / 10;
			CloseHandle(hFile);
			hFile = CreateFile(L"input.txt",
				GENERIC_READ | GENERIC_WRITE,
				NULL,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);

			hFile2 = CreateFile(L"output.txt",
				GENERIC_READ | GENERIC_WRITE,
				NULL,
				NULL,
				CREATE_NEW,
				FILE_ATTRIBUTE_NORMAL,
				NULL);

			for (int i = 0; i < k; i++)
			{
				ReadFile(hFile, text, 16, NULL, NULL);
				//MessageBoxA(hWnd, text, "Test", NULL);
				num = atoi(text);
				lust2dg = num % 10 + (num % 100) / 10;
				if ((lust2dg != lust2dgmin)&(num < 10000)&(num > 999))
				{
					WriteFile(hFile2, text, 16, NULL, NULL);
					WriteFile(hFile2, &newLine, 2, NULL, NULL);
				}
				ReadFile(hFile, text, 2, NULL, NULL);
			}

			ShowWindow(hButtonGetNewFile, SW_HIDE);
			ShowWindow(hButtonClear, SW_SHOW);
			break;
		case 7:
			ShowWindow(hButtonCreateFolder, SW_SHOW);
			ShowWindow(hButtonClear, SW_HIDE);
			break;
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
		TextOutA(hdc, 400, ycor, text, sizeof(text));
		//Sleep(100);
		ycor = ycor + 20;
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
