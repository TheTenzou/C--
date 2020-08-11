// MDI.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MDI.h"

#define MAX_LOADSTRING 100

// Global Variables:
HWND hwndFrame; // окно Frame Window
HWND hwndClient; // окно Client Window
HWND hwndChild; // окно Child Window

char const szFrameClassName[] = "MDIAppClass";
char const szChildClassName[] = "MDIchildAppClass";
char const szWindowTitle[] = "Simple MDI Application";


HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

BOOL InitApp(HINSTANCE);
LRESULT CALLBACK FrameWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    /*UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MDI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MDI));

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
	*/
	MSG msg; // структура для работы с сообщениями
	hInst = hInstance; // сохраняем идентификатор приложения
	if (hPrevInstance) // может быть запущена
		return FALSE; // только одна копия приложения
		// Инициализируем приложение
	if (!InitApp(hInstance))
		return FALSE;
	// Создаем главное окно приложения - Frame Window
	hwndFrame = CreateWindowA(
		szFrameClassName, // имя класса окна
		szWindowTitle, // заголовок окна
		WS_OVERLAPPEDWINDOW, // стиль окна
		CW_USEDEFAULT, 0, // задаем размеры и расположение
		CW_USEDEFAULT, 0, // окна, принятые по умолчанию
		0, // идентификатор родительского окна
		0, // идентификатор меню
		hInstance, // идентификатор приложения
		NULL); // указатель на дополнительные параметры
		// Если создать окно не удалось, завершаем приложение
	if (!hwndFrame)
		return FALSE;
	// Рисуем главное окно
	ShowWindow(hwndFrame, nCmdShow);
		UpdateWindow(hwndFrame);
	// Запускаем цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// Трансляция для MDI-приложения
		if (!TranslateMDISysAccel(hwndClient, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	//return msg.wParam;
//}

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MDI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MDI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitApp(HINSTANCE hInstance)
{
	ATOM aWndClass; // атом для кода возврата
	WNDCLASS wc; // структура для регистрации
	// класса окна
	// Регистрируем класс для главного окна приложения
	// (т. е. для окна Frame Window)
	memset(&wc, 0, sizeof(wc));
	wc.lpszMenuName = L"APP_MENU";
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)FrameWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MDI));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);
	wc.lpszClassName = (LPCWSTR)szFrameClassName;
	aWndClass = RegisterClass(&wc);
	if (!aWndClass)
		return FALSE;
	// Регистрируем класс окна для дочернего окна Document Window
	memset(&wc, 0, sizeof(wc));
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)ChildWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MDI));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = (LPCWSTR)szChildClassName;
	aWndClass = RegisterClass(&wc);
	if (!aWndClass)
		return FALSE;
		return TRUE;
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
		CLIENTCREATESTRUCT ccs;

		// Retrieve the handle to the window menu and assign the 
		// first child window identifier. 

		ccs.hWindowMenu = GetSubMenu(GetMenu(hWnd), 1);
		ccs.idFirstChild = 1;

		// Create the MDI client window. 

		hwndClient = CreateWindow(L"MDICLIENT", (LPCTSTR)NULL,
			WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL,
			0, 0, 0, 0, hWnd, (HMENU)0xCAC, hInst, (LPSTR)&ccs);

		ShowWindow(hwndClient, SW_SHOW);

		break;
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


LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Структура для создания окна Client Window
	CLIENTCREATESTRUCT clcs;
	// Структура для создания дочернего окна Document Window
	MDICREATESTRUCT mdics;
	switch (msg)
	{
		// При создании окна Frame Window создаем
		// окно Client Window, внутри которого будут создаваться
		// дочерние окна Document Window
	case WM_CREATE:
	{
		// Получаем и сохраняем в структуре clcs идентификатор
		// временного меню "Window". Так как это меню второе
		// слева, его позиция равна 1 (меню "File" имеет
		// позицию 0)
		clcs.hWindowMenu = GetSubMenu(GetMenu(hwnd), 1);
		// Идентификатор первого дочернего окна Document Window
		clcs.idFirstChild = 500;

		// Создаем окно Client Window
		hwndClient = CreateWindowA(
			"MDICLIENT", // имя класса окна
			NULL, // заголовок окна
			WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE | // стиль окна
			WS_HSCROLL | WS_VSCROLL,
			0, 0, 0, 0,
			hwnd, // идентификатор родительского окна
			(HMENU)1, // идентификатор меню
			hInst, // идентификатор приложения
			(LPSTR)&clcs);// указатель на дополнительные параметры
		break;
	}
	// Обработка сообщений от главного меню приложения
	case WM_COMMAND:
	{
		switch (wParam)
		{
			// Создание нового окна Document Window
		//case IDM_ABOUT:
		{
			// Заполняем структуру MDICREATESTRUCT
			mdics.szClass = (LPCWSTR)szChildClassName; // класс окна
			mdics.szTitle = L"MDI Child Window"; // заголовок окна
			mdics.hOwner = hInst; // идентификатор приложения
			mdics.x = CW_USEDEFAULT; // размеры окна
			mdics.y = CW_USEDEFAULT; // Document Window
			mdics.cx = CW_USEDEFAULT;
			mdics.cy = CW_USEDEFAULT;
			mdics.style = 0; // дополнительные стили
			mdics.lParam = NULL; // 32-битное значение
			// Посылаем сообщение WM_MDICREATE окну Client
			// Window. В результате будет создано
			// новое окно Document Window
			hwndChild = (HWND)SendMessage(hwndClient,
				WM_MDICREATE, 0, (LPARAM)&mdics);
			break;
		}
		break;
		}

		return DefFrameProc(hwnd, hwndClient,
			msg, wParam, lParam);
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	break;
	}
	return DefFrameProc(hwnd, hwndClient, msg, wParam, lParam);
}
// Функция ChildWndProc
LRESULT CALLBACK ChildWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefMDIChildProc(hwnd, msg, wParam, lParam);
}