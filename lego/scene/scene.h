#pragma once

#include "../geometry\gmatrix.h"
#include "../model/composite.h"
#include "camera.h"

class Render;

#include "../render/render.h"

class Scene
{
public:
	Scene();
	Scene(HWND hWnd, int x, int y, int width, int height);
	~Scene();

	void DrawScene();
	void AddBrick(Brick brick);
	Composite* getBricks();
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
	Camera* cam;

	Render* render;

};