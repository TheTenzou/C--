// Practice.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Practice.h"
#include "math.h"
#include <Commdlg.h>

#define MAX_LOADSTRING 100

#define ID_BUTTON_INPUT			1
#define ID_BUTTON_EDIT			2
#define ID_BUTTON_SEARCH		3
#define	ID_BUTTON_NEXT			4
#define ID_BUTTON_PREV			5
#define	ID_BUTTON_SEARCH_NEXT	6
#define ID_BUTTON_SEARCH_PREV	7

#define ID_COMBOBOX_SECONDNAME		10
#define ID_COMBOBOX_FIRSTNAME		11
#define ID_COMBOBOX_GROUP			12
#define ID_COMBOBOX_AVERAGESCORE	13
#define ID_COMBOBOX_RATING			14
#define ID_COMBOBOX_INFORMATICS		15
#define ID_COMBOBOX_MATH			16
#define ID_COMBOBOX_FOREIGNLANGUAGE 17

#define ID_BUTTON_EDIT_1	101
#define ID_BUTTON_DELETE_1	201 
#define ID_BUTTON_EDIT_2	102
#define ID_BUTTON_DELETE_2	202 
#define ID_BUTTON_EDIT_3	103
#define ID_BUTTON_DELETE_3	203 
#define ID_BUTTON_EDIT_4	104
#define ID_BUTTON_DELETE_4	204 
#define ID_BUTTON_EDIT_5	105
#define ID_BUTTON_DELETE_5	205 
#define ID_BUTTON_EDIT_6	106
#define ID_BUTTON_DELETE_6	206 
#define ID_BUTTON_EDIT_7	107
#define ID_BUTTON_DELETE_7	207 
#define ID_BUTTON_EDIT_8	108
#define ID_BUTTON_DELETE_8	208 
#define ID_BUTTON_EDIT_9	109
#define ID_BUTTON_DELETE_9	209
#define ID_BUTTON_EDIT_10	110
#define ID_BUTTON_DELETE_10	210 
#define ID_BUTTON_EDIT_11	111
#define ID_BUTTON_DELETE_11 211 
#define ID_BUTTON_EDIT_12	112
#define ID_BUTTON_DELETE_12 212 
#define ID_BUTTON_EDIT_13	113
#define ID_BUTTON_DELETE_13 213 
#define ID_BUTTON_EDIT_14	114
#define ID_BUTTON_DELETE_14 214 
#define ID_BUTTON_EDIT_15	115
#define ID_BUTTON_DELETE_15 215 
#define ID_BUTTON_EDIT_16	116
#define ID_BUTTON_DELETE_16 216 
#define ID_BUTTON_EDIT_17	117
#define ID_BUTTON_DELETE_17 217 
#define ID_BUTTON_EDIT_18	118
#define ID_BUTTON_DELETE_18 218 
#define ID_BUTTON_EDIT_19	119
#define ID_BUTTON_DELETE_19 219
#define ID_BUTTON_EDIT_20	120
#define ID_BUTTON_DELETE_20 220 

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HDC hdc;
PAINTSTRUCT	ps;

//iNPUT ELEMENTS
//Edits
HWND hEditSecondName;
HWND hEditFirstName; 
HWND hEditGroup;
HWND hEditAverageScore;
HWND hEditAverageScoreFrom;
HWND hEditAverageScoreTo;
HWND hEditRating;
HWND hEditRatingFrom;
HWND hEditRatingTo;
HWND hEditInformatics;
HWND hEditMath;
HWND hEditForeignLanguage;
//Button
HWND hButtonInPut;
HWND hButtonEdit;
HWND hButtonSearch;
HWND hButtonNext;
HWND hButtonPrev;

HWND hComboBoxSecondName;
HWND hComboBoxFirstName;
HWND hComboBoxGroup;
HWND hComboBoxAverageScore;
HWND hComboBoxRating;
HWND hComboBoxIformatics;
HWND hComboBoxMath;
HWND hComboBoxForeignLanguage;

HWND hButtonEdit1;
HWND hButtonDelete1;
HWND hButtonEdit2;
HWND hButtonDelete2;
HWND hButtonEdit3;
HWND hButtonDelete3;
HWND hButtonEdit4;
HWND hButtonDelete4;
HWND hButtonEdit5;
HWND hButtonDelete5;
HWND hButtonEdit6;
HWND hButtonDelete6;
HWND hButtonEdit7;
HWND hButtonDelete7;
HWND hButtonEdit8;
HWND hButtonDelete8;
HWND hButtonEdit9;
HWND hButtonDelete9;
HWND hButtonEdit10;
HWND hButtonDelete10;
HWND hButtonEdit11;
HWND hButtonDelete11;
HWND hButtonEdit12;
HWND hButtonDelete12;
HWND hButtonEdit13;
HWND hButtonDelete13;
HWND hButtonEdit14;
HWND hButtonDelete14;
HWND hButtonEdit15;
HWND hButtonDelete15;
HWND hButtonEdit16;
HWND hButtonDelete16;
HWND hButtonEdit17;
HWND hButtonDelete17;
HWND hButtonEdit18;
HWND hButtonDelete18;
HWND hButtonEdit19;
HWND hButtonDelete19;
HWND hButtonEdit20;
HWND hButtonDelete20;

HANDLE file;

OPENFILENAMEA ofn;
CHAR filePath[256];
DWORD read;

//Two way list
struct Node 
{
	INT		id;
	CHAR	secondName[256];
	CHAR	firstName[256];
	INT		group;
	double	averageScore;
	INT		rating;
	INT		marks[3];
	Node*	next;
	Node*	pred;
};
Node* listHead = NULL;
Node* listEnd = NULL;
Node* listCurrent = NULL;
Node* listOutPut = NULL;
Node* listSearch = NULL;

CHAR id[256];
CHAR secondName[256];
CHAR firstName[256];
CHAR group[256];
CHAR AverageScore[256];
CHAR AverageScoreFrom[256];
CHAR AverageScoreTo[256];
CHAR rating[256];
CHAR ratingFrom[256];
CHAR ratingTo[256];
CHAR markInformatics[256];
CHAR markMath[256];
CHAR markForeignLanguage[256];
CHAR numberOfOtl[256];
CHAR numberOfZd[256];

INT y				= 0;
INT fMenu			= 0;
INT lustGenratedId	= 1;
INT currentId		= 0;
INT scrol			= 0;
INT numberOfRows	= 1;
INT pageToOutPut	= 1;
INT deleteYesNo		= 0;
INT search			= 0;
INT sortFlags[8] = { 0 }; 

