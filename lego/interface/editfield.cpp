#include "stdafx.h"
#include "../stdafx.h"
#include "editfield.h"

Editfield::Editfield()
{

}

Editfield::Editfield(int ID)
{
	this->ID = ID;
}

Editfield::Editfield(int X, int Y, int HEIGHT, int WIDTH, WCHAR* TEXT)
{
	this->create(X, Y, HEIGHT, WIDTH, TEXT);
}

Editfield::~Editfield()
{
	this->remove();
}

HWND Editfield::create(int X, int Y, int HEIGHT, int WIDTH, WCHAR* TEXT)
{
	if (this->ehWnd)
	{
		return this->ehWnd;
	}
	this->ehWnd = CreateWindowExW(WS_EX_WINDOWEDGE, TEXT("Edit"), TEXT,
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
		X, Y, WIDTH, HEIGHT,
		this->hWnd, (HMENU)this->ID, this->hInst, NULL);

	HFONT hfont = CreateFont(HEIGHT-2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Arial"));
	SendMessage(this->ehWnd, WM_SETFONT, (WPARAM)hfont, 0);

	return this->ehWnd;
}

WCHAR* Editfield::getText()
{
	TCHAR buf[5];
	GetWindowText(this->ehWnd, buf, 5);
	return buf;
}

int Editfield::getInt()
{
	WCHAR* result = this->getText();
	if (wcslen(result) == 0)
	{
		return 0;
	}
	return _wtoi(result);
}

HWND Editfield::getHWND()
{
	return this->ehWnd;
}

void Editfield::remove()
{
	DestroyWindow(GetDlgItem(this->hWnd, this->ID));
	this->ehWnd = NULL;
}