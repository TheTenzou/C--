#include "stdafx.h"
#include <cmath>
#include "MDI3.h"
#include "windows.h"
#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
HWND hwndFrame;									// Фрейм
HWND hwndClient;								// Клиент
HWND hwndChildGraph;							// Первая Доча
HWND hwndChildSeq;								// Вторая Доча
UINT_PTR TIMER;
int t = 0;
char text[255] = "";
// Глобальные переменные для графика:
const double PI = 3.1415926535897932384626433832795;
float rotkoeff = 0, intkoeff = 0;		// Контролируем интервал и коэффициент растяжения:

// Глобальные переменные для последовательности:
int nTimerID;
// Имена классов окон:
WCHAR szFrameClassName[MAX_LOADSTRING] = L"MDIAppClass";   // имя класса главного окна
WCHAR szChild1ClassName[MAX_LOADSTRING] = L"MDIchild1AppClass";
WCHAR szChild2ClassName[MAX_LOADSTRING] = L"MDIChild2AppClass";
// Заголовок окна:
WCHAR szTitle[MAX_LOADSTRING] = L"MDI_15";                  // Текст строки заголовка

// Отправить объявления функций, включенных в этот модуль кода:
BOOL                InitApp(HINSTANCE);
LRESULT CALLBACK    FrameWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ChildGraphWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT	CALLBACK	ChildSeqWndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: разместите код здесь.

	hInst = hInstance;
	MSG msg;

	// Инициализация:
	if (!InitApp(hInstance))
	{
		return FALSE;
	}

	// Создаем фрейм:
	hwndFrame = CreateWindow(
		szFrameClassName,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0,
		CW_USEDEFAULT, 0,
		0,
		0,
		hInstance,
		NULL);

	// Не удалось - идем лесом:
	if (!hwndFrame)
		return FALSE;

	// Рисуем фрейм:
	ShowWindow(hwndFrame, nCmdShow);
	UpdateWindow(hwndFrame);

	// Цикл обработки сообщений и трансляция МДИ:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateMDISysAccel(hwndClient, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

//
//   ФУНКЦИЯ: InitApp(HINSTANCE)
//
//   НАЗНАЧЕНИЕ: регистрирует классы окон.
//

