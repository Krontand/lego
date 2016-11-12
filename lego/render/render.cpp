#include "stdafx.h"
#include "../stdafx.h"
#include "render.h"

Render::Render(unsigned long* pixels, int height, int width)
{
	this->pixels = pixels;
	this->height = height;
	this->width = width;
	this->zbuffer = new int[this->width * this->height];
	if (!zbuffer)
	{
		throw AllocationMemoryError();
	}
}

Render::~Render()
{
}

void Render::run(Brick* brick, Camera* cam, Light* light)
{
	for (int i = 0; i<this->width * this->height; i++) {
		this->zbuffer[i] = -9999999;
	}

	COLORREF color = RGB(255,255,255);

#pragma omp parallel for
	for (int faceIndex = 0; faceIndex < brick->facesCount(); faceIndex++)
	{
		Face face = brick->faces[faceIndex];
		
		Vertex A(brick->svertex[face.getA() - 1]);
		Vertex B(brick->svertex[face.getB() - 1]);
		Vertex C(brick->svertex[face.getC() - 1]);

		GVector nA = brick->VNormal[faceIndex][0];
		GVector nB = brick->VNormal[faceIndex][1];
		GVector nC = brick->VNormal[faceIndex][2];

		this->fillFaces(A, B, C, nA, nB, nC, color, *light);
	}
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

void Render::fillFaces(Vertex A, Vertex B, Vertex C, GVector normA, GVector normB, GVector normC, COLORREF color, Light light)
{	
	if (A.Y == B.Y && A.Y == C.Y) return;

	if (A.Y > B.Y) { std::swap(A, B); std::swap(normA, normB); }
	if (A.Y > C.Y) { std::swap(A, C); std::swap(normA, normC); }
	if (B.Y > C.Y) { std::swap(B, C); std::swap(normB, normC); }

	int faceHeight = (int)C.Y - (int)A.Y;
	int halfHeight = (int)B.Y - (int)A.Y;

	for (int yCoord = 0; yCoord < faceHeight; yCoord++) {
		bool secondPart = yCoord >(int)B.Y - (int)A.Y || (int)B.Y == (int)A.Y;

		float ak = (float)yCoord / faceHeight;
		float bk;
		if (secondPart)
		{
			halfHeight = (int)C.Y - (int)B.Y;
			bk = (float) (yCoord - ((int)B.Y - (int)A.Y)) / halfHeight;
		}
		else
		{
			bk = (float) yCoord / halfHeight;
		}

		Vertex na((int)A.X + ((int)C.X - (int)A.X) * ak, (int)A.Y + ((int)C.Y - (int)A.Y) * ak, (int)A.Z + ((int)C.Z - (int)A.Z) * ak);
		GVector nNormA(normA + (normC - normA) * ak);

		Vertex nb;
		GVector nNormB;
		if (secondPart)
		{	
			nb.X = (int)B.X + ((int)C.X - (int)B.X) * bk;
			nb.Y = (int)B.Y + ((int)C.Y - (int)B.Y) * bk;
			nb.Z = (int)B.Z + ((int)C.Z - (int)B.Z) * bk;

			nNormB = normB + (normC - normB) * bk;
		}
		else
		{
			nb.X = (int)A.X + ((int)B.X - (int)A.X) * bk;
			nb.Y = (int)A.Y + ((int)B.Y - (int)A.Y) * bk;
			nb.Z = (int)A.Z + ((int)B.Z - (int)A.Z) * bk;

			nNormB = normA + (normB - normA) * bk;
		}

		if ((int)na.X > (int)nb.X)
		{
			std::swap(na, nb);
			std::swap(nNormA, nNormB);
		}

		for (int xCoord = (int)na.X; xCoord <= (int)nb.X; xCoord++)
		{

			double phi = 1.;
			if ((int)nb.X != (int)na.X)
			{
				phi = (double)(xCoord - (int)na.X) / (double)((int)nb.X - (int)na.X);
			}

			Vertex P((int)na.X + ((int)nb.X - (int)na.X) * phi, (int)na.Y + ((int)nb.Y - (int)na.Y) * phi, (int)na.Z + ((int)nb.Z - (int)na.Z) * phi);
			GVector normP(nNormA + (nNormB - nNormA) * phi);
			
			int pix = ((int)A.Y + yCoord) * this->width + xCoord;
			if (pix >= 0 && pix <= this->width * this->height)
			{
				if (this->zbuffer[(int)P.X + (int)P.Y * this->width] <= P.Z)
				{
					this->zbuffer[(int)P.X + (int)P.Y * this->width] = P.Z;
					double I =  this->intencity(P.X, P.Y, P.Z, normP, light);
					this->pixels[pix] = RGB(GetRValue(color) * I, GetGValue(color) * I, GetBValue(color) * I);
				}
			}
		}

	}

}

double Render::intencity(double X, double Y, double Z, GVector N, Light light)
{
	//GVector d = light.direction - N;
	//d.normalize();
	N.normalize();
	light.sdirection[0] = light.sdirection[0] + this->width / 2;
	light.sdirection[1] = light.sdirection[1] + this->height / 2;
	light.sdirection.normalize();
	return max(0,GVector::scalar(N,light.sdirection));
}