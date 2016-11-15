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

	GVector position(0, 0, 500, 1);
	GVector target(0, 0, 0, 1);

	this->cam = new Camera(position, target);
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

	this->light = this->light * this->cam->cameraview();

	this->light.X += this->width / 2;
	this->light.Y += this->height / 2;
	this->light.Z += 0;

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
	int fps;
	WCHAR fps_buf[11] = { 0 };
	LARGE_INTEGER sta, fin, frq;
	QueryPerformanceCounter(&sta);

#pragma omp parallel for
	for (int i = 0; i < this->width; i++)
	{
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

	this->toCam();

	Brick* brick = bricks->objects[0]; // temporary
	this->render->run(brick, this->cam, this->light);

	SelectObject(this->hdcMem, this->sBmp);
	BitBlt(this->hdc, X, Y, this->width, this->height, this->hdcMem, 0, 0, SRCCOPY);

	QueryPerformanceCounter(&fin);
	QueryPerformanceFrequency(&frq);

	long double dif = long double(fin.QuadPart - sta.QuadPart) / frq.QuadPart;
	fps = 1.0 / dif;

	wsprintf(fps_buf, TEXT("FPS: %d"), fps);
	TextOut(this->hdc, this->X + 25, this->height - 50, (LPCWSTR)fps_buf, 11);
}

void Scene::AddBrick(Brick brick)
{
	Brick* nbrick = new Brick(brick);

#pragma omp parallel for
	for (int vertexIndex = 0; vertexIndex < nbrick->vertexCount(); vertexIndex++)
	{
		Vertex v = nbrick->vertex[vertexIndex];

		int nX = v.X + 1. - nbrick->center.X;
		int nY = v.Y + 1. - nbrick->center.Y;
		int nZ = v.Z + 1. - nbrick->center.Z;

		nbrick->vertex[vertexIndex].X = nX;
		nbrick->vertex[vertexIndex].Y = nY;
		nbrick->vertex[vertexIndex].Z = nZ;
	}
	
	Vertex center(0, 0, 0);
	nbrick->center = center;

	this->bricks->add(nbrick);
}

void Scene::toCam()
{
	int xCenter = this->width / 2;
	int yCenter = this->height / 2;

	GMatrix view = this->cam->cameraview();

	for (int brickIndex = 0; brickIndex < this->bricks->objects.size(); brickIndex++)
	{
		Brick* nbrick = this->bricks->objects[brickIndex];
#pragma omp parallel for
		for (int vertexIndex = 0; vertexIndex < nbrick->vertexCount(); vertexIndex++)
		{
			Vertex tmpVertex = nbrick->vertex[vertexIndex];
			tmpVertex = tmpVertex * view;
			tmpVertex.X = tmpVertex.X + xCenter;
			tmpVertex.Y = tmpVertex.Y + yCenter;

			nbrick->svertex[vertexIndex] = tmpVertex;
		}

#pragma omp parallel for
		for (int faceIndex = 0; faceIndex < nbrick->facesCount(); faceIndex++)
		{
			for (int i = 0; i < 3; i++)
			{
				GVector tmpN = nbrick->VNormal[faceIndex][i];
				//tmpN = tmpN * view;
				nbrick->sVNormal[faceIndex][i] = tmpN;
			}
		}
	}

}