INT idInt;
INT groupInt;
double AverageScoreDouble;
INT ratingInt;
INT markInformaticsInt;
INT markMathInt;
INT markForeignLanguageInt;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass				(HINSTANCE hInstance);
BOOL                InitInstance				(HINSTANCE, INT);
LRESULT CALLBACK    WndProc						(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About						(HWND, UINT, WPARAM, LPARAM);
VOID				AddToList					(INT, CHAR*, CHAR*, INT, double, INT, INT, INT, INT);
INT					GetId						();
VOID				EditRecord					(Node*, CHAR*, CHAR*, INT, double, INT, INT, INT, INT);
Node*				DeleteRecord				(Node*, Node*);
Node*				SearchInList				(Node*, CHAR*, CHAR*, INT, double, double, INT, INT, INT, INT, INT);
INT					ListRecordCount				(Node*);
Node*				CopyRecord					(Node*);
Node*				ListSort					(Node*);
Node*				ListSort					(Node*);
Node*				InsertElemt					(Node*, Node*);
INT					CompareRecords				(Node*, Node*);
INT					NumberOfOtl					(Node*);
INT					NumberOfZd					(Node*);
VOID				DeleteList					(Node*);
VOID				CreateInPutMenu				(HWND);
VOID				CreateEditMenu				(HWND, CHAR*, CHAR*, INT, double, INT, INT, INT, INT);
VOID				CreateSearchMenu			(HWND);
VOID				CreateOutPutButtons			(HWND, INT, INT);
VOID				CreateSearchOutPutButtons	(HWND, INT, INT);
VOID				CreateSortBar				(HWND);
VOID				ResetSortBar				();
VOID				EditFn						(HWND, INT);
VOID				DeliteFn					(HWND, INT);
VOID				RedrawAfterDelete			(HWND);
VOID				DestroyMenu					();
VOID				DestroyOutPutButtons		();
VOID				DestroySortBar				();
INT_PTR CALLBACK	DeleteYesNo					(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	numberOf					(HWND, UINT, WPARAM, LPARAM);



int APIENTRY wWinMain(_In_		HINSTANCE hInstance,
                     _In_opt_	HINSTANCE hPrevInstance,
                     _In_		LPWSTR    lpCmdLine,
                     _In_		INT       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PRACTICE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRACTICE));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PRACTICE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCEW(IDR_MENU);
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
BOOL InitInstance(HINSTANCE hInstance, INT nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 1470, 808, nullptr, nullptr, hInstance, nullptr);

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
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize		= sizeof(ofn);
		ofn.hwndOwner		= NULL;
		ofn.lpstrFile		= filePath;
		ofn.lpstrFile[0]	= '\0';
		ofn.nMaxFile		= sizeof(filePath);
		ofn.lpstrFilter		= "All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex	= 1;
		ofn.lpstrFileTitle	= NULL;
		ofn.nMaxFileTitle	= 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags			= OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		search = 0;
		fMenu = 2;
		DestroyMenu();
		DestroySortBar();
		pageToOutPut = 1;
		CreateSortBar(hWnd);
		listOutPut = listHead;
		DestroyOutPutButtons();
		CreateOutPutButtons(hWnd, pageToOutPut, ListRecordCount(listHead));
		InvalidateRect(hWnd, NULL, TRUE);
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
			switch (wmId)
			{
			case ID_SAVE:
				GetSaveFileNameA(&ofn);
				file = CreateFileA(	ofn.lpstrFile,
									GENERIC_READ | GENERIC_WRITE,
									NULL,
									NULL,
									CREATE_ALWAYS,
									FILE_ATTRIBUTE_NORMAL,
									NULL);
				WriteFile(file, &lustGenratedId, sizeof(lustGenratedId), NULL, NULL);
				listCurrent = listHead;
				while (listCurrent)
				{
					WriteFile(file, &listCurrent->id,			sizeof(listCurrent->id),			NULL, NULL);
					WriteFile(file,  listCurrent->secondName,	sizeof(listCurrent->secondName),	NULL, NULL);
					WriteFile(file,  listCurrent->firstName,	sizeof(listCurrent->firstName),		NULL, NULL);
					WriteFile(file, &listCurrent->group,		sizeof(listCurrent->group),			NULL, NULL);
					WriteFile(file, &listCurrent->averageScore, sizeof(listCurrent->averageScore),	NULL, NULL);
					WriteFile(file, &listCurrent->rating,		sizeof(listCurrent->rating),		NULL, NULL);
					WriteFile(file, &listCurrent->marks[0],		sizeof(listCurrent->marks[0]),		NULL, NULL);
					WriteFile(file, &listCurrent->marks[1],		sizeof(listCurrent->marks[1]),		NULL, NULL);
					WriteFile(file, &listCurrent->marks[2],		sizeof(listCurrent->marks[2]),		NULL, NULL);
					listCurrent = listCurrent->next;
				}
				CloseHandle(file);
				break;
			case ID_OPEN:
				DeleteList(listHead);
				listHead = NULL;
				listEnd	 = NULL;
				GetOpenFileNameA(&ofn);
				file = CreateFileA(	ofn.lpstrFile,
									GENERIC_READ | GENERIC_WRITE,
									NULL,
									NULL,
									OPEN_EXISTING,
									FILE_ATTRIBUTE_NORMAL,
									NULL);
				ReadFile(file, &lustGenratedId, sizeof(lustGenratedId), &read, NULL);
				while (read)
				{
					ReadFile(file, &idInt,					sizeof(idInt),					&read, NULL);
					ReadFile(file, &secondName,				sizeof(secondName),				&read, NULL);
					ReadFile(file, &firstName,				sizeof(firstName),				&read, NULL);
					ReadFile(file, &groupInt,				sizeof(groupInt),				&read, NULL);
					ReadFile(file, &AverageScoreDouble,		sizeof(AverageScoreDouble),		&read, NULL);
					ReadFile(file, &ratingInt,				sizeof(ratingInt),				&read, NULL);
					ReadFile(file, &markInformaticsInt,		sizeof(markInformaticsInt),		&read, NULL);
					ReadFile(file, &markMathInt,			sizeof(markMathInt),			&read, NULL);
					ReadFile(file, &markForeignLanguageInt,	sizeof(markForeignLanguageInt), &read, NULL);
					if (read)
					{
						AddToList(idInt,
								secondName,
								firstName,
								groupInt,
								AverageScoreDouble,
								ratingInt,
								markInformaticsInt,
								markMathInt,
								markForeignLanguageInt);
					}
				}
				CloseHandle(file);
				fMenu = 2;
				DestroyMenu();
				pageToOutPut = 1;
				DestroySortBar();
				CreateSortBar(hWnd);
				listOutPut = listHead;
				DestroyOutPutButtons();
				CreateOutPutButtons(hWnd, pageToOutPut, ListRecordCount(listHead));
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_INPUT:
				fMenu = 1;
				DestroyMenu();
				DestroySortBar();
				CreateInPutMenu(hWnd);
				DestroyOutPutButtons();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_INPUT:
				GetWindowTextA(hEditSecondName, secondName, 256);
				GetWindowTextA(hEditFirstName, firstName, 256);
				GetWindowTextA(hEditGroup, group, 256);
				GetWindowTextA(hEditAverageScore, AverageScore, 256);
				GetWindowTextA(hEditRating, rating, 256);
				GetWindowTextA(hEditInformatics, markInformatics, 256);
				GetWindowTextA(hEditMath, markMath, 256);
				GetWindowTextA(hEditForeignLanguage, markForeignLanguage, 256);
				AddToList(	GetId(),
							secondName, 
							firstName, 
							atoi(group), 
							atof(AverageScore), 
							atoi(rating), 
							atoi(markInformatics), 
							atoi(markMath), 
							atoi(markForeignLanguage));
				search = 0;
				fMenu = 2;
				DestroyMenu();
				DestroySortBar();
				pageToOutPut = 1;
				CreateSortBar(hWnd);
				listOutPut = listHead;
				DestroyOutPutButtons();
				CreateOutPutButtons(hWnd, pageToOutPut, ListRecordCount(listHead));
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_OUTPUT:
				search = 0;
				fMenu = 2;
				DestroyMenu();
				DestroySortBar();
				pageToOutPut = 1;
				CreateSortBar(hWnd);
				listOutPut = listHead;
				DestroyOutPutButtons();
				CreateOutPutButtons(hWnd, pageToOutPut, ListRecordCount(listHead));
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_NEXT:
				fMenu = 2;
				pageToOutPut++;
				listOutPut = listHead;
				DestroyOutPutButtons();
				CreateOutPutButtons(hWnd,pageToOutPut, ListRecordCount(listHead));
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_PREV:
				fMenu = 2;
				pageToOutPut--;
				listOutPut = listHead;
				DestroyOutPutButtons();
				CreateOutPutButtons(hWnd, pageToOutPut, ListRecordCount(listHead));
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_SEARCH_NEXT:
				fMenu = 2;
				pageToOutPut++;
				listOutPut = listSearch;
				DestroyOutPutButtons();
				CreateSearchOutPutButtons(hWnd, pageToOutPut, ListRecordCount(listSearch));
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_SEARCH_PREV:
				fMenu = 2;
				pageToOutPut--;
				listOutPut = listSearch;
				DestroyOutPutButtons();
				CreateSearchOutPutButtons(hWnd, pageToOutPut, ListRecordCount(listSearch));
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_EDIT_1:
				fMenu = 1;
				DestroySortBar();
				listCurrent = listHead;
				EditFn(hWnd, 1);
				DestroyOutPutButtons();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_EDIT_2:
				listCurrent = listHead;
				DestroySortBar();
				EditFn(hWnd, 2);
				fMenu = 1;
				DestroyOutPutButtons();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_EDIT_3:
				listCurrent = listHead;
				DestroySortBar();
				EditFn(hWnd, 3);
				fMenu = 1;
				DestroyOutPutButtons();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_EDIT_4:
				listCurrent = listHead;
				DestroySortBar();
				EditFn(hWnd, 4);
				fMenu = 1;
				DestroyOutPutButtons();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_EDIT_5:
				listCurrent = listHead;
				DestroySortBar();
				EditFn(hWnd, 5);
				fMenu = 1;
				DestroyOutPutButtons();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_EDIT_6:
				listCurrent = listHead;
				DestroySortBar();
				EditFn(hWnd, 6);
				fMenu = 1;
				DestroyOutPutButtons();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_EDIT_7:
				listCurrent = listHead;
				DestroySortBar();
				EditFn(hWnd, 7);
				fMenu = 1;
				DestroyOutPutButtons();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_EDIT_8:
				listCurrent = listHead;
				DestroySortBar();
				EditFn(hWnd, 8);
				fMenu = 1;
				DestroyOutPutButtons();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_EDIT_9:
				listCurrent = listHead;
				DestroySortBar();
				EditFn(hWnd, 9);
				fMenu = 1;
				DestroyOutPutButtons();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_EDIT_10:
				listCurrent = listHead;
				DestroySortBar();
				EditFn(hWnd, 10);
				fMenu = 1;
				DestroyOutPutButtons();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_EDIT_11:
				listCurrent = listHead;
				DestroySortBar();
				EditFn(hWnd, 11);
				fMenu = 1;
				DestroyOutPutButtons();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_EDIT_12:
				listCurrent = listHead;
				DestroySortBar();
				EditFn(hWnd, 12);
				fMenu = 1;
				DestroyOutPutButtons();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_EDIT_13:
				listCurrent = listHead;
				DestroySortBar();
				EditFn(hWnd, 13);
				fMenu = 1;
				DestroyOutPutButtons();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_EDIT_14:
				listCurrent = listHead;
				DestroySortBar();
				EditFn(hWnd, 14);
				fMenu = 1;
				DestroyOutPutButtons();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_EDIT_15:
				listCurrent = listHead;
				DestroySortBar();
				EditFn(hWnd, 15);
				fMenu = 1;
				DestroyOutPutButtons();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_EDIT_16:
				listCurrent = listHead;
				DestroySortBar();
				EditFn(hWnd, 61);
				fMenu = 1;
				DestroyOutPutButtons();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_EDIT_17:
				listCurrent = listHead;
				DestroySortBar();
				EditFn(hWnd, 17);
				fMenu = 1;
				DestroyOutPutButtons();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_EDIT_18:
				listCurrent = listHead;
				DestroySortBar();
				EditFn(hWnd, 18);
				fMenu = 1;
				DestroyOutPutButtons();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_EDIT_19:
				listCurrent = listHead;
				DestroySortBar();
				EditFn(hWnd, 19);
				fMenu = 1;
				DestroyOutPutButtons();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_EDIT_20:
				listCurrent = listHead;
				DestroySortBar();
				EditFn(hWnd, 20);
				fMenu = 1;
				DestroyOutPutButtons();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_EDIT:
				GetWindowTextA(hEditSecondName, secondName, 256);
				GetWindowTextA(hEditFirstName, firstName, 256);
				GetWindowTextA(hEditGroup, group, 256);
				GetWindowTextA(hEditAverageScore, AverageScore, 256);
				GetWindowTextA(hEditRating, rating, 256);
				GetWindowTextA(hEditInformatics, markInformatics, 256);
				GetWindowTextA(hEditMath, markMath, 256);
				GetWindowTextA(hEditForeignLanguage, markForeignLanguage, 256);
				EditRecord(	listCurrent,
							secondName,
							firstName,
							atoi(group),
							atof(AverageScore),
							atoi(rating),
							atoi(markInformatics),
							atoi(markMath),
							atoi(markForeignLanguage));
				DestroyMenu();

				fMenu = 2;
				DestroyMenu();
				CreateSortBar(hWnd);
				listOutPut = listHead;
				DestroyOutPutButtons();
				CreateOutPutButtons(hWnd, pageToOutPut, ListRecordCount(listHead));
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BUTTON_DELETE_1:
				listCurrent = listHead;
				DeliteFn(hWnd,1);
				RedrawAfterDelete(hWnd);
				break;
			case ID_BUTTON_DELETE_2:
				listCurrent = listHead;
				DeliteFn(hWnd, 2);
				RedrawAfterDelete(hWnd);
				break;
			case ID_BUTTON_DELETE_3:
				listCurrent = listHead;
				DeliteFn(hWnd, 3);
				RedrawAfterDelete(hWnd);
				break;
			case ID_BUTTON_DELETE_4:
				listCurrent = listHead;
				DeliteFn(hWnd, 4);
				RedrawAfterDelete(hWnd);
				break;
			case ID_BUTTON_DELETE_5:
				listCurrent = listHead;
				DeliteFn(hWnd, 5);
				RedrawAfterDelete(hWnd);
				break;
			case ID_BUTTON_DELETE_6:
				listCurrent = listHead;
				DeliteFn(hWnd, 6);
				RedrawAfterDelete(hWnd);
				break;
			case ID_BUTTON_DELETE_7:
				listCurrent = listHead;
				DeliteFn(hWnd, 7);
				RedrawAfterDelete(hWnd);
				break;
			case ID_BUTTON_DELETE_8:
				listCurrent = listHead;
				DeliteFn(hWnd, 8);
				RedrawAfterDelete(hWnd);
				break;
			case ID_BUTTON_DELETE_9:
				listCurrent = listHead;
				DeliteFn(hWnd, 9);
				RedrawAfterDelete(hWnd);
				break;
			case ID_BUTTON_DELETE_10:
				listCurrent = listHead;
				DeliteFn(hWnd, 10);
				RedrawAfterDelete(hWnd);
				break;
			case ID_BUTTON_DELETE_11:
				listCurrent = listHead;
				DeliteFn(hWnd, 11);
				RedrawAfterDelete(hWnd);
				break;
			case ID_BUTTON_DELETE_12:
				listCurrent = listHead;
				DeliteFn(hWnd, 12);
				RedrawAfterDelete(hWnd);
				break;
			case ID_BUTTON_DELETE_13:
				listCurrent = listHead;
				DeliteFn(hWnd, 13);
				RedrawAfterDelete(hWnd);
				break;
			case ID_BUTTON_DELETE_14:
				listCurrent = listHead;
				DeliteFn(hWnd, 14);
				RedrawAfterDelete(hWnd);
				break;
			case ID_BUTTON_DELETE_15:
				listCurrent = listHead;
				DeliteFn(hWnd, 15);
				RedrawAfterDelete(hWnd);
				break;
			case ID_BUTTON_DELETE_16:
				listCurrent = listHead;
				DeliteFn(hWnd, 16);
				RedrawAfterDelete(hWnd);
				break;
			case ID_BUTTON_DELETE_17:
				listCurrent = listHead;
				DeliteFn(hWnd, 17);
				RedrawAfterDelete(hWnd);
				break;
			case ID_BUTTON_DELETE_18:
				listCurrent = listHead;
				DeliteFn(hWnd, 18);
				RedrawAfterDelete(hWnd);
				break;
			case ID_BUTTON_DELETE_19:
				listCurrent = listHead;
				DeliteFn(hWnd, 19);
				RedrawAfterDelete(hWnd);
				break;
			case ID_BUTTON_DELETE_20:
				listCurrent = listHead;
				DeliteFn(hWnd, 20);
				RedrawAfterDelete(hWnd);
				break;
			case ID_SEARCH:
				DestroyOutPutButtons();
				DestroySortBar();
				DestroyMenu();
				fMenu = 3;
				InvalidateRect(hWnd, NULL, TRUE);
				CreateSearchMenu(hWnd);
				break;
			case ID_BUTTON_SEARCH:
				GetWindowTextA(hEditSecondName, secondName, 256);
				GetWindowTextA(hEditFirstName, firstName, 256);
				GetWindowTextA(hEditGroup, group, 256);
				GetWindowTextA(hEditAverageScoreFrom, AverageScoreFrom, 256);
				GetWindowTextA(hEditAverageScoreTo, AverageScoreTo, 256);
				GetWindowTextA(hEditRatingFrom, ratingFrom, 256);
				GetWindowTextA(hEditRatingTo, ratingTo, 256);
				GetWindowTextA(hEditInformatics, markInformatics, 256);
				GetWindowTextA(hEditMath, markMath, 256);
				GetWindowTextA(hEditForeignLanguage, markForeignLanguage, 256);
				listSearch = listHead;
				listSearch = SearchInList(	listSearch,
											secondName,
											firstName,
											atoi(group),
											atof(AverageScoreFrom),
											atof(AverageScoreTo),
											atoi(ratingFrom),
											atoi(ratingTo),
											atoi(markInformatics),
											atoi(markMath),
											atoi(markForeignLanguage));
				fMenu = 2;
				search = 1;
				pageToOutPut = 1;
				DestroyMenu();
				listOutPut = listSearch;
				DestroyOutPutButtons();
				CreateSortBar(hWnd);
				CreateSearchOutPutButtons(hWnd, pageToOutPut, ListRecordCount(listSearch));
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_COMBOBOX_SECONDNAME:
				if (HIWORD(wParam) == CBN_SELCHANGE)
				{	
					for (INT i = 0; i < 8; i++) sortFlags[i] = 0;
					sortFlags[0] = SendMessage(hComboBoxSecondName, CB_GETCURSEL, NULL, NULL);
					if (!search)
					{
						listHead = ListSort(listHead);
						listOutPut = listHead;
					}
					else
					{
						listSearch = ListSort(listSearch);
						listOutPut = listSearch;
					}
					fMenu = 2;
					ResetSortBar();
					InvalidateRect(hWnd, NULL, TRUE);
				}
				break;
			case ID_COMBOBOX_FIRSTNAME:
				if (HIWORD(wParam) == CBN_SELCHANGE)
				{
					for (INT i = 0; i < 8; i++) sortFlags[i] = 0;
					sortFlags[1] = SendMessage(hComboBoxFirstName, CB_GETCURSEL, NULL, NULL);
					if (!search)
					{
						listHead = ListSort(listHead);
						listOutPut = listHead;
					}
					else
					{
						listSearch = ListSort(listSearch);
						listOutPut = listSearch;
					}
					fMenu = 2;
					ResetSortBar();
					InvalidateRect(hWnd, NULL, TRUE);
				}
				break;
			case ID_COMBOBOX_GROUP:
				if (HIWORD(wParam) == CBN_SELCHANGE)
				{
					for (INT i = 0; i < 8; i++) sortFlags[i] = 0;
					sortFlags[2] = SendMessage(hComboBoxGroup, CB_GETCURSEL, NULL, NULL);
					if (!search)
					{
						listHead = ListSort(listHead);
						listOutPut = listHead;
					}
					else
					{
						listSearch = ListSort(listSearch);
						listOutPut = listSearch;
					}
					fMenu = 2;
					ResetSortBar();
					InvalidateRect(hWnd, NULL, TRUE);
				}
				break;
			case ID_COMBOBOX_AVERAGESCORE:
				if (HIWORD(wParam) == CBN_SELCHANGE)
				{
					for (INT i = 0; i < 8; i++) sortFlags[i] = 0;
					sortFlags[3] = SendMessage(hComboBoxAverageScore, CB_GETCURSEL, NULL, NULL);
					if (!search)
					{
						listHead = ListSort(listHead);
						listOutPut = listHead;
					}
					else
					{
						listSearch = ListSort(listSearch);
						listOutPut = listSearch;
					}
					fMenu = 2;
					ResetSortBar();
					InvalidateRect(hWnd, NULL, TRUE);
				}
				break;
			case ID_COMBOBOX_RATING:
				if (HIWORD(wParam) == CBN_SELCHANGE)
				{
					for (INT i = 0; i < 8; i++) sortFlags[i] = 0;
					sortFlags[4] = SendMessage(hComboBoxRating, CB_GETCURSEL, NULL, NULL);
					if (!search)
					{
						listHead = ListSort(listHead);
						listOutPut = listHead;
					}
					else
					{
						listSearch = ListSort(listSearch);
						listOutPut = listSearch;
					}
					fMenu = 2;
					ResetSortBar();
					InvalidateRect(hWnd, NULL, TRUE);
				}
				break;
			case ID_COMBOBOX_INFORMATICS:
				if (HIWORD(wParam) == CBN_SELCHANGE)
				{
					for (INT i = 0; i < 8; i++) sortFlags[i] = 0;
					sortFlags[5] = SendMessage(hComboBoxIformatics, CB_GETCURSEL, NULL, NULL);
					if (!search)
					{
						listHead = ListSort(listHead);
						listOutPut = listHead;
					}
					else
					{
						listSearch = ListSort(listSearch);
						listOutPut = listSearch;
					}
					fMenu = 2;
					ResetSortBar();
					InvalidateRect(hWnd, NULL, TRUE);
				}
				break;
			case ID_COMBOBOX_MATH:
				if (HIWORD(wParam) == CBN_SELCHANGE)
				{
					for (INT i = 0; i < 8; i++) sortFlags[i] = 0;
					sortFlags[6] = SendMessage(hComboBoxMath, CB_GETCURSEL, NULL, NULL);
					if (!search)
					{
						listHead = ListSort(listHead);
						listOutPut = listHead;
					}
					else
					{
						listSearch = ListSort(listSearch);
						listOutPut = listSearch;
					}
					fMenu = 2;
					ResetSortBar();
					InvalidateRect(hWnd, NULL, TRUE);
				}
				break;
			case ID_COMBOBOX_FOREIGNLANGUAGE:
				if (HIWORD(wParam) == CBN_SELCHANGE)
				{
					for (INT i = 0; i < 8; i++) sortFlags[i] = 0;
					sortFlags[7] = SendMessage(hComboBoxForeignLanguage, CB_GETCURSEL, NULL, NULL);
					if (!search)
					{
						listHead = ListSort(listHead);
						listOutPut = listHead;
					}
					else
					{
						listSearch = ListSort(listSearch);
						listOutPut = listSearch;
					}
					fMenu = 2;
					ResetSortBar();
					InvalidateRect(hWnd, NULL, TRUE);
				}
				break;
			case ID_CALC:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_NUMBEROF), hWnd, numberOf);
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            //PAINTSTRUCT ps;
            hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
				
			switch (fMenu)
			{
			case 1:
				TextOutA(hdc, 20, 20, "Фамилия", 8);
				TextOutA(hdc, 20, 50, "Имя", 4);
				TextOutA(hdc, 20, 80, "Группа", 7);
				TextOutA(hdc, 20, 110, "Средний бал за предыдушию сесию", 32);
				TextOutA(hdc, 20, 140, "Рейтинг", 8);
				TextOutA(hdc, 20, 170, "Иформатика", 11);
				TextOutA(hdc, 20, 200, "Математика", 11);
				TextOutA(hdc, 20, 230, "Иностранный язык", 17);
				break;
			case 2:
				y = 75;
				numberOfRows = 1;
				MoveToEx(hdc, 15,	15, NULL);
				LineTo	(hdc, 15,	45);
				MoveToEx(hdc, 185,	15, NULL);
				LineTo	(hdc, 185,	45);
				MoveToEx(hdc, 355,	15, NULL);
				LineTo	(hdc, 355,	45 );
				MoveToEx(hdc, 475,	15, NULL);
				LineTo	(hdc, 475,	45 );
				MoveToEx(hdc, 735,	15, NULL);
				LineTo	(hdc, 735,	45);
				MoveToEx(hdc, 855,	15, NULL);
				LineTo	(hdc, 855,	45);
				MoveToEx(hdc, 975,	15 , NULL);
				LineTo	(hdc, 975,	45 );
				MoveToEx(hdc, 1095, 15 , NULL);
				LineTo	(hdc, 1095, 45);
				MoveToEx(hdc, 1235, 15, NULL);
				LineTo	(hdc, 1235, 45);
				MoveToEx(hdc, 15,	15, NULL);
				LineTo	(hdc, 1235, 15);
				MoveToEx(hdc, 15,	45, NULL);
				LineTo	(hdc, 1235, 45);
				MoveToEx(hdc, 15,	y - 5, NULL);
				LineTo	(hdc, 1235, y - 5);
				TextOutA(hdc, 20,	20, "Фамилия", 8);
				TextOutA(hdc, 190,	20, "Имя", 4);
				TextOutA(hdc, 360,	20, "Группа", 7);
				TextOutA(hdc, 479,	20, "Средний бал за предыдушию сесию", 32);
				TextOutA(hdc, 740,	20, "Рейтинг", 8);
				TextOutA(hdc, 860,	20, "Иформатика", 11);
				TextOutA(hdc, 980,	20, "Математика", 11);
				TextOutA(hdc, 1100, 20, "Иностранный язык", 17);
				listCurrent = listOutPut;
				for (INT i = 0; i < 20 * (pageToOutPut - 1); i++)
				{
					listCurrent = listCurrent->next;
				}
				for (INT i = 0; ((i < 20)&(listCurrent != NULL)); i++)
				{
					MoveToEx(hdc, 15,	y - 5, NULL);
					LineTo	(hdc, 15,	y + 25);
					MoveToEx(hdc, 185,	y - 5, NULL);
					LineTo	(hdc, 185,	y + 25);
					MoveToEx(hdc, 355,	y - 5, NULL);
					LineTo	(hdc, 355,	y + 25);
					MoveToEx(hdc, 475,	y - 5, NULL);
					LineTo	(hdc, 475,	y + 25);
					MoveToEx(hdc, 735,	y - 5, NULL);
					LineTo	(hdc, 735,	y + 25);
					MoveToEx(hdc, 855,	y - 5, NULL);
					LineTo	(hdc, 855,	y + 25);
					MoveToEx(hdc, 975,	y - 5, NULL);
					LineTo	(hdc, 975,	y + 25);
					MoveToEx(hdc, 1095, y - 5, NULL);
					LineTo	(hdc, 1095, y + 25);
					MoveToEx(hdc, 1235, y - 5, NULL);
					LineTo	(hdc, 1235, y + 25);
					MoveToEx(hdc, 15,	y + 25, NULL);
					LineTo	(hdc, 1235, y + 25);
					TextOutA(hdc, 20,  y, listCurrent->secondName, strlen(listCurrent->secondName));
					TextOutA(hdc, 190, y, listCurrent->firstName, strlen(listCurrent->firstName));
					if (listCurrent->group)
					{
						_itoa_s(listCurrent->group, group, 10);
						TextOutA(hdc, 360, y, group, strlen(group));
					}
					if (listCurrent->averageScore)
					{
						_gcvt_s(AverageScore, listCurrent->averageScore, 10);
						TextOutA(hdc, 480, y, AverageScore, strlen(AverageScore));
					}
					if (listCurrent->rating) 
					{
						_itoa_s(listCurrent->rating, rating, 10);
						TextOutA(hdc, 740, y, rating, strlen(rating));
					}
					if (listCurrent->marks[0])
					{
						_itoa_s(listCurrent->marks[0], markInformatics, 10);
						TextOutA(hdc, 860, y, markInformatics, strlen(markInformatics));
					}
					if (listCurrent->marks[1])
					{
						_itoa_s(listCurrent->marks[1], markMath, 10);
						TextOutA(hdc, 980, y, markMath, strlen(markMath));
					}
					if (listCurrent->marks[2])
					{
						_itoa_s(listCurrent->marks[2], markForeignLanguage, 10);
						TextOutA(hdc, 1100, y, markForeignLanguage, strlen(markForeignLanguage));
					}
					listCurrent = listCurrent->next;
					y += 30;
					numberOfRows++;
				}
				break;
			case 3:
				TextOutA(hdc, 20,	20, "Фамилия", 8);
				TextOutA(hdc, 20,	50, "Имя", 4);
				TextOutA(hdc, 20,	80, "Группа", 7);
				TextOutA(hdc, 20,	110, "Средний бал за предыдушию сесию", 32);
				TextOutA(hdc, 300,	110, "От", 3);
				TextOutA(hdc, 440,	110, "До", 3);
				TextOutA(hdc, 20,	140, "Рейтинг", 8);
				TextOutA(hdc, 300,	140, "От", 3);
				TextOutA(hdc, 440,	140, "До", 3);
				TextOutA(hdc, 20,	170, "Иформатика", 11);
				TextOutA(hdc, 20,	200, "Математика", 11);
				TextOutA(hdc, 20,	230, "Иностранный язык", 17);
				break;
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

VOID AddToList(	INT id,
				CHAR*	secondName,
				CHAR*	firstName,
				INT		group,
				double	averageScore,
				INT		rating,
				INT		marks0,
				INT		marks1,
				INT		marks2)
{
	Node *tmp = new Node;
	tmp->id				= id;
	strcpy_s(tmp->secondName, secondName);
	strcpy_s(tmp->firstName, firstName);
	tmp->group			= group;
	tmp->averageScore	= averageScore;
	tmp->rating			= rating;
	tmp->marks[0]		= marks0;
	tmp->marks[1]		= marks1;
	tmp->marks[2]		= marks2;
	tmp->next			= NULL;
	if (listEnd)
	{
		tmp->pred = listEnd;
		listEnd->next = tmp;
		listEnd = tmp;
	}
	else
	{
		listHead = tmp;
		listEnd = tmp;
	}
}

INT GetId()
{
	return lustGenratedId++;
}

VOID EditRecord(Node *head, CHAR*	secondName,
							CHAR*	firstName,
							INT		group,
							double	averageScore,
							INT		rating,
							INT		marks0,
							INT		marks1,
							INT		marks2)
{
	strcpy_s(head->secondName, secondName);
	strcpy_s(head->firstName, firstName);
	head->group = group;
	head->averageScore = averageScore;
	head->rating = rating;
	head->marks[0] = marks0;
	head->marks[1] = marks1;
	head->marks[2] = marks2;
}

Node* DeleteRecord(Node *head, Node *del)
{
	if (head == del)
	{
		if (head->next == NULL) 
		{	
			head->next = NULL;
			head->pred = NULL;
			delete head;
			head = NULL;
		}
		else
		{
			head = head->next;
			head->pred->pred = NULL;
			head->pred->next = NULL;
			delete head->pred;
			head->pred = NULL;
		}
	}
	else
	{	
		if (del->next == NULL)
		{
			Node *tmp = del;
			del->pred->next = NULL;
			tmp->pred = NULL;
			delete tmp;
		}
		else
		{
			Node *tmp = del;
			del->pred->next = del->next;
			del->next->pred = del->pred;
			tmp->next = NULL;
			tmp->pred = NULL;
			delete tmp;
		}
	}
	return head;
}

Node* SearchInList(Node *head,	CHAR*	secondName,
								CHAR*	firstName,
								INT		group,
								double	averageScoreFrom,
								double	averageScoreTo,
								INT		ratingFrom,
								INT		ratingTo,
								INT		marks0,
								INT		marks1,
								INT		marks2)
{
	Node *tmpH = NULL;
	Node *tmp = NULL;
	while (head)
	{
		if (((secondName[0] == '\0')	| !strcmp(head->secondName, secondName))	&
			((firstName[0] == '\0')		| !strcmp(head->firstName, firstName))		&
			((group == 0)				| (head->group == group))					&
			((averageScoreFrom == 0)	| (head->averageScore >= averageScoreFrom)) &
			((averageScoreTo == 0)		| (head->averageScore <= averageScoreTo))	&
			((ratingFrom == 0)			| (head->rating >= ratingFrom))				&
			((ratingTo == 0)			| (head->rating <= ratingTo))				&
			((marks0 == 0)				| (head->marks[0] == marks0))				&
			((marks1 == 0)				| (head->marks[1] == marks1))				&
			((marks2 == 0)				| (head->marks[2] == marks2)))
		{
			tmp = CopyRecord(head);
			tmp->next = tmpH;
			if (tmpH) tmpH->pred = tmp;
			tmpH = tmp;
		}
		head = head->next;
	}
	return tmpH;
}

INT ListRecordCount(Node *head)
{
	INT count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return count;
}

Node* CopyRecord(Node* elem)
{
	Node* tmp = new Node;
	tmp->id				= elem->id;
	strcpy_s(tmp->secondName,  elem->secondName);
	strcpy_s(tmp->firstName,  elem->firstName);
	tmp->group			= elem->group;
	tmp->averageScore	= elem->averageScore;
	tmp->rating			= elem->rating;
	tmp->marks[0]		= elem->marks[0];
	tmp->marks[1]		= elem->marks[1];
	tmp->marks[2]		= elem->marks[2];
	tmp->next = NULL;
	tmp->pred = NULL;
	return tmp;
}

Node* ListSort(Node* head)
{
	if (head == NULL)
	{
		return NULL;
	}
	else
	{
		head = InsertElemt(head, ListSort(head->next));
		return head;
	}
}

Node* InsertElemt(Node* elem, Node* list)
{
	if (list == NULL)
	{
		elem->pred = NULL;
		elem->next = NULL;
		listEnd = elem;
		return elem;
	}
	else if (CompareRecords(elem, list))
	{
		elem->next = list;
		list->pred = elem;
		return elem;
	}
	else
	{
		list->next = InsertElemt(elem, list->next);
		list->next->pred = list;
		return list;
	}
}

INT CompareRecords(Node* r1, Node* r2)
{
	if (sortFlags[0] == 2)
	{
		return strcmp(r1->secondName, r2->secondName) > 0;
	}
	else if (sortFlags[0] == 1)
	{
		return strcmp(r2->secondName, r1->secondName) > 0;
	}
	else if (sortFlags[1] == 2)
	{
		return strcmp(r1->firstName, r2->firstName) > 0;
	}
	else if (sortFlags[1] == 1)
	{
		return strcmp(r2->firstName, r1->firstName) > 0;
	}
	else if (sortFlags[2] == 2)
	{
		return r1->group > r2->group;
	}
	else if (sortFlags[2] == 1)
	{
		return r1->group < r2->group;
	}
	else if (sortFlags[3] == 2)
	{
		return r1->averageScore > r2->averageScore;
	}
	else if (sortFlags[3] == 1)
	{
		return r1->averageScore < r2->averageScore;
	}
	else if (sortFlags[4] == 2)
	{
		return r1->rating > r2->rating;
	}
	else if (sortFlags[4] == 1)
	{
		return r1->rating < r2->rating;
	}
	else if (sortFlags[5] == 2)
	{
		return r1->marks[0] > r2->marks[0];
	}
	else if (sortFlags[5] == 1)
	{
		return r1->marks[0] < r2->marks[0];
	}
	else if (sortFlags[6] == 2)
	{
		return r1->marks[1] > r2->marks[1];
	}
	else if (sortFlags[6] == 1)
	{
		return r1->marks[1] < r2->marks[1];
	}
	else if (sortFlags[7] == 2)
	{
		return r1->marks[2] > r2->marks[2];
	}
	else if (sortFlags[7] == 1)
	{
		return r1->marks[2] < r2->marks[2];
	}
	else
	{
		return r1->id < r2->id;
	}
}

INT NumberOfOtl(Node* head)
{
	INT count = 0;
	while (head)
	{
		if ((head->marks[0] == 5) & (head->marks[1] == 5) & (head->marks[2] == 5))
		{
			count++;
		}
		head = head->next;
	}
	return count;
}

INT NumberOfZd(Node* head)
{
	INT count = 0;
	while (head)
	{
		if ((head->marks[0] < 3) | (head->marks[1] < 3) | (head->marks[2] < 3))
		{
			count++;
		}
		head = head->next;
	}
	return count;
}

VOID DeleteList(Node* head)
{	
	if (head != NULL)
	{
		DeleteList(head->next);
		free(head);
	}
}

VOID CreateInPutMenu(HWND hWnd)
{
	hEditSecondName			= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 20,  260, 20, hWnd, NULL, NULL, NULL);
	hEditFirstName			= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 50,  260, 20, hWnd, NULL, NULL, NULL);
	hEditGroup				= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 80,  260, 20, hWnd, NULL, NULL, NULL);
	hEditAverageScore		= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 110, 260, 20, hWnd, NULL, NULL, NULL);
	hEditRating				= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 140, 260, 20, hWnd, NULL, NULL, NULL);
	hEditInformatics		= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 170, 260, 20, hWnd, NULL, NULL, NULL);
	hEditMath				= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 200, 260, 20, hWnd, NULL, NULL, NULL);
	hEditForeignLanguage	= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 230, 260, 20, hWnd, NULL, NULL, NULL);
	hButtonInPut			= CreateWindow(L"BUTTON", L"Ввести данные", WS_CHILD | WS_VISIBLE, 300, 260, 260, 40, hWnd, (HMENU)ID_BUTTON_INPUT, NULL, NULL);
}

