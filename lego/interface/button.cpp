#include "stdafx.h"
#include "../stdafx.h"
#include "button.h"

Button::Button()
{

}

Button::Button(int ID)
{
	this->ID = ID;
}

Button::Button(int X, int Y, int HEIGHT, int WIDTH, WCHAR* TEXT)
{
	this->create(X, Y, HEIGHT, WIDTH, TEXT);
}

Button::~Button()
{
	this->remove();
}

HWND Button::create(int X, int Y, int HEIGHT, int WIDTH, WCHAR* TEXT)
{
	if (this->bhWnd)
	{
		return this->bhWnd;
	}
	this->bhWnd = CreateWindowW(TEXT("BUTTON"), TEXT,
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_BITMAP,
		X, Y, WIDTH, HEIGHT,
		this->hWnd, (HMENU)this->ID, this->hInst, NULL);
	return this->bhWnd;
}

LRESULT Button::setImage(int rID)
{
	HBITMAP hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(rID));
	return SendMessageW(this->bhWnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
}

void Button::remove()
{
	DestroyWindow(GetDlgItem(this->hWnd, this->ID));
	this->bhWnd = NULL;
}