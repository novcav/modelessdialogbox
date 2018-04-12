//
//  Modeless Dialog
//

#pragma once

#include "resource.h"

class CModelessDialog
{
private:
	HWND hDialog;
	wchar_t str[100];


public:
	CModelessDialog();
	~CModelessDialog();

	void Show(HWND hWnd, HINSTANCE hInstance, DLGPROC pDlgProc);
	INT_PTR DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

public:



};