//Create all in put elemnts
VOID CreateEditMenu(HWND	hWnd, 
					CHAR	*secondName,
					CHAR	*firstName,
					INT		group_, 
					double	averageScore_, 
					INT		rating_,
					INT		informatics_, 
					INT		math_, 
					INT		foriegnLenguage_)
{
	hEditSecondName				= CreateWindowA("EDIT", secondName, WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 20, 260, 20, hWnd, NULL, NULL, NULL);
	hEditFirstName				= CreateWindowA("EDIT", firstName, WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 50, 260, 20, hWnd, NULL, NULL, NULL);
	if (group_)
	{
		_itoa_s(group_, group, 10);
		hEditGroup				= CreateWindowA("EDIT", group, WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 80, 260, 20, hWnd, NULL, NULL, NULL);
	}
	else
	{
		hEditGroup				= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 80, 260, 20, hWnd, NULL, NULL, NULL);
	}
	if (averageScore_)
	{
		_gcvt_s(AverageScore, averageScore_, 10);
		hEditAverageScore		= CreateWindowA("EDIT", AverageScore, WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 110, 260, 20, hWnd, NULL, NULL, NULL);
	}
	else
	{
		hEditAverageScore		= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 110, 260, 20, hWnd, NULL, NULL, NULL);
	}
	if (rating_)
	{
		_itoa_s(rating_, rating, 10);
		hEditRating				= CreateWindowA("EDIT", rating, WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 140, 260, 20, hWnd, NULL, NULL, NULL);
	}
	else
	{
		hEditRating				= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 140, 260, 20, hWnd, NULL, NULL, NULL);
	}
	if (informatics_)
	{
		_itoa_s(informatics_, markInformatics, 10);
		hEditInformatics		= CreateWindowA("EDIT", markInformatics, WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 170, 260, 20, hWnd, NULL, NULL, NULL);
	}
	else
	{
		hEditInformatics		= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 170, 260, 20, hWnd, NULL, NULL, NULL);
	}
	if (math_)
	{
		_itoa_s(listCurrent->marks[1], markMath, 10);
		hEditMath				= CreateWindowA("EDIT", markMath, WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 200, 260, 20, hWnd, NULL, NULL, NULL);
	}
	else
	{
		hEditMath				= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 200, 260, 20, hWnd, NULL, NULL, NULL);
	}
	if (foriegnLenguage_)
	{
		_itoa_s(listCurrent->marks[2], markForeignLanguage, 10);
		hEditForeignLanguage	= CreateWindowA("EDIT", markForeignLanguage, WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 230, 260, 20, hWnd, NULL, NULL, NULL);
	}
	else
	{
		hEditForeignLanguage	= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 230, 260, 20, hWnd, NULL, NULL, NULL);
	}
	hButtonEdit					= CreateWindow(L"BUTTON", L"Сохранить изменения", WS_CHILD | WS_VISIBLE, 300, 260, 260, 40, hWnd, (HMENU)ID_BUTTON_EDIT, NULL, NULL);
}

