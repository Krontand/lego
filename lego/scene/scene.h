#pragma once

#include "../model/composite.h"

class Scene
{
public:
	Scene();
	Scene(HWND hWnd, int x, int y, int width, int height);

	void DrawScene();
private:
	void InitBitmap();

	int X;
	int Y;
	int width;
	int height;

	unsigned long* pixels;

	BITMAPINFO sBmInfo;
	HBITMAP sBmp;
	HDC hdc;
	HDC hdcMem;
	HWND hWnd;

	Composite* bricks;
	//Camera* cam;

};