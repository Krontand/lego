#include "stdafx.h"
#include "../stdafx.h"
#include "text.h"

Text::Text()
{
	this->font.lfHeight = 25;
	this->font.lfWidth = 0;
	this->font.lfEscapement = 0;
	this->font.lfOrientation = 0;
	this->font.lfWeight = 500;
	this->font.lfItalic = 0;
	this->font.lfUnderline = 0;
	this->font.lfStrikeOut = 0;
	this->font.lfCharSet = RUSSIAN_CHARSET;
	this->font.lfOutPrecision = 0;
	this->font.lfClipPrecision = 0;
	this->font.lfQuality = 0;
	this->font.lfPitchAndFamily = 0;
	wcscpy_s(this->font.lfFaceName, TEXT("Arial"));
	this->COLOR = RGB(0, 0, 0);
}

Text::Text(int X, int Y, WCHAR* TEXT) : Text()
{
	this->X = X;
	this->Y = Y;
	this->TEXT = TEXT;
	this->display(X, Y, 0, 0, TEXT);
}

bool Text::display(int X1, int Y1, int X2, int Y2, WCHAR* TEXT)
{
	this->X = X1;
	this->Y = Y1;
	this->TEXT = TEXT;
	HFONT hfont;
	hfont = ::CreateFontIndirect(&this->font);
	SelectObject(this->hdc, hfont);
	SetBkMode(this->hdc, TRANSPARENT);
	return TextOutW(this->hdc, X1, Y1, TEXT, wcslen(TEXT));
}

bool Text::redraw()
{
	this->SetColor(this->COLOR);
	return this->display(this->X, this->Y, 0, 0, this->TEXT);
}

Text* Text::SetColor(COLORREF color)
{
	this->COLOR = color;
	SetTextColor(this->hdc,this->COLOR);
	return this;
}

Text* Text::SetWeight(int w)
{
	this->font.lfWeight = w;
	return this;
}

Text* Text::SetHeight(int h)
{
	this->font.lfHeight = h;
	return this;
}

Text* Text::SetSymbolWidth(int w)
{
	this->font.lfWidth = w;
	return this;
}