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

	this->bricks = nullptr;
	this->pixels = nullptr;
	this->render = nullptr;
	this->cam = nullptr;
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

	this->pixels = new unsigned long[this->width * this->height];
	if (!this->pixels)
	{
		throw AllocationMemoryError();
	}

	this->InitBitmap();

	this->bricks = new Composite;
	if (!this->bricks)
	{
		delete this->pixels;
		this->pixels = nullptr;

		throw AllocationMemoryError();
	}

	this->render = new Render(pixels, this->height, this->width);
	if (!this->render)
	{
		delete this->pixels;
		delete this->bricks;
		this->pixels = nullptr;
		this->bricks = nullptr;

		throw AllocationMemoryError();
	}

	this->cam = new Camera;
	if (!this->cam)
	{
		delete this->pixels;
		delete this->bricks;
		delete this->render;
		this->pixels = nullptr;
		this->bricks = nullptr;
		this->render = nullptr;

		throw AllocationMemoryError();
	}
}

Scene::~Scene()
{
	delete this->pixels;
	delete this->bricks;
	delete this->render;
	delete this->cam;
	this->pixels = nullptr;
	this->bricks = nullptr;
	this->render = nullptr;
	this->cam = nullptr;
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
#pragma omp parallel for
	for (int i = 0; i < this->width; i++)
	{
#pragma omp parallel for
		for (int j = 0; j < this->height; j++)
		{
			this->pixels[j*this->width + i] = 0x00586bab;
		}
	}

#pragma omp parallel for
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < this->height; j++)
		{
			this->pixels[j*this->width + i] = 0x00a0aacf;
		}
	}

	//draw model

	Brick* brick = bricks->objects[0]; // temporary
	this->render->run(brick, this->cam);

	SelectObject(this->hdcMem, this->sBmp);
	BitBlt(this->hdc, X, Y, this->width, this->height, this->hdcMem, 0, 0, SRCCOPY);
}

void Scene::AddBrick(Brick brick)
{
	Brick* nbrick = new Brick(brick);

	this->bricks->add(nbrick);
}

Composite* Scene::getBricks()
{
	return this->bricks;
}