VOID CreateSearchMenu(HWND hWnd)
{
	hEditSecondName			= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 20,  260, 20, hWnd, NULL, NULL, NULL);
	hEditFirstName			= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 50,  260, 20, hWnd, NULL, NULL, NULL);
	hEditGroup				= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 80,  260, 20, hWnd, NULL, NULL, NULL);
	hEditAverageScoreFrom	= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 330, 110, 90,  20, hWnd, NULL, NULL, NULL);
	hEditAverageScoreTo		= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 470, 110, 90,  20, hWnd, NULL, NULL, NULL);
	hEditRatingFrom			= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 330, 140, 90,  20, hWnd, NULL, NULL, NULL);
	hEditRatingTo			= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 470, 140, 90,  20, hWnd, NULL, NULL, NULL);
	hEditInformatics		= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 170, 260, 20, hWnd, NULL, NULL, NULL);
	hEditMath				= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 200, 260, 20, hWnd, NULL, NULL, NULL);
	hEditForeignLanguage	= CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 230, 260, 20, hWnd, NULL, NULL, NULL);
	hButtonSearch			= CreateWindow(L"BUTTON", L"Поиск", WS_CHILD | WS_VISIBLE, 300, 260, 260, 40, hWnd, (HMENU)ID_BUTTON_SEARCH, NULL, NULL);
}

