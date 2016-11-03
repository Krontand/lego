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

	int xCenter = this->width / 2;
	int yCenter = this->height / 2;

#pragma omp parallel for
	for (int faceIndex = 0; faceIndex < brick->facesCount(); faceIndex++)
	{
		Face face = brick->faces[faceIndex];
		
		Vertex A(brick->vertex[face.getA() - 1]);
		Vertex B(brick->vertex[face.getB() - 1]);
		Vertex C(brick->vertex[face.getC() - 1]);

		A = A * view;
		B = B * view;
		C = C * view;

		A.X = A.X + xCenter;
		A.Y = A.Y + yCenter;

		B.X = B.X + xCenter;
		B.Y = B.Y + yCenter;

		C.X = C.X + xCenter;
		C.Y = C.Y + yCenter;

		this->fillFaces(A, B, C);
	}
}

void Render::InitRenderedFaces(Vertex A, Vertex B, Vertex C) 
{
	RFace rf;

	rf.A = A;
	rf.B = B;
	rf.C = C;

	rf.xCA = C.X - A.X;
	rf.xCB = C.X - B.X;
	rf.xBA = B.X - A.X;
	rf.yCA = C.Y - A.Y;
	rf.yCB = C.Y - B.Y;
	rf.yBA = B.Y - A.Y;

	rf.visible = true;
}

void Render::line(int x0, int y0, int x1, int y1)
{
	bool step = false;
	if (abs(x0 - x1) < abs(y0 - y1)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		step = true;
	}

	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
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
	if (A.Y == B.Y && A.Y == C.Y) return;

	if (A.Y > B.Y) std::swap(A, B);
	if (A.Y > C.Y) std::swap(A, C);
	if (B.Y > C.Y) std::swap(B, C);

	int aY = A.Y;
	int bY = B.Y;
	int cY = C.Y;
	int aX = A.X;
	int bX = B.X;
	int cX = C.X;

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
			nb.X = bX + (cX - bX) * bk;
			nb.Y = bY + (cY - bY) * bk;
		}
		else
		{
			nb.X = aX + (bX - aX) * bk;
			nb.Y = aY + (bY - aY) * bk;
		}

		if (na.X > nb.X)
		{
			std::swap(na, nb);
		}

		for (int xCoord = na.X; xCoord <= nb.X; xCoord++) 
		{
			int pix = (int)(A.Y + yCoord)*this->width + xCoord;
			if (pix >= 0 && pix <= this->width * this->height)
			{
				this->pixels[pix] = 0x00000000;
			}
		}

	}

}
