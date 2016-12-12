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

	GVector position(0, 400, 400, 1);
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
	this->light.Y = -500;
	this->light.Z = 0;

	this->initFloor();
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

void Scene::initFloor()
{
	int floorsize = this->width - 100;
	int sharpSize = this->width / 20;
	for (int x = -floorsize; x < floorsize; x += sharpSize)
	{
		floorX.push_back(Vertex(x, 0, -floorsize));
		floorX.push_back(Vertex(x, 0, floorsize));
		floorXSC.push_back(Vertex(x, 0, -floorsize));
		floorXSC.push_back(Vertex(x, 0, floorsize));
	}
	for (int z = -floorsize; z < floorsize; z += sharpSize)
	{
		floorZ.push_back(Vertex(-floorsize, 0, z));
		floorZ.push_back(Vertex(floorsize, 0, z));
		floorZSC.push_back(Vertex(-floorsize, 0, z));
		floorZSC.push_back(Vertex(floorsize, 0, z));
	}
}

void Scene::drawFloor()
{
	for (int i = 0; i < this->floorXSC.size(); i += 2)
	{
		int x1 = this->floorXSC[i].X;
		int y1 = this->floorXSC[i].Y;
		int z1 = this->floorXSC[i].Z;
		int x2 = this->floorXSC[i + 1].X;
		int y2 = this->floorXSC[i + 1].Y;
		int z2 = this->floorXSC[i + 1].Z;
		this->render->line(x1, y1, x2, y2, z1, z2);
	}

	for (int i = 0; i < this->floorZSC.size(); i += 2)
	{
		int x1 = this->floorZSC[i].X;
		int y1 = this->floorZSC[i].Y;
		int z1 = this->floorZSC[i].Z;
		int x2 = this->floorZSC[i + 1].X;
		int y2 = this->floorZSC[i + 1].Y;
		int z2 = this->floorZSC[i + 1].Z;
		this->render->line(x1, y1, x2, y2, z1, z2);
	}
}

void Scene::DrawScene(int ActiveBrick)
{
	int fps;
	WCHAR fps_buf[11] = { 0 };
	LARGE_INTEGER sta, fin, frq;
	QueryPerformanceCounter(&sta);

	this->toCam();

	//
	// Draw scene
	//
	this->drawFloor();

	this->render->run(bricks, *this->cam, this->slight, ActiveBrick);

	SelectObject(this->hdcMem, this->sBmp);
	BitBlt(this->hdc, X, Y, this->width, this->height, this->hdcMem, 0, 0, SRCCOPY);

	//
	// Count FPS
	//
	QueryPerformanceCounter(&fin);
	QueryPerformanceFrequency(&frq);

	long double dif = long double(fin.QuadPart - sta.QuadPart) / frq.QuadPart;
	fps = 1.0 / dif;

	wsprintf(fps_buf, TEXT("  FPS: %d"), fps);
	TextOut(this->hdc, this->X + 25, this->height - 50, (LPCWSTR)fps_buf, 11);
}

bool Scene::AddBrick(Brick brick, int X, int Y, int Z, COLORREF color, float transparency)
{
	Brick* nbrick = new Brick(brick);
	nbrick->color = color;
	nbrick->transparency = transparency;

	GMatrix movetoorigin = matrixMove(-nbrick->center.X + X, -nbrick->center.Y + Y, -nbrick->center.Z + Z);

#pragma omp parallel for
	for (int vertexIndex = 0; vertexIndex < nbrick->vertexCount(); vertexIndex++)
	{
		nbrick->sourceVertex[vertexIndex] = nbrick->sourceVertex[vertexIndex] * movetoorigin;
		nbrick->vertex[vertexIndex] = nbrick->vertex[vertexIndex] * movetoorigin;
	}

	Vertex center(X, Y, Z);
	nbrick->center = center;
	nbrick->sourceCenter = center;
	this->bricks->add(nbrick);
	if (this->checkCollision(this->bricks->objects.size() - 1) == 1)
	{
		this->bricks->objects.pop_back();
		return false;
	}
	return true;
}

