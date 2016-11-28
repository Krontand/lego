#include "stdafx.h"
#include "listener.h"
#include "interface\interface.h"
#include "interface\drawinterface.h"
#include "interface\button.h"
#include "interface\text.h"
#include "application.h"

#define ROTATTION_ANGLE 5 * M_PI / 180

extern HINSTANCE hInst;
PAINTSTRUCT ps;
BaseInterface* interface;
BaseDrawInterface* drawInterface = new BaseDrawInterface;

double angle = ROTATTION_ANGLE;

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

	try
	{
		
		static ActionDraw* actionDraw = new ActionDraw();
		static Application* application = new Application(hWnd, 270, 0, 850, 750);

		if (!application)
		{
			throw AllocationMemoryError();
		}

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
				ActionLoadbrick* LoadFirst = new ActionLoadbrick("objs/untitled.obj");
				//ActionLoadbrick* LoadFirst = new ActionLoadbrick("objs/one.obj");
				application->call(*LoadFirst, 0);

				ActionAddbrick* addBrick = new ActionAddbrick();
				application->call(*addBrick, 0);
			}
			catch (BaseException& err)
			{
				throw;
			}
		}
		break;
		case WM_COMMAND:
		case WM_KEYDOWN:
		{
			SetFocus(hWnd);
			int wmId = LOWORD(wParam);
			// –азобрать выбор в меню:
			switch (wmId)
			{
			case VK_RIGHT:
			{
				ActionBrickRotateX* rotatex = new ActionBrickRotateX(-angle);
				application->call(*rotatex, 0);
				application->call(*actionDraw, 0);
			}
			break;
			case VK_LEFT:
			{
				ActionBrickRotateX* rotatex = new ActionBrickRotateX(angle);
				application->call(*rotatex, 0);
				application->call(*actionDraw, 0);
			}
			break;
			case VK_UP:
			{
				ActionBrickRotateY* rotatey = new ActionBrickRotateY(angle);
				application->call(*rotatey, 0);
				application->call(*actionDraw, 0);
			}
			break;
			case VK_DOWN:
			{	
				ActionBrickRotateY* rotatey = new ActionBrickRotateY(-angle);
				application->call(*rotatey, 0);
				application->call(*actionDraw, 0);
			}
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
			double width = 1;
			double height = 1;
			HDC hdc = BeginPaint(hWnd, &ps);
			InterfaceDrawInit DrawInit(hdc);
			drawInterface->redraw();
			application->call(*actionDraw, 0);
			/*
			Brick* brick = new Brick;
			brick = cobject->objects[0];
			vector<Face> faces = brick->getFaces();
			for (int i = 0; i < brick->facesCount(); i++) {
				Face face = faces[i];
				for (int j = 0; j < 3; j++) {
					Vertex v0 = brick->getVertex()[face.getCurrent() - 1];
					Vertex v1 = brick->getVertex()[face.getNext() - 1];
					int x0 = (v0.getX())*width / 2. + 100;
					int y0 = (v0.getY())*height / 2. + 100;
					int x1 = (v1.getX())*width / 2. + 100;
					int y1 = (v1.getY())*height / 2. + 100;
					MoveToEx(hdc, x0, y0, NULL);
					LineTo(hdc, x1, y1);
					//line(x0, y0, x1, y1, image, white);
				}
			} */
			EndPaint(hWnd, &ps);
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	catch (BaseException& err)
	{
		WCHAR msg[256];
		MultiByteToWideChar(0, 0, err.what(), 255, msg, 256);
		MessageBox(NULL, msg, TEXT("ERROR"), MB_OK);
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