VOID CreateOutPutButtons(HWND hWnd, INT page, INT totalRecordCoutn)
{
	if (totalRecordCoutn > 20)
	{
		if (page == 1)
		{
			hButtonNext = CreateWindow(L"BUTTON", L"Следуюшая страница", WS_CHILD | WS_VISIBLE, 1035, 690, 200, 40, hWnd, (HMENU)ID_BUTTON_NEXT, NULL, NULL);
		}
		else if (page == (totalRecordCoutn - 1) / 20 + 1)
		{
			hButtonPrev = CreateWindow(L"BUTTON", L"Предыдушая страница", WS_CHILD | WS_VISIBLE, 15, 690, 200, 40, hWnd, (HMENU)ID_BUTTON_PREV, NULL, NULL);
		}
		else
		{
			hButtonNext = CreateWindow(L"BUTTON", L"Следуюшая страница", WS_CHILD | WS_VISIBLE, 1035, 690, 200, 40, hWnd, (HMENU)ID_BUTTON_NEXT, NULL, NULL);
			hButtonPrev = CreateWindow(L"BUTTON", L"Предыдушая страница", WS_CHILD | WS_VISIBLE, 15, 690, 200, 40, hWnd, (HMENU)ID_BUTTON_PREV, NULL, NULL);
		}

	}
	if (totalRecordCoutn - 20 * (page - 1) >= 1)
	{
		hButtonEdit1	= CreateWindow(L"BUTTON", L"Редактировать", WS_CHILD | WS_VISIBLE, 1237, 71, 120, 28, hWnd, (HMENU)ID_BUTTON_EDIT_1, NULL, NULL);
		hButtonDelete1	= CreateWindow(L"BUTTON", L"Удалить",		WS_CHILD | WS_VISIBLE, 1357, 71, 80, 28, hWnd,	(HMENU)ID_BUTTON_DELETE_1, NULL, NULL);
	}
	if (totalRecordCoutn - 20 * (page - 1) >= 2)
	{
		hButtonEdit2	= CreateWindow(L"BUTTON", L"Редактировать", WS_CHILD | WS_VISIBLE, 1237, 101, 120, 28, hWnd, (HMENU)ID_BUTTON_EDIT_2, NULL, NULL);
		hButtonDelete2	= CreateWindow(L"BUTTON", L"Удалить",		WS_CHILD | WS_VISIBLE, 1357, 101, 80, 28, hWnd,	(HMENU)ID_BUTTON_DELETE_2, NULL, NULL);
	}
	if (totalRecordCoutn - 20 * (page - 1) >= 3)
	{
		hButtonEdit3	= CreateWindow(L"BUTTON", L"Редактировать", WS_CHILD | WS_VISIBLE, 1237, 131, 120, 28, hWnd, (HMENU)ID_BUTTON_EDIT_3, NULL, NULL);
		hButtonDelete3	= CreateWindow(L"BUTTON", L"Удалить",		WS_CHILD | WS_VISIBLE, 1357, 131, 80, 28, hWnd,	 (HMENU)ID_BUTTON_DELETE_3, NULL, NULL);
	}
	if (totalRecordCoutn - 20 * (page - 1) >= 4)
	{
		hButtonEdit4	= CreateWindow(L"BUTTON", L"Редактировать", WS_CHILD | WS_VISIBLE, 1237, 161, 120, 28, hWnd, (HMENU)ID_BUTTON_EDIT_4, NULL, NULL);
		hButtonDelete4	= CreateWindow(L"BUTTON", L"Удалить",		WS_CHILD | WS_VISIBLE, 1357, 161, 80, 28, hWnd,	 (HMENU)ID_BUTTON_DELETE_4, NULL, NULL);
	}
	if (totalRecordCoutn - 20 * (page - 1) >= 5)
	{
		hButtonEdit5	= CreateWindow(L"BUTTON", L"Редактировать", WS_CHILD | WS_VISIBLE, 1237, 191, 120, 28, hWnd, (HMENU)ID_BUTTON_EDIT_5, NULL, NULL);
		hButtonDelete5	= CreateWindow(L"BUTTON", L"Удалить",		WS_CHILD | WS_VISIBLE, 1357, 191, 80, 28, hWnd,	 (HMENU)ID_BUTTON_DELETE_5, NULL, NULL);
	}
	if (totalRecordCoutn - 20 * (page - 1) >= 6)
	{
		hButtonEdit6	= CreateWindow(L"BUTTON", L"Редактировать", WS_CHILD | WS_VISIBLE, 1237, 221, 120, 28, hWnd, (HMENU)ID_BUTTON_EDIT_6, NULL, NULL);
		hButtonDelete6	= CreateWindow(L"BUTTON", L"Удалить",		WS_CHILD | WS_VISIBLE, 1357, 221, 80, 28, hWnd,	 (HMENU)ID_BUTTON_DELETE_6, NULL, NULL);
	}
	if (totalRecordCoutn - 20 * (page - 1) >= 7)
	{
		hButtonEdit7	= CreateWindow(L"BUTTON", L"Редактировать", WS_CHILD | WS_VISIBLE, 1237, 251, 120, 28, hWnd, (HMENU)ID_BUTTON_EDIT_7, NULL, NULL);
		hButtonDelete7	= CreateWindow(L"BUTTON", L"Удалить",		WS_CHILD | WS_VISIBLE, 1357, 251, 80, 28, hWnd,	 (HMENU)ID_BUTTON_DELETE_7, NULL, NULL);
	}
	if (totalRecordCoutn - 20 * (page - 1) >= 8)
	{
		hButtonEdit8	= CreateWindow(L"BUTTON", L"Редактировать", WS_CHILD | WS_VISIBLE, 1237, 281, 120, 28, hWnd, (HMENU)ID_BUTTON_EDIT_8, NULL, NULL);
		hButtonDelete8	= CreateWindow(L"BUTTON", L"Удалить",		WS_CHILD | WS_VISIBLE, 1357, 281, 80, 28, hWnd,	 (HMENU)ID_BUTTON_DELETE_8, NULL, NULL);
	}
	if (totalRecordCoutn - 20 * (page - 1) >= 9)
	{
		hButtonEdit9	= CreateWindow(L"BUTTON", L"Редактировать", WS_CHILD | WS_VISIBLE, 1237, 311, 120, 28, hWnd, (HMENU)ID_BUTTON_EDIT_9, NULL, NULL);
		hButtonDelete9	= CreateWindow(L"BUTTON", L"Удалить",		WS_CHILD | WS_VISIBLE, 1357, 311, 80, 28, hWnd,	 (HMENU)ID_BUTTON_DELETE_9, NULL, NULL);
	}
	if (totalRecordCoutn - 20 * (page - 1) >= 10)
	{
		hButtonEdit10	= CreateWindow(L"BUTTON", L"Редактировать", WS_CHILD | WS_VISIBLE, 1237, 341, 120, 28, hWnd, (HMENU)ID_BUTTON_EDIT_10, NULL, NULL);
		hButtonDelete10	= CreateWindow(L"BUTTON", L"Удалить",		WS_CHILD | WS_VISIBLE, 1357, 341, 80, 28, hWnd,	 (HMENU)ID_BUTTON_DELETE_10, NULL, NULL);
	}
	if (totalRecordCoutn - 20 * (page - 1) >= 11)
	{
		hButtonEdit11	= CreateWindow(L"BUTTON", L"Редактировать", WS_CHILD | WS_VISIBLE, 1237, 371, 120, 28, hWnd, (HMENU)ID_BUTTON_EDIT_11, NULL, NULL);
		hButtonDelete11 = CreateWindow(L"BUTTON", L"Удалить",		WS_CHILD | WS_VISIBLE, 1357, 371, 80, 28, hWnd,	 (HMENU)ID_BUTTON_DELETE_11, NULL, NULL);
	}
	if (totalRecordCoutn - 20 * (page - 1) >= 12)
	{
		hButtonEdit12	= CreateWindow(L"BUTTON", L"Редактировать", WS_CHILD | WS_VISIBLE, 1237, 401, 120, 28, hWnd, (HMENU)ID_BUTTON_EDIT_12, NULL, NULL);
		hButtonDelete12 = CreateWindow(L"BUTTON", L"Удалить",		WS_CHILD | WS_VISIBLE, 1357, 401, 80, 28, hWnd,	 (HMENU)ID_BUTTON_DELETE_12, NULL, NULL);
	}
	if (totalRecordCoutn - 20 * (page - 1) >= 13)
	{
		hButtonEdit13	= CreateWindow(L"BUTTON", L"Редактировать", WS_CHILD | WS_VISIBLE, 1237, 431, 120, 28, hWnd, (HMENU)ID_BUTTON_EDIT_13, NULL, NULL);
		hButtonDelete13 = CreateWindow(L"BUTTON", L"Удалить",		WS_CHILD | WS_VISIBLE, 1357, 431, 80, 28, hWnd,	 (HMENU)ID_BUTTON_DELETE_13, NULL, NULL);
	}
	if (totalRecordCoutn - 20 * (page - 1) >= 14)
	{
		hButtonEdit14	= CreateWindow(L"BUTTON", L"Редактировать", WS_CHILD | WS_VISIBLE, 1237, 461, 120, 28, hWnd, (HMENU)ID_BUTTON_EDIT_14, NULL, NULL);
		hButtonDelete14 = CreateWindow(L"BUTTON", L"Удалить",		WS_CHILD | WS_VISIBLE, 1357, 461, 80, 28, hWnd,	 (HMENU)ID_BUTTON_DELETE_14, NULL, NULL);
	}
	if (totalRecordCoutn - 20 * (page - 1) >= 15)
	{
		hButtonEdit15	= CreateWindow(L"BUTTON", L"Редактировать", WS_CHILD | WS_VISIBLE, 1237, 491, 120, 28, hWnd, (HMENU)ID_BUTTON_EDIT_15, NULL, NULL);
		hButtonDelete15 = CreateWindow(L"BUTTON", L"Удалить",		WS_CHILD | WS_VISIBLE, 1357, 491, 80, 28, hWnd,	 (HMENU)ID_BUTTON_DELETE_15, NULL, NULL);
	}
	if (totalRecordCoutn - 20 * (page - 1) >= 16)
	{
		hButtonEdit16	= CreateWindow(L"BUTTON", L"Редактировать", WS_CHILD | WS_VISIBLE, 1237, 521, 120, 28, hWnd, (HMENU)ID_BUTTON_EDIT_16, NULL, NULL);
		hButtonDelete16 = CreateWindow(L"BUTTON", L"Удалить",		WS_CHILD | WS_VISIBLE, 1357, 521, 80, 28, hWnd,	 (HMENU)ID_BUTTON_DELETE_16, NULL, NULL);
	}
	if (totalRecordCoutn - 20 * (page - 1) >= 17)
	{
		hButtonEdit17	= CreateWindow(L"BUTTON", L"Редактировать", WS_CHILD | WS_VISIBLE, 1237, 551, 120, 28, hWnd, (HMENU)ID_BUTTON_EDIT_17, NULL, NULL);
		hButtonDelete17 = CreateWindow(L"BUTTON", L"Удалить",		WS_CHILD | WS_VISIBLE, 1357, 551, 80, 28, hWnd,	 (HMENU)ID_BUTTON_DELETE_17, NULL, NULL);
	}
	if (totalRecordCoutn - 20 * (page - 1) >= 18)
	{
		hButtonEdit18	= CreateWindow(L"BUTTON", L"Редактировать", WS_CHILD | WS_VISIBLE, 1237, 581, 120, 28, hWnd, (HMENU)ID_BUTTON_EDIT_18, NULL, NULL);
		hButtonDelete18 = CreateWindow(L"BUTTON", L"Удалить",		WS_CHILD | WS_VISIBLE, 1357, 581, 80, 28, hWnd,	 (HMENU)ID_BUTTON_DELETE_18, NULL, NULL);
	}
	if (totalRecordCoutn - 20 * (page - 1) >= 19)
	{
		hButtonEdit19	= CreateWindow(L"BUTTON", L"Редактировать", WS_CHILD | WS_VISIBLE, 1237, 611, 120, 28, hWnd, (HMENU)ID_BUTTON_EDIT_19, NULL, NULL);
		hButtonDelete19 = CreateWindow(L"BUTTON", L"Удалить",		WS_CHILD | WS_VISIBLE, 1357, 611, 80, 28, hWnd,	 (HMENU)ID_BUTTON_DELETE_19, NULL, NULL);
	}
	if (totalRecordCoutn - 20 * (page - 1) >= 20)
	{
		hButtonEdit20	= CreateWindow(L"BUTTON", L"Редактировать", WS_CHILD | WS_VISIBLE, 1237, 641, 120, 28, hWnd, (HMENU)ID_BUTTON_EDIT_20, NULL, NULL);
		hButtonDelete20 = CreateWindow(L"BUTTON", L"Удалить",		WS_CHILD | WS_VISIBLE, 1357, 641, 80, 28, hWnd,	 (HMENU)ID_BUTTON_DELETE_20, NULL, NULL);
	}
}

