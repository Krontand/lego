#include "stdafx.h"
#include "../stdafx.h"
#include "rectangle.h"

URectangle::URectangle()
{}

URectangle::URectangle(int X1, int Y1, int X2, int Y2, COLORREF color) : URectangle()
{
	this->X1 = X1;
	this->Y1 = Y1;
	this->X2 = X2;
	this->Y2 = Y2;
	this->COLOR = color;
	this->display(X1, Y1, X2, Y2, nullptr);
}

bool URectangle::display(int X1, int Y1, int X2, int Y2, WCHAR* TEXT)
{
	this->X1 = X1;
	this->Y1 = Y1;
	this->X2 = X2;
	this->Y2 = Y2;
	
	if (this->bWidth == 0)
	{
		SelectObject(this->hdc, CreatePen(PS_NULL, this->bWidth, this->bCOLOR));
	}
	else
	{
		SelectObject(this->hdc, CreatePen(PS_SOLID, this->bWidth, this->bCOLOR));
	}
	SelectObject(this->hdc, CreateSolidBrush(this->COLOR));

	return Rectangle(this->hdc, this->X1, this->Y1, this->X2, this->Y2);
}

bool URectangle::redraw()
{
	return this->display(this->X1, this->Y1, this->X2, this->Y2, nullptr);
}

URectangle* URectangle::SetColor(COLORREF color)
{
	this->COLOR = color;
	return this;
}

URectangle* URectangle::SetBorderColor(COLORREF color)
{
	this->bCOLOR = color;
	return this;
}

URectangle* URectangle::SetBorderWidth(int w)
{
	this->bWidth = w;
	return this;
}