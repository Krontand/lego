#include "stdafx.h"
#include "../stdafx.h"
#include "combobox.h"

Combobox::Combobox()
{

}

Combobox::Combobox(int ID)
{
	this->ID = ID;
}

Combobox::Combobox(int X, int Y, int HEIGHT, int WIDTH, WCHAR* TEXT)
{
	this->create(X, Y, HEIGHT, WIDTH, TEXT);
}

Combobox::~Combobox()
{
	this->remove();
}

HWND Combobox::create(int X, int Y, int HEIGHT, int WIDTH, WCHAR* TEXT)
{
	if (this->chWnd)
	{
		return this->chWnd;
	}
	this->chWnd = CreateWindowExW(NULL, TEXT("COMBOBOX"), TEXT(""),
		WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL,
		X, Y, WIDTH, 30,
		this->hWnd, (HMENU)this->ID, this->hInst, NULL);

	this->addItem(TEXT);

	HFONT hfont = CreateFont(HEIGHT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Arial"));
	SendMessage(this->chWnd, WM_SETFONT, (WPARAM)hfont, 0);

	return this->chWnd;
}

void Combobox::resetSelect()
{
	SendMessage(this->chWnd, CB_SETCURSEL, 0, 0L);
}

void Combobox::addItem(WCHAR* item)
{
	WCHAR buf[100];
	memset(&buf, 0, sizeof(buf));
	wcscpy_s(buf, sizeof(buf) / sizeof(WCHAR), (WCHAR*)item);
	SendMessage(this->chWnd, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
	SendMessage(this->chWnd, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
}

void Combobox::deleteItem(int ID)
{
	SendMessage(this->chWnd, CB_DELETESTRING, (WPARAM)ID, (LPARAM)0L);
}

int Combobox::getCurrentItem()
{
	return ComboBox_GetCurSel(this->chWnd);
}

HWND Combobox::getHWND()
{
	return this->chWnd;
}

void Combobox::remove()
{
	DestroyWindow(GetDlgItem(this->hWnd, this->ID));
	this->chWnd = NULL;
}