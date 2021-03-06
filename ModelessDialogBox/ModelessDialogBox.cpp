//
// Put a modeless dialog into a class
//

#include "stdafx.h"
#include "ModelessDialogBox.h"
#include "modelessdialog.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

//
wchar_t str[100];
CModelessDialog dlg;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK    WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK	DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void OnSend(HWND hWnd, WPARAM wParam, LPARAM lParam);

void OnPaint(HWND hWnd);
void OnCreate(HWND hWnd);
void OnDestroy(HWND hWnd);

void OnFileOpen(HWND hWnd, HINSTANCE hInst);
void OnFileExit(HWND hWnd);

// main window
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MODELESSDIALOGBOX, szWindowClass, MAX_LOADSTRING);

    //  Registers the window class.
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MODELESSDIALOGBOX));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MODELESSDIALOGBOX);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    RegisterClassExW(&wcex);

    // Store instance handle in our global variable.
    hInst = hInstance; 

    // Create the main program window.
    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd) return FALSE;

    // Display the main program window.
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MODELESSDIALOGBOX));

    MSG msg;

    // Main message loop
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

//  Processes messages for the main window.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_SEND: OnSend(hWnd, wParam, lParam);					break;
    case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_OPEN:  OnFileOpen(hWnd, hInst);				break;
		case IDM_EXIT:  OnFileExit(hWnd);						break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
        break;
	case WM_PAINT:   OnPaint(hWnd);									break;
	case WM_CREATE:  OnCreate(hWnd);								break;
	case WM_DESTROY: OnDestroy(hWnd);								break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for dialog box.
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	return dlg.DlgProc(hDlg, message, wParam, lParam);
}

//
void OnSend(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	wchar_t* p = (wchar_t*)lParam;

	// display text
	wcscpy_s(str, 100, p);
	InvalidateRect(hWnd, NULL, TRUE);
}

//
void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hDC;

	RECT rect;
    HFONT hFont;

	hDC = BeginPaint(hWnd, &ps);

	hFont = CreateFont(48,0,0,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Impact"));

	SelectObject(hDC, hFont);
            
	SetRect(&rect, 100,100,700,200);
	SetTextColor(hDC, RGB(255,0,0));
	DrawText(hDC, str, wcslen(str), &rect, DT_NOCLIP);

	DeleteObject(hFont); 

	EndPaint(hWnd, &ps);
}

//
void OnCreate(HWND hWnd)
{
	wcscpy_s(str, 100, L"");
}

//
void OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
}

//
void OnFileOpen(HWND hWnd, HINSTANCE hInst)
{
	// show dialog window
	dlg.Show(hWnd, hInst, DlgProc);
}

//
void OnFileExit(HWND hWnd)
{
	DestroyWindow(hWnd);
}
