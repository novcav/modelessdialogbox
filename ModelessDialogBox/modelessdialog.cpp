//
//  Modeless Dialog Box
//

#include "stdafx.h"
#include "modelessdialog.h"

// constructor
CModelessDialog::CModelessDialog()
{
	hDialog = NULL;
}

// destructor
CModelessDialog::~CModelessDialog()
{
}

// display dialog box
void CModelessDialog::Show(HWND hWnd, HINSTANCE hInstance, DLGPROC pDlgProc)
{
	// if window already exist return
	if (IsWindow(hDialog)) return;

	// Creates a modeless dialog box from a dialog box template IDD_DIALOG1
	hDialog = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, pDlgProc);

	// show dialog box
	ShowWindow(hDialog, SW_SHOW);
}

// dialog procedure
INT_PTR CModelessDialog::DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	HWND hWnd;

	switch (message)
	{
	case WM_INITDIALOG:

	return (INT_PTR)TRUE;

	case WM_COMMAND:

		switch (LOWORD(wParam)) 
		{
                case IDOK:

					// get the text from the control
					GetDlgItemText(hDlg, IDC_EDIT1, str, 100);

					// send the data to parent window
					hWnd = GetParent(hDlg);
					SendMessage(hWnd, WM_SEND, 0, (LPARAM)str);

 					return (INT_PTR)TRUE;

                case IDCANCEL: 

					// destroy window
					DestroyWindow(hDlg); 
					hDialog = NULL;

					return (INT_PTR)TRUE;
		}
	}
	return (INT_PTR)FALSE;
}

//