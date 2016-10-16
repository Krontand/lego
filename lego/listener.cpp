#include "stdafx.h"
#include "listener.h"
#include "interface\interface.h"
#include "interface\drawinterface.h"
#include "interface\button.h"
#include "interface\text.h"
#include "model\loader.h"

extern HINSTANCE hInst;
PAINTSTRUCT ps;
BaseInterface* interface;
BaseDrawInterface* drawInterface = new BaseDrawInterface;

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
		InterfaceCtrlInit CtrlInit(hWnd, hInst);
		interface = new BaseInterface;
		
		interface->button(BTN_OK)->create(10, 500, 33, 223, TEXT("OK"));
		interface->button(BTN_OK)->setImage(BTN_ADDBRICK);

		drawInterface->text(TXT_LEGO)
			->SetColor(RGB(255, 255, 255))
			->SetWeight(800)
			->SetHeight(36)
			->SetSymbolWidth(13)
			->display(20, 30, 0, 0, TEXT("LEGO"));
		drawInterface->text(TXT_DESIGNER)
			->SetColor(RGB(37, 45, 74))
			->SetWeight(400)
			->SetHeight(36)
			->SetSymbolWidth(11)
			->display(95, 30, 0, 0, TEXT("DESIGNER"));
		//interface->remove(888);
		try 
		{
			Loader test("objs/one.obj");
			Brick* brk = test.load();
		}
		catch (BaseException& err)
		{
			WCHAR msg[256];
			MultiByteToWideChar(0, 0, err.what(), 255, msg, 256);
			MessageBox(NULL, msg, TEXT("ERROR"), MB_OK);
		}
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
		HDC hdc = BeginPaint(hWnd, &ps);
		InterfaceDrawInit DrawInit(hdc);
		drawInterface->redraw();
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