VOID CreateSearchOutPutButtons(HWND hWnd, INT page, INT totalRecordCoutn)
{
	if (totalRecordCoutn > 20)
	{
		if (page == 1)
		{
			hButtonNext = CreateWindow(L"BUTTON", L"Следуюшая страница",  WS_CHILD | WS_VISIBLE, 1015, 675, 200, 40, hWnd, (HMENU)ID_BUTTON_SEARCH_NEXT, NULL, NULL);
		}
		else if (page == (totalRecordCoutn - 1) / 20 + 1)
		{
			hButtonPrev = CreateWindow(L"BUTTON", L"Предыдушая страница", WS_CHILD | WS_VISIBLE, 15, 675, 200, 40, hWnd, (HMENU)ID_BUTTON_SEARCH_PREV, NULL, NULL);
		}
		else
		{
			hButtonNext = CreateWindow(L"BUTTON", L"Следуюшая страница",  WS_CHILD | WS_VISIBLE, 1015, 675, 200, 40, hWnd, (HMENU)ID_BUTTON_SEARCH_NEXT, NULL, NULL);
			hButtonPrev = CreateWindow(L"BUTTON", L"Предыдушая страница", WS_CHILD | WS_VISIBLE, 15,   675, 200, 40, hWnd, (HMENU)ID_BUTTON_SEARCH_PREV, NULL, NULL);
		}
	}
}