BOOL InitApp(HINSTANCE hInstance)
{
	ATOM aWndClass;
	WNDCLASS wc;

	// Регистрируем класс для фрейма:
	memset(&wc, 0, sizeof(wc));
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)FrameWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, L"APP_ICON");
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);
	wc.lpszClassName = szFrameClassName;
	aWndClass = RegisterClass(&wc);

	if (!aWndClass)
		return FALSE;

	// Регистрируем класс для дочи:
	memset(&wc, 0, sizeof(wc));
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)ChildGraphWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MDI3));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = szChild1ClassName;
	aWndClass = RegisterClass(&wc);

	if (!aWndClass)
		return FALSE;

	// Регистрируем класс для второй дочи:
	memset(&wc, 0, sizeof(wc));
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)ChildSeqWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MDI3));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = szChild2ClassName;
	aWndClass = RegisterClass(&wc);

	if (!aWndClass)
		return FALSE;

	return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK FrameWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CLIENTCREATESTRUCT clcs;
	CLIENTCREATESTRUCT cls;
	MDICREATESTRUCT	   mdics;
	MDICREATESTRUCT	   mcs;
	RECT rect;
	switch (message)
	{
	case WM_CREATE:
	{
		// заполняем клиентскую структуру:
		clcs.hWindowMenu = GetSubMenu(GetMenu(hWnd), 0);
		clcs.idFirstChild = 500;

		// создаем клиента:
		hwndClient = CreateWindow(
			L"MDICLIENT",
			NULL,
			WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE |
			WS_HSCROLL | WS_VSCROLL,
			0, 0, 0, 0,
			hWnd,
			(HMENU)0,
			hInst,
			(LPSTR)&clcs);
		ShowWindow(hwndClient, SW_SHOW);
		UpdateWindow(hwndClient);
		break;
	}
	case WM_COMMAND:
	{
		switch (wParam)
		{
		case IDM_GRAPH:
		{
			// заполняем мди структуру:
			mcs.szClass = szChild1ClassName;
			mcs.szTitle = L"Graph";
			mcs.hOwner = hInst;
			mcs.x = CW_USEDEFAULT;
			mcs.y = CW_USEDEFAULT;
			mcs.cx = CW_USEDEFAULT;
			mcs.cy = CW_USEDEFAULT;
			mcs.style = 0;
			mcs.lParam = NULL;

			//MessageBox(0, 0, 0, 0);
			//посылаем сообщение WM_MDICREATE клиентскому окну
			// в реузльтате будет создано одно документное окно
			// в этом случае окно для графика функции 
			// y = k*ctg(x), k in R
			hwndChildGraph = (HWND)SendMessage(hwndClient,WM_MDICREATE, 0, (LPARAM)&mcs);
			break;
		}
		case IDM_SEQ:
		{
			// заполняем мди структуру:
			mdics.szClass = szChild2ClassName;
			mdics.szTitle = L"Sequence";
			mdics.hOwner = hInst;
			mdics.x = CW_USEDEFAULT;
			mdics.y = CW_USEDEFAULT;
			mdics.cx = CW_USEDEFAULT;
			mdics.cy = CW_USEDEFAULT;
			mdics.style = 0;
			mdics.lParam = NULL;

			//посылаем сообщение WM_MDICREATE клиентскому окну
			// в реузльтате будет создано одно документное окно
			// в этом случае окно для последовательности
			//MessageBox(0,0,0,0);

			hwndChildSeq = (HWND)SendMessage(hwndClient,WM_MDICREATE, 0, (LPARAM)&mdics);

			break;
		}
		//case IDM_WINDOWTILE:
		{
			SendMessage(hwndClient, WM_MDITILE, 0, NULL);
			break;
		}
		//case IDM_WINDOWCASCADE:
		{
			SendMessage(hwndClient, WM_MDICASCADE, 0, NULL);
			break;
		}
		case IDM_WINDOWCLOSEALL:
		{
			HWND hwndTemp;
			ShowWindow(hwndClient, SW_HIDE);
			for (;;)
			{
				hwndTemp = GetWindow(hwndClient, GW_CHILD);
				if (!hwndTemp)
				{
					break;
				}
				while (hwndTemp && GetWindow(hwndTemp, GW_OWNER))
					hwndTemp = GetWindow(hwndTemp, GW_HWNDNEXT);
				if (hwndTemp)
					SendMessage(hwndClient,
						WM_MDIDESTROY,
						(WPARAM)hwndTemp,
						NULL);
				else
					break;
			}
			ShowWindow(hwndClient, SW_SHOW);
			break;
		}
		case IDM_EXIT:
		{
			DestroyWindow(hWnd);
			break;
		}
		default:
			return DefFrameProc(hWnd, hwndClient, message, wParam, lParam);
		}

		return DefFrameProc(hWnd, hwndClient, message, wParam, lParam);
	}
	break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default:
		return DefFrameProc(hWnd, hwndClient, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK ChildGraphWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Для отрисовки:
	HDC hdc;
	PAINTSTRUCT ps;
	static HPEN pen1, pen2;

	// Контролируем изменение размера дочи: 
	RECT rect;

	// Координаты границы дочернего окна:
	static int sx, sy;

	// Экранные координаты:
	int a, b, x_scr, y_scr;

	// Фактические координаты:
	double x, h;

	// Для popup-меню:
	HMENU GraphMenu;
	HMENU GraphPopUpMenu;
	int result;

	switch (message)
	{
	case WM_CREATE:
		pen1 = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		pen2 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		GetClientRect(GetParent(hWnd), &rect);
		if (rect.bottom == sy && rect.right == sx)
			MoveWindow(hWnd, 0, 0, rect.right, rect.bottom, false);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_INT_ONE:
			intkoeff = 1.0;
			InvalidateRect(hWnd, NULL, true);
			break;
		case IDM_INT_TWO:
			intkoeff = 0.5;
			InvalidateRect(hWnd, NULL, true);
			break;
		case IDM_INT_THREE:
			intkoeff = 0.335;
			InvalidateRect(hWnd, NULL, true);
			break;
		case IDM_INT_ZO:
			rotkoeff = 0.1;
			InvalidateRect(hWnd, NULL, true);
			break;
		case IDM_INT_ZF:
			rotkoeff = 0.5;
			InvalidateRect(hWnd, NULL, true);
			break;
		case IDM_INT_O:
			rotkoeff = 1.0;
			InvalidateRect(hWnd, NULL, true);
			break;
		default:
			return	DefMDIChildProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_CONTEXTMENU:
		POINT pt;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		if (pt.x == -1 && pt.y == -1)
		{
			RECT rect1;
			GetWindowRect(hWnd, &rect);
			pt.x = rect.left + 5;
			pt.y = rect.top + 5;
		}
		GraphMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU2));
		GraphPopUpMenu = GetSubMenu(GraphMenu, 0);
		TrackPopupMenu(GraphPopUpMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, 0);
		DestroyMenu(GraphMenu);
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		a = sx / 2;
		b = sy / 2;
		// Строим сам котангенс:
		MoveToEx(hdc, 0, b, NULL);
		h = 3 * PI / a;
		SelectObject(hdc, pen2);
		for (x = -50 * PI, x_scr = 0; x < 50 * PI; x += h)
		{
			x_scr = intkoeff * ((x + PI)*a / PI);
			y_scr = b - rotkoeff * b*(1 / (tan(x)));
			LineTo(hdc, x_scr, y_scr);
		}

		// Строим систему координат:
		SelectObject(hdc, pen1);
		MoveToEx(hdc, 0, b, NULL);
		LineTo(hdc, sx, b);
		MoveToEx(hdc, a, 0, NULL);
		LineTo(hdc, a, sy);
		MoveToEx(hdc, a, 0, NULL);
		LineTo(hdc, a - 5, 5);
		MoveToEx(hdc, a, 0, NULL);
		LineTo(hdc, a + 5, 5);
		MoveToEx(hdc, sx, b, NULL);
		LineTo(hdc, sx - 5, b - 5);
		MoveToEx(hdc, sx, b, NULL);
		LineTo(hdc, sx - 5, b + 5);
		TextOut(hdc, a - 20, 0, L"y", 1);
		TextOut(hdc, sx - 20, b - 20, L"x", 1);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		SendMessage(hWnd, WM_MDIDESTROY, (WPARAM)hwndClient, NULL);
		break;

	default:
		return	DefMDIChildProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
LRESULT CALLBACK ChildSeqWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int sx=10, sy=10;
	RECT rect;


	switch (message)
	{
	
	case WM_CREATE:
		SetTimer(hWnd, TIMER, 1000, (TIMERPROC)NULL);
		//MessageBox(0, 0, 0, 0);
		break;
	case WM_TIMER:
		
		t++;
		_itoa_s(t*t, text, 10);
		
		InvalidateRect(hWnd, NULL, true);
		//MessageBox(0, 0, 0, 0);
		break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		GetClientRect(GetParent(hWnd), &rect);
		if (rect.bottom == sy && rect.right == sx)
			MoveWindow(hWnd, 0, 0, rect.right, rect.bottom, false);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOutA(hdc, sx / 2, sy / 2, text, strlen(text));
		EndPaint(hWnd, &ps);
		break;
	default:
		return DefMDIChildProc(hWnd, message, wParam, lParam);
	}
	return 0;
}