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

	GVector position(0, 1000, 1000, 1);
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
	this->light.X = 0;
	this->light.Y = 0;
	this->light.Z = 1000;

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

	this->render->run(bricks, *this->cam, this->slight);

	SelectObject(this->hdcMem, this->sBmp);
	BitBlt(this->hdc, X, Y, this->width, this->height, this->hdcMem, 0, 0, SRCCOPY);

	QueryPerformanceCounter(&fin);
	QueryPerformanceFrequency(&frq);

	long double dif = long double(fin.QuadPart - sta.QuadPart) / frq.QuadPart;
	fps = 1.0 / dif;

	wsprintf(fps_buf, TEXT("  FPS: %d"), fps);
	TextOut(this->hdc, this->X + 25, this->height - 50, (LPCWSTR)fps_buf, 11);
}

void Scene::AddBrick(Brick brick, int X, int Y, int Z, COLORREF color)
{
	Brick* nbrick = new Brick(brick);
	nbrick->color = color;

	GMatrix movetoorigin = matrixMove(-nbrick->center.X + X, -nbrick->center.Y + Y, -nbrick->center.Z + Z);

#pragma omp parallel for
	for (int vertexIndex = 0; vertexIndex < nbrick->vertexCount(); vertexIndex++)
	{
		nbrick->vertex[vertexIndex] = nbrick->vertex[vertexIndex] * movetoorigin;
	}

	movetoorigin.transposition().inverse();

#pragma omp parallel for
	for (int faceIndex = 0; faceIndex < nbrick->facesCount(); faceIndex++)
	{
		for (int i = 0; i < 3; i++)
		{
			//nbrick->VNormal[faceIndex][i] = nbrick->VNormal[faceIndex][i] * movetoorigin;
		}
	}
	
	Vertex center(X, Y, Z);
	nbrick->center = center;

	this->bricks->add(nbrick);
}

void Scene::toCam()
{
	int xCenter = this->width / 2;
	int yCenter = this->height / 2;

	GMatrix view = this->cam->cameraview();

	GMatrix nview = view;
	nview.transposition();
	nview.inverse();

	GMatrix scenecoord = matrixMove(xCenter, yCenter, 0);
	GMatrix nscenecoord = scenecoord;
	nscenecoord.transposition();
	nscenecoord.inverse();
	
	// I don't know why, but if I put
	// light and normals in camera system coordinates
	// they don't work. I guess something here is answer
	// why cylinders lighting works not very good...
	this->slight = this->light;
	this->slight = this->slight * view;
	this->slight = this->slight * scenecoord;

	for (int brickIndex = 0; brickIndex < this->bricks->objects.size(); brickIndex++)
	{
		Brick* nbrick = this->bricks->objects[brickIndex];

#pragma omp parallel for
		for (int vertexIndex = 0; vertexIndex < nbrick->vertexCount(); vertexIndex++)
		{
			Vertex tmpVertex = nbrick->vertex[vertexIndex];
			tmpVertex = tmpVertex * view;
			tmpVertex = tmpVertex * scenecoord;

			nbrick->svertex[vertexIndex] = tmpVertex;
		}

#pragma omp parallel for
		for (int faceIndex = 0; faceIndex < nbrick->facesCount(); faceIndex++)
		{
			for (int i = 0; i < 3; i++)
			{
				GVector tmpN(nbrick->VNormal[faceIndex][i]);
				tmpN = tmpN * nview;
				tmpN = tmpN * nscenecoord;
				tmpN.normalize();
				nbrick->sVNormal[faceIndex][i] = tmpN;
			}
		}
	}

}