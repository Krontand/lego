#include "stdafx.h"
#include "../stdafx.h"
#include "render.h"
#include <time.h>

Render::Render(unsigned long* pixels, int height, int width)
{
	this->pixels = pixels;
	this->height = height;
	this->width = width;
}

Render::~Render()
{
}

void Render::run(Brick* brick, Camera* cam)
{
	GMatrix view = cam->cameraview();
//#pragma omp parallel for
	for (int faceIndex = 0; faceIndex < brick->facesCount(); faceIndex++)
	{
		Face face = brick->getFaces()[faceIndex];
		
		Vertex A(brick->getVertex()[face.getA() - 1]);
		Vertex B(brick->getVertex()[face.getB() - 1]);
		Vertex C(brick->getVertex()[face.getC() - 1]);

		A = A * view;
		B = B * view;
		C = C * view;

		A.setX(A.getX() + this->width / 2);
		A.setY(A.getY() + this->height / 2);

		B.setX(B.getX() + this->width / 2);
		B.setY(B.getY() + this->height / 2);

		C.setX(C.getX() + this->width / 2);
		C.setY(C.getY() + this->height / 2);

		this->fillFaces(A, B, C);

		/*for (int vertexIndex = 0; vertexIndex < 3; vertexIndex++)
		{
			Vertex v0 = brick->getVertex()[face.getCurrent() - 1];
			Vertex v1 = brick->getVertex()[face.getNext() - 1];

			int x0 = (v0.getX());
			int y0 = (v0.getY());
			int x1 = (v1.getX());
			int y1 = (v1.getY());

			this->line(x0, y0, x1, y1);

		}*/
	}
}

void Render::InitRenderedFaces(Vertex A, Vertex B, Vertex C) 
{
	RFace rf;

	rf.A = A;
	rf.B = B;
	rf.C = C;

	rf.xCA = C.getX() - A.getX();
	rf.xCB = C.getX() - B.getX();
	rf.xBA = B.getX() - A.getX();
	rf.yCA = C.getY() - A.getY();
	rf.yCB = C.getY() - B.getY();
	rf.yBA = B.getY() - A.getY();

	rf.visible = true;
}

void Render::line(int x0, int y0, int x1, int y1)
{
	bool step = false;
	if (abs(x0 - x1) < abs(y0 - y1)) {
		swap(x0, y0);
		swap(x1, y1);
		step = true;
	}

	if (x0 > x1) {
		swap(x0, x1);
		swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror2 = abs(dy) * 2;
	int error2 = 0;

	int y = y0;

	for (int x = x0; x <= x1; x++) {
		if (step) {
			this->pixels[x*this->width + y] = 0x00ffffff;
		}
		else {
			this->pixels[y*this->width + x] = 0x00ffffff;
		}
		error2 += derror2;

		if (error2 > dx) {
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx * 2;
		}
	}
}

void Render::fillFaces(Vertex A, Vertex B, Vertex C)
{	
	if (A.getY() == B.getY() && A.getY() == C.getY()) return;

	if (A.getY() > B.getY()) swap(A, B);
	if (A.getY() > C.getY()) swap(A, C);
	if (B.getY() > C.getY()) swap(B, C);

	int aY = A.getY();
	int bY = B.getY();
	int cY = C.getY();
	int aX = A.getX();
	int bX = B.getX();
	int cX = C.getX();

	int faceHeight = cY - aY;
	int halfHeight = bY - aY;

	for (int yCoord = 0; yCoord < faceHeight; yCoord++) {
		bool secondPart = yCoord > bY - aY || bY == aY;

		float ak = (float)yCoord / faceHeight;
		float bk;
		if (secondPart)
		{
			halfHeight = cY - bY;
			bk = (float) (yCoord - (bY - aY)) / halfHeight;
		}
		else
		{
			bk = (float) yCoord / halfHeight;
		}

		Vertex na(aX + (cX - aX) * ak, aY + (cY - aY) * ak, 0);
		Vertex nb;
		if (secondPart)
		{	
			nb.setX(bX + (cX - bX) * bk);
			nb.setY(bY + (cY - bY) * bk);
		}
		else
		{
			nb.setX(aX + (bX - aX) * bk);
			nb.setY(aY + (bY - aY) * bk);
		}

		if (na.getX() > nb.getX())
		{
			swap(na, nb);
		}

		for (int xCoord = na.getX(); xCoord <= nb.getX(); xCoord++) 
		{
			int pix = (int)(A.getY() + yCoord)*this->width + xCoord;
			if (pix >= 0 && pix <= this->width * this->height)
			{
				this->pixels[pix] = 0x00000000;
			}
		}

	}

}
