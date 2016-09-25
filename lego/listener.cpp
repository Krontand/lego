#include "stdafx.h"
#include "listener.h"
#include "interface\interface.h"
#include "interface\button.h"

extern HINSTANCE hInst;
PAINTSTRUCT ps;
BaseInterface* interface;
HDC hdc;

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  process messages in main window
//
//  WM_COMMAND Ч process menu
//  WM_PAINT Ч draw main window
//  WM_DESTROY Ч send exit message
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		InterfaceItemInit(hWnd, hInst);
		interface = new BaseInterface;
		interface->button(BTN_OK)->create(10, 500, 33, 223, TEXT("OK"));
		interface->button(BTN_OK)->setImage(BTN_ADDBRICK);
		//interface->remove(888);
		
	}
	break;
	case WM_COMMAND:
	{
		SetFocus(hWnd);
		int wmId = LOWORD(wParam);
		// –азобрать выбор в меню:
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
		hdc = BeginPaint(hWnd, &ps);
		InterfaceItemInit(hdc);
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

// Handler for ABOUT window
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