VOID CreateSortBar(HWND hWnd)
{
	hComboBoxSecondName		 = CreateWindow(L"COMBOBOX", L"-", CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE, 15,	46, 172, 80, hWnd, (HMENU)ID_COMBOBOX_SECONDNAME,		NULL, NULL);
	hComboBoxFirstName		 = CreateWindow(L"COMBOBOX", L"-", CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE, 185,	46, 172, 80, hWnd, (HMENU)ID_COMBOBOX_FIRSTNAME,		NULL, NULL);
	hComboBoxGroup			 = CreateWindow(L"COMBOBOX", L"-", CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE, 355,	46, 122, 80, hWnd, (HMENU)ID_COMBOBOX_GROUP,			NULL, NULL);
	hComboBoxAverageScore	 = CreateWindow(L"COMBOBOX", L"-", CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE, 475,	46, 262, 80, hWnd, (HMENU)ID_COMBOBOX_AVERAGESCORE,		NULL, NULL);
	hComboBoxRating			 = CreateWindow(L"COMBOBOX", L"-", CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE, 735,	46, 122, 80, hWnd, (HMENU)ID_COMBOBOX_RATING,			NULL, NULL);
	hComboBoxIformatics		 = CreateWindow(L"COMBOBOX", L"-", CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE, 855,	46, 122, 80, hWnd, (HMENU)ID_COMBOBOX_INFORMATICS,		NULL, NULL);
	hComboBoxMath			 = CreateWindow(L"COMBOBOX", L"-", CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE, 975,	46, 122, 80, hWnd, (HMENU)ID_COMBOBOX_MATH,				NULL, NULL);
	hComboBoxForeignLanguage = CreateWindow(L"COMBOBOX", L"-", CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE, 1095, 46, 142, 80, hWnd, (HMENU)ID_COMBOBOX_FOREIGNLANGUAGE,  NULL, NULL);
	SendMessageA(hComboBoxSecondName,		CB_ADDSTRING, 0, (LPARAM)"-");
	SendMessageA(hComboBoxSecondName,		CB_ADDSTRING, 0, (LPARAM)"По возрастанию");
	SendMessageA(hComboBoxSecondName,		CB_ADDSTRING, 0, (LPARAM)"По убыванию");
	SendMessageA(hComboBoxFirstName,		CB_ADDSTRING, 0, (LPARAM)"-");
	SendMessageA(hComboBoxFirstName,		CB_ADDSTRING, 0, (LPARAM)"По возрастанию");
	SendMessageA(hComboBoxFirstName,		CB_ADDSTRING, 0, (LPARAM)"По убыванию");
	SendMessageA(hComboBoxGroup,			CB_ADDSTRING, 0, (LPARAM)"-");
	SendMessageA(hComboBoxGroup,			CB_ADDSTRING, 0, (LPARAM)"По возрастанию");
	SendMessageA(hComboBoxGroup,			CB_ADDSTRING, 0, (LPARAM)"По убыванию");
	SendMessageA(hComboBoxAverageScore,		CB_ADDSTRING, 0, (LPARAM)"-");
	SendMessageA(hComboBoxAverageScore,		CB_ADDSTRING, 0, (LPARAM)"По возрастанию");
	SendMessageA(hComboBoxAverageScore,		CB_ADDSTRING, 0, (LPARAM)"По убыванию");
	SendMessageA(hComboBoxRating,			CB_ADDSTRING, 0, (LPARAM)"-");
	SendMessageA(hComboBoxRating,			CB_ADDSTRING, 0, (LPARAM)"По возрастанию");
	SendMessageA(hComboBoxRating,			CB_ADDSTRING, 0, (LPARAM)"По убыванию");
	SendMessageA(hComboBoxIformatics,		CB_ADDSTRING, 0, (LPARAM)"-");
	SendMessageA(hComboBoxIformatics,		CB_ADDSTRING, 0, (LPARAM)"По возрастанию");
	SendMessageA(hComboBoxIformatics,		CB_ADDSTRING, 0, (LPARAM)"По убыванию");
	SendMessageA(hComboBoxMath,				CB_ADDSTRING, 0, (LPARAM)"-");
	SendMessageA(hComboBoxMath,				CB_ADDSTRING, 0, (LPARAM)"По возрастанию");
	SendMessageA(hComboBoxMath,				CB_ADDSTRING, 0, (LPARAM)"По убыванию");
	SendMessageA(hComboBoxForeignLanguage,	CB_ADDSTRING, 0, (LPARAM)"-");
	SendMessageA(hComboBoxForeignLanguage,	CB_ADDSTRING, 0, (LPARAM)"По возрастанию");
	SendMessageA(hComboBoxForeignLanguage,	CB_ADDSTRING, 0, (LPARAM)"По убыванию");
	SendMessageA(hComboBoxSecondName,		CB_SETCURSEL, 0, NULL);
	SendMessageA(hComboBoxFirstName,		CB_SETCURSEL, 0, NULL);
	SendMessageA(hComboBoxGroup,			CB_SETCURSEL, 0, NULL);
	SendMessageA(hComboBoxAverageScore,		CB_SETCURSEL, 0, NULL);
	SendMessageA(hComboBoxRating,			CB_SETCURSEL, 0, NULL);
	SendMessageA(hComboBoxIformatics,		CB_SETCURSEL, 0, NULL);
	SendMessageA(hComboBoxMath,				CB_SETCURSEL, 0, NULL);
	SendMessageA(hComboBoxForeignLanguage,	CB_SETCURSEL, 0, NULL);
}

