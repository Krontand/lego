#include "stdafx.h"
#include "listener.h"
#include "interface\drawinterface.h"
#include "interface\interface.h"
#include "interface\text.h"
#include "application.h"

#define ROTATTION_ANGLE 5 * M_PI / 180

extern HINSTANCE hInst;
PAINTSTRUCT ps;
BaseInterface* UI;
BaseDrawInterface* drawUI = new BaseDrawInterface;

COLORREF brickColor = RGB(140, 140, 255);

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
		if (!actionDraw)
		{
			throw AllocationMemoryError();
		}

		static Application* application = new Application(hWnd, 245, 0, 875, 750);
		if (!application)
		{
			delete actionDraw;
			throw AllocationMemoryError();
		}

		switch (message)
		{
		case WM_CREATE:
		{
			drawUI->text(TXT_LEGO)
				->SetColor(RGB(255, 255, 255))
				->SetWeight(800)
				->SetHeight(36)
				->SetSymbolWidth(13)
				->display(20, 30, 0, 0, TEXT("LEGO"));
			drawUI->text(TXT_DESIGNER)
				->SetColor(RGB(37, 45, 74))
				->SetWeight(400)
				->SetHeight(36)
				->SetSymbolWidth(11)
				->display(95, 30, 0, 0, TEXT("DESIGNER"));
			
			INITCOMMONCONTROLSEX init = { sizeof(INITCOMMONCONTROLSEX), ICC_WIN95_CLASSES };
			InitCommonControlsEx(&init);

			InterfaceCtrlInit CtrlInit(hWnd, hInst);
			UI = new BaseInterface;

			UI->combobox(CB_CHOOSEBRICK)->create(10, 250, 22, 223, TEXT("Choose brick type..."));

			UI->editfield(EDIT_X)->create(10, 290, 28, 70, TEXT("0"));
			UI->editfield(EDIT_Y)->create(87, 290, 28, 70, TEXT("0"));
			UI->editfield(EDIT_Z)->create(164, 290, 28, 70, TEXT("0"));

			drawUI->text(TXT_COLOR)
				->SetColor(RGB(211, 220, 236))
				->SetWeight(200)
				->SetHeight(22)
				->SetSymbolWidth(8)
				->display(20, 335, 0, 0, TEXT("Color"));

			drawUI->rectangle(RCT_COLOR)
				->SetBorderColor(RGB(255, 255, 255))
				->SetBorderWidth(1)
				->SetColor(brickColor)
				->display(88, 330, 156, 363, NULL);

			UI->button(BTN_CHCOLOR)->create(164, 330, 33, 70, TEXT("Change!"));
			UI->button(BTN_CHCOLOR)->setImage(BTN_COLOR);

			UI->button(BTN_OK)->create(10, 500, 33, 223, TEXT("Add Brick!"));
			UI->button(BTN_OK)->setImage(BTN_ADDBRICK);

		
			ActionLoadbrick* LoadFirst = new ActionLoadbrick("objs/untitled.obj");
			if (!LoadFirst)
			{
				throw AllocationMemoryError();
			}

			application->call(*LoadFirst, 0);
			UI->combobox(CB_CHOOSEBRICK)->addItem(TEXT("2x1"));

		}
		break;

		case  WM_SETCURSOR:
			if ((HWND)wParam == UI->button(BTN_OK)->getHWND())
			{
				SetCursor(LoadCursor(nullptr, IDC_HAND));
				UI->button(BTN_OK)->setImage(BTN_ADDBRICK_ACTIVE);
				return true;
			}
			else
			{
				UI->button(BTN_OK)->setImage(BTN_ADDBRICK);
				if ((HWND)wParam == UI->button(BTN_CHCOLOR)->getHWND())
				{
					SetCursor(LoadCursor(nullptr, IDC_HAND));
					UI->button(BTN_CHCOLOR)->setImage(BTN_COLOR_ACTIVE);
					return true;
				}
				else
				{
					SetCursor(LoadCursor(nullptr, IDC_ARROW));
					UI->button(BTN_CHCOLOR)->setImage(BTN_COLOR);
					return true;
				}
			}
			break;
		case WM_COMMAND:
		case WM_KEYDOWN:
		{
			int wmId = LOWORD(wParam);
			// –азобрать выбор в меню:
			switch (wmId)
			{
			case CB_CHOOSEBRICK:
			{

			}
			break;
			case BTN_CHCOLOR:
			{
				brickColor = colorDialog();
				drawUI->rectangle(RCT_COLOR)->SetColor(brickColor);
				RedrawWindow(hWnd, NULL, 0, RDW_INVALIDATE);
			}
			break;
			case BTN_OK:
			{
				int brickID = UI->combobox(CB_CHOOSEBRICK)->getCurrentItem();
				if (brickID == 0)
				{
					throw ModelChoosingError();
				}

				int X = UI->editfield(EDIT_X)->getInt();
				int Y = UI->editfield(EDIT_Y)->getInt();
				int Z = UI->editfield(EDIT_Z)->getInt();

				ActionAddbrick* addBrick = new ActionAddbrick(X,Y,Z, brickColor);
				if (!addBrick)
				{
					throw AllocationMemoryError();
				}

				application->call(*addBrick, brickID-1);
				application->call(*actionDraw, 0);
				SetFocus(hWnd);
			}
			break;
			case VK_RIGHT:
			{
				ActionBrickRotateX* rotatex = new ActionBrickRotateX(-angle);
				if (!rotatex)
				{
					throw AllocationMemoryError();
				}

				application->call(*rotatex, 0);
				application->call(*actionDraw, 0);
			}
			break;
			case VK_LEFT:
			{
				ActionBrickRotateX* rotatex = new ActionBrickRotateX(angle);
				if (!rotatex)
				{
					throw AllocationMemoryError();
				}

				application->call(*rotatex, 0);
				application->call(*actionDraw, 0);
			}
			break;
			case VK_UP:
			{
				ActionBrickRotateZ* rotatez = new ActionBrickRotateZ(angle);
				if (!rotatez)
				{
					throw AllocationMemoryError();
				}

				application->call(*rotatez, 0);
				application->call(*actionDraw, 0);
			}
			break;
			case VK_DOWN:
			{	
				ActionBrickRotateZ* rotatez = new ActionBrickRotateZ(-angle);
				if (!rotatez)
				{
					throw AllocationMemoryError();
				}

				application->call(*rotatez, 0);
				application->call(*actionDraw, 0);
			}
			break;
			case 104: // 8 NUMPAD
			{
				ActionCameraRotationHorizontal* rotateh = new ActionCameraRotationHorizontal(-angle);
				if (!rotateh)
				{
					throw AllocationMemoryError();
				}

				application->call(*rotateh, 0);
				application->call(*actionDraw, 0);
			}
			break;
			case 98: // 2 NUMPAD
			{
				ActionCameraRotationHorizontal* rotateh = new ActionCameraRotationHorizontal(angle);
				if (!rotateh)
				{
					throw AllocationMemoryError();
				}

				application->call(*rotateh, 0);
				application->call(*actionDraw, 0);
			}
			break;
			case 100: // 4 NUMPAD
			{
				ActionCameraRotationVertical* rotatev = new ActionCameraRotationVertical(-angle);
				if (!rotatev)
				{
					throw AllocationMemoryError();
				}

				application->call(*rotatev, 0);
				application->call(*actionDraw, 0);
			}
			break;
			case 102: // 6 NUMPAD
			{
				ActionCameraRotationVertical* rotatev = new ActionCameraRotationVertical(angle);
				if (!rotatev)
				{
					throw AllocationMemoryError();
				}

				application->call(*rotatev, 0);
				application->call(*actionDraw, 0);
			}
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
			drawUI->redraw();
			application->call(*actionDraw, 0);
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