bool Scene::checkFaceVisibility(Brick* nbrick, int faceIndex, GMatrix nresult)
{
	GVector check;
	double minZ = 9999999;
	for (int i = 0; i < 3; i++)
	{
		GVector tmpN(nbrick->VNormal[faceIndex][i]);
		tmpN = tmpN * nresult;
		check = check + tmpN;

		if (nbrick->svertex[nbrick->faces[faceIndex].Vertices[i]-1].Z < minZ)
		{
			minZ = nbrick->svertex[nbrick->faces[faceIndex].Vertices[i]-1].Z;
		}
	}
	if (check[2] <= 0 || minZ > this->cam->cposition.length())
	{
		nbrick->faces[faceIndex].visible = false;
		return false;
	}
	else
	{
		nbrick->faces[faceIndex].visible = true;
		return true;
	}
}

void Scene::toCam()
{
	int xCenter = this->width / 2;
	int yCenter = this->height / 2;

	GMatrix view = this->cam->cameraview();
	GMatrix nview = view;
	nview.transposition();
	nview.inverse();

	GVector d = this->cam->target;
	d = d - this->cam->position;

	GMatrix proj = matrixProjection(d.length());
	GMatrix scenecoord = matrixMove(xCenter, yCenter, 0);
	GMatrix nscenecoord = scenecoord;
	nscenecoord.transposition();
	nscenecoord.inverse();

	GMatrix result = view * proj * scenecoord;
	GMatrix nresult = result;
	nresult.transposition();
	nresult.inverse();

	for (int i = 0; i < this->floorX.size(); i++)
	{
		Vertex tmp = this->floorX[i];
		tmp = tmp * result;
		this->floorXSC[i] = tmp;
	}
	for (int i = 0; i < this->floorZ.size(); i++)
	{
		Vertex tmp = this->floorZ[i];
		tmp = tmp * result;
		this->floorZSC[i] = tmp;
	}

	this->slight = this->light;
	this->slight = this->slight * result;

	for (int brickIndex = 0; brickIndex < this->bricks->objects.size(); brickIndex++)
	{
		Brick* nbrick = this->bricks->objects[brickIndex];

#pragma omp parallel for
		for (int vertexIndex = 0; vertexIndex < nbrick->vertexCount(); vertexIndex++)
		{
			Vertex tmpVertex = nbrick->vertex[vertexIndex];
			tmpVertex = tmpVertex * result;

			nbrick->svertex[vertexIndex] = tmpVertex;
		}

		nbrick->scenter = nbrick->center * result;

#pragma omp parallel for
		for (int faceIndex = 0; faceIndex < nbrick->facesCount(); faceIndex++)
		{
			for (int i = 0; i < 3; i++)
			{
				GVector tmpN(nbrick->VNormal[faceIndex][i]);
				tmpN = tmpN * nview * nscenecoord;;
				nbrick->sVNormal[faceIndex][i] = tmpN;
			}
			this->checkFaceVisibility(nbrick, faceIndex, nresult);

		}
	}

}

bool Scene::checkCollision(int ID)
{
	bool collision = false;
	Brick* currentBrick = this->bricks->objects[ID];
	for (int currentBrickFaceCount = 0; currentBrickFaceCount < currentBrick->facesCount() && !collision; currentBrickFaceCount++)
	{
		Vertex A1 = currentBrick->sourceVertex[currentBrick->faces[currentBrickFaceCount].A() - 1];
		Vertex B1 = currentBrick->sourceVertex[currentBrick->faces[currentBrickFaceCount].B() - 1];
		Vertex C1 = currentBrick->sourceVertex[currentBrick->faces[currentBrickFaceCount].C() - 1];
		for (int bricksCount = 0; bricksCount < this->bricks->objects.size() && !collision; bricksCount++)
		{
			if (bricksCount != ID)
			{
				Brick* otherBrick = this->bricks->objects[bricksCount];
				for (int otherBrickFaceCount = 0; otherBrickFaceCount < otherBrick->facesCount() && !collision; otherBrickFaceCount++)
				{
					Vertex A2 = otherBrick->vertex[otherBrick->faces[otherBrickFaceCount].A() - 1];
					Vertex B2 = otherBrick->vertex[otherBrick->faces[otherBrickFaceCount].B() - 1];
					Vertex C2 = otherBrick->vertex[otherBrick->faces[otherBrickFaceCount].C() - 1];
					collision = (PolygonCompare(A1, B1, C1, A2, B2, C2) == 1);
				}
			}
		}
	}
	return collision;
}