VOID ResetSortBar()
{
	if (!sortFlags[0])
	{
		SendMessageA(hComboBoxSecondName,		CB_SETCURSEL, 0, NULL);
	}
	if (!sortFlags[1])
	{
		SendMessageA(hComboBoxFirstName,		CB_SETCURSEL, 0, NULL);
	}
	if (!sortFlags[2])
	{
		SendMessageA(hComboBoxGroup,			CB_SETCURSEL, 0, NULL);
	}
	if (!sortFlags[3])
	{
		SendMessageA(hComboBoxAverageScore,		CB_SETCURSEL, 0, NULL);
	}
	if (!sortFlags[4])
	{
		SendMessageA(hComboBoxRating,			CB_SETCURSEL, 0, NULL);
	}
	if (!sortFlags[5])
	{
		SendMessageA(hComboBoxIformatics,		CB_SETCURSEL, 0, NULL);
	}
	if (!sortFlags[6])
	{
		SendMessageA(hComboBoxMath,				CB_SETCURSEL, 0, NULL);
	}
	if (!sortFlags[7])
	{
		SendMessageA(hComboBoxForeignLanguage,	CB_SETCURSEL, 0, NULL);
	}
}

VOID EditFn(HWND hWnd, INT k)
{
	for (INT i = 0; i < (pageToOutPut - 1) * 20 + k - 1; i++)
	{
		listCurrent = listCurrent->next;
	}
	CreateEditMenu(hWnd,
		listCurrent->secondName,
		listCurrent->firstName,
		listCurrent->group,
		listCurrent->averageScore,
		listCurrent->rating,
		listCurrent->marks[0],
		listCurrent->marks[1],
		listCurrent->marks[2]);
}

VOID DeliteFn(HWND hWnd, INT k)
{
	for (INT i = 0; i < (pageToOutPut - 1) * 20 + k - 1; i++)
	{
		listCurrent = listCurrent->next;
	}
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DELETE_YES_NO), hWnd, DeleteYesNo);
	if (deleteYesNo)
	{
		if (listCurrent)
		{
			listHead = DeleteRecord(listHead, listCurrent);
		}
	}
}

VOID RedrawAfterDelete(HWND hWnd)
{
	fMenu = 2;
	DestroyMenu();
	if (pageToOutPut > (ListRecordCount(listHead) - 1) / 20 + 1)
	{
		pageToOutPut--;
	}
	listOutPut = listHead;
	DestroyOutPutButtons();
	CreateOutPutButtons(hWnd, pageToOutPut, ListRecordCount(listHead));
	InvalidateRect(hWnd, NULL, TRUE);
}

//Destrou all in put elemnts
VOID DestroyMenu()
{
	DestroyWindow(hEditSecondName);
	DestroyWindow(hEditFirstName);
	DestroyWindow(hEditGroup);
	DestroyWindow(hEditAverageScore);
	DestroyWindow(hEditAverageScoreFrom);
	DestroyWindow(hEditAverageScoreTo);
	DestroyWindow(hEditRating);
	DestroyWindow(hEditRatingFrom);
	DestroyWindow(hEditRatingTo);
	DestroyWindow(hEditInformatics);
	DestroyWindow(hEditMath);
	DestroyWindow(hEditForeignLanguage);
	DestroyWindow(hButtonInPut);
	DestroyWindow(hButtonEdit);
	DestroyWindow(hButtonSearch);
}

VOID DestroyOutPutButtons()
{
	DestroyWindow(hButtonNext);
	DestroyWindow(hButtonPrev);
	DestroyWindow(hButtonEdit1);
	DestroyWindow(hButtonDelete1);
	DestroyWindow(hButtonEdit2);
	DestroyWindow(hButtonDelete2);
	DestroyWindow(hButtonEdit3);
	DestroyWindow(hButtonDelete3);
	DestroyWindow(hButtonEdit4);
	DestroyWindow(hButtonDelete4);
	DestroyWindow(hButtonEdit5);
	DestroyWindow(hButtonDelete5);
	DestroyWindow(hButtonEdit6);
	DestroyWindow(hButtonDelete6);
	DestroyWindow(hButtonEdit7);
	DestroyWindow(hButtonDelete7);
	DestroyWindow(hButtonEdit8);
	DestroyWindow(hButtonDelete8);
	DestroyWindow(hButtonEdit9);
	DestroyWindow(hButtonDelete9);
	DestroyWindow(hButtonEdit10);
	DestroyWindow(hButtonDelete10);
	DestroyWindow(hButtonEdit11);
	DestroyWindow(hButtonDelete11);
	DestroyWindow(hButtonEdit12);
	DestroyWindow(hButtonDelete12);
	DestroyWindow(hButtonEdit13);
	DestroyWindow(hButtonDelete13);
	DestroyWindow(hButtonEdit14);
	DestroyWindow(hButtonDelete14);
	DestroyWindow(hButtonEdit15);
	DestroyWindow(hButtonDelete15);
	DestroyWindow(hButtonEdit16);
	DestroyWindow(hButtonDelete16);
	DestroyWindow(hButtonEdit17);
	DestroyWindow(hButtonDelete17);
	DestroyWindow(hButtonEdit18);
	DestroyWindow(hButtonDelete18);
	DestroyWindow(hButtonEdit19);
	DestroyWindow(hButtonDelete19);
	DestroyWindow(hButtonEdit20);
	DestroyWindow(hButtonDelete20);
}
VOID DestroySortBar()
{
	DestroyWindow(hComboBoxSecondName);
	DestroyWindow(hComboBoxFirstName);
	DestroyWindow(hComboBoxGroup);
	DestroyWindow(hComboBoxAverageScore);
	DestroyWindow(hComboBoxRating);
	DestroyWindow(hComboBoxIformatics);
	DestroyWindow(hComboBoxMath);
	DestroyWindow(hComboBoxForeignLanguage);
}

INT_PTR CALLBACK DeleteYesNo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_YES:
			deleteYesNo = 1;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			break;
		case ID_NO:
			deleteYesNo = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK numberOf(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		_itoa_s(NumberOfOtl(listHead), numberOfOtl, 10);
		SetDlgItemTextA(hDlg, IDC_OTL, numberOfOtl);
		_itoa_s(NumberOfZd(listHead), numberOfZd, 10);
		SetDlgItemTextA(hDlg, IDC_ZD, numberOfZd);
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}