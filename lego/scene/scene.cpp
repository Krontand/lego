#include "stdafx.h"
#include "../stdafx.h"
#include "scene.h"

Scene::Scene()
{
	this->hWnd = NULL;
	this->hdc = NULL;
	this->hdcMem = NULL;

	this->X = 0;
	this->Y = 0;
	this->width = 0;
	this->height = 0;

	this->InitBitmap();

	this->bricks = new Composite;
	if (!this->bricks)
	{
		throw AllocationMemoryError();
	}
	this->pixels = new unsigned long[500 * 600];
}

Scene::Scene(HWND hWnd, int x, int y, int width, int height)
{
	this->hWnd = hWnd;
	this->hdc = GetDC(hWnd);
	this->hdcMem = CreateCompatibleDC(this->hdc);
	
	this->X = x;
	this->Y = y;
	this->width = width;
	this->height = height;

	this->pixels = new unsigned long[500 * 600];

	this->InitBitmap();

	this->bricks = new Composite;
	if (!this->bricks)
	{
		throw AllocationMemoryError();
	}
}

void Scene::InitBitmap()
{
	this->sBmInfo.bmiHeader.biSize = sizeof(BITMAPINFO);
	this->sBmInfo.bmiHeader.biWidth = this->width;
	this->sBmInfo.bmiHeader.biHeight = -this->height;
	this->sBmInfo.bmiHeader.biPlanes = 1;
	this->sBmInfo.bmiHeader.biBitCount = 32;
	this->sBmInfo.bmiHeader.biCompression = BI_RGB;
	this->sBmInfo.bmiHeader.biSizeImage = 0;
	this->sBmInfo.bmiHeader.biXPelsPerMeter = 0;
	this->sBmInfo.bmiHeader.biYPelsPerMeter = 0;
	this->sBmInfo.bmiHeader.biClrUsed = 0;
	this->sBmInfo.bmiHeader.biClrImportant = 0;

	this->sBmInfo.bmiColors[0].rgbBlue = 0;
	this->sBmInfo.bmiColors[0].rgbGreen = 0;
	this->sBmInfo.bmiColors[0].rgbRed = 0;
	this->sBmInfo.bmiColors[0].rgbReserved = 0;

	this->sBmp = CreateDIBSection(
		this->hdc, &this->sBmInfo, DIB_RGB_COLORS, (void**)&pixels, NULL, 0
		);
}

void Scene::DrawScene()
{
	for (int i = 0; i < this->width; i++)
	{
		for (int j = 0; j < this->height; j++)
		{
			this->pixels[j*width + i] = 0x00ffff00;
		}
	}
	SelectObject(this->hdcMem, this->sBmp);
	BitBlt(this->hdc, X, Y, this->width, this->height, this->hdcMem, 0, 0, SRCCOPY);
	
	//HDC sourceHdc = CreateCompatibleDC(this->hdc);
	
	
	//sBmp = CreateBitmap(width, height, 1    // Одна панель цветов
	//	, 8 * 4            // 4 байта - Количество байтов цвета на один пиксель  
	//	, pixels);
	//HBITMAP hbmpOldTarget = (HBITMAP)SelectObject(sourceHdc, sBmp);
	//BOOL r1 = BitBlt(hdc, X, Y, width, height, sourceHdc, 0, 0, SRCCOPY);
	//if (!r1)
	//{
		// ERROR........................ 
	//}
	/*::selectobject(sourcehdc, hbmpoldtarget);
	hbmpoldtarget = null;
	deletedc(sourcehdc);*/
}