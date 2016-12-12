#include "stdafx.h"
#include "../stdafx.h"
#include "render.h"

Render::Render(unsigned long* pixels, int height, int width)
{
	this->pixels = pixels;
	this->height = height;
	this->width = width;
	this->zbuffer = new int[this->width * this->height];
	this->c_buf = new float[this->width * this->height];
	this->itransparent = new unsigned long[this->width * this->height];
	this->isolid = new unsigned long[this->width * this->height];

	if (!zbuffer || !c_buf || !itransparent || !isolid)
	{
		throw AllocationMemoryError();
	}

	this->clear();

	this->activeIntencity = 0;
	this->activeGrow = true;
	this->activeBrick = false;
}

Render::~Render()
{
}

void Render::clear()
{
#pragma omp parallel
	for (int i = 0; i<this->width * this->height; i++) {
		this->zbuffer[i] = -9999999;
		this->c_buf[i] = 0;
		this->itransparent[i] = 0x0;
		this->isolid[i] = 0x00586bab; // background color
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < this->height; j++)
		{
			this->isolid[j*this->width + i] = 0x00a0aacf; // line between menu and scene
		}
	}
}

void Render::run(Composite* bricks, Camera cam, Vertex light, int activeBrick)
{
	// Sorting bricks in order of distance from camera (need for transparent bricks)
	for (int brickIndex = 0; brickIndex < bricks->objects.size(); brickIndex++)
	{
		for (int sbrickIndex = brickIndex; sbrickIndex < bricks->objects.size() - 1; sbrickIndex++)
		{
			if (bricks->objects[sbrickIndex]->transparency < 1 && bricks->objects[sbrickIndex]->scenter.Z > bricks->objects[sbrickIndex+1]->scenter.Z)
			{
				std::swap(bricks->objects[sbrickIndex], bricks->objects[sbrickIndex + 1]);
			}
		}
	}
	
	double intencityCoeffitient = 0;
	for (int brickIndex = 0; brickIndex < bricks->objects.size(); brickIndex++)
	{
		Brick* brick = bricks->objects[brickIndex];
		COLORREF color = brick->color;
		float transparency = brick->transparency;

		this->activeBrick = (brick->ID == activeBrick);
		if(this->activeBrick)
		{
			this->actBrickIntencity();
		}

#pragma omp parallel for schedule(dynamic, 1)
		for (int faceIndex = 0; faceIndex < brick->facesCount(); faceIndex++)
		{
			Face face = brick->faces[faceIndex];
			if (face.visible)
			{
				Vertex A(brick->svertex[face.A() - 1]);
				Vertex B(brick->svertex[face.B() - 1]);
				Vertex C(brick->svertex[face.C() - 1]);

				Normal nA = brick->sVNormal[faceIndex][0];
				Normal nB = brick->sVNormal[faceIndex][1];
				Normal nC = brick->sVNormal[faceIndex][2];

				this->fillFaces(A, B, C, nA, nB, nC, color, light, cam, transparency);
			}
		}
	}

	this->sun(light.X, light.Y, 5, light.Z);

	for (int i = 0; i<this->width * this->height; i++) {
		this->pixels[i] = RGB(
				GetRValue(this->itransparent[i]) * this->c_buf[i] + (1 - this->c_buf[i]) * GetRValue(this->isolid[i]),
				GetGValue(this->itransparent[i]) * this->c_buf[i] + (1 - this->c_buf[i]) * GetGValue(this->isolid[i]),
				GetBValue(this->itransparent[i]) * this->c_buf[i] + (1 - this->c_buf[i]) * GetBValue(this->isolid[i]));
	}

	this->clear();
}

void Render::line(int x0, int y0, int x1, int y1, int z0, int z1)
{
	bool step = false;
	bool started = false;
	if (abs(x0 - x1) < abs(y0 - y1)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		step = true;
	}

	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
		std::swap(z0, z1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror2 = abs(dy) * 2;
	int error2 = 0;

	float dz = (float)(z1 - z0) / dx;

	int y = y0;
	float z = z0;

	for (int x = x0; x <= x1; x++) {
		if (step) {
			if (x < this->height && x > 0 && y > 0 && y < this->width)
			{
				if (this->zbuffer[x*this->width + y] < z)
				{
					this->isolid[x*this->width + y] = 0x00a0aacf;
					this->zbuffer[x*this->width + y] = z;
				}
				started = true;
			}
			else
			{
				if (started) return;
			}
		}
		else {

			if (x < this->width && x > 0 && y > 0 && y < this->height)
			{
				if (this->zbuffer[y*this->width + x] < z)
				{
					this->isolid[y*this->width + x] = 0x00a0aacf;
					this->zbuffer[y*this->width + x] = z;
				}
				started = true;
			}
			else
			{
				if (started) return;
			}
		}
		z += dz;
		error2 += derror2;
		if (error2 > dx) {
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx * 2;
		}
	}
}

void Render::sun(int x0, int y0, int r, int z)
{
	COLORREF c = 0x00FF0000;
	for (; r >= 0; r--)
	{
		int x = 0, y = r;
		int k = r * r;
		if (x0 < this->width && x0 > 0 && y0 + y > 0 && y0 + y < this->height)
			if (this->zbuffer[(y0 + y)*this->width + x0] < z)
			{
				this->isolid[(y0 + y)*this->width + x0] = c;
				this->zbuffer[(y0 + y)*this->width + x0] = z;
			}
		if (x0 < this->width && x0 > 0 && y0 - y > 0 && y0 - y < this->height)
			
			if (this->zbuffer[(y0 - y)*this->width + x0] < z)
			{
				this->isolid[(y0 - y)*this->width + x0] = c;
				this->zbuffer[(y0 - y)*this->width + x0] = z;
			}
		while (y >= 0)
		{
			int d = (x + 1) * (x + 1) + (y - 1) * (y - 1) - k;
			if (d >= 0)
				y--;
			if (d <= 0)
				x++;
			if (x0 + x < this->width && x0 + x > 0 && y0 + y > 0 && y0 + y < this->height)
				if (this->zbuffer[(y0 + y)*this->width + x0 + x] < z)
				{
					this->isolid[(y0 + y)*this->width + x0 + x] = c;
					this->zbuffer[(y0 + y)*this->width + x0 + x] = z;
				}
			if (x0 - x < this->width && x0 - x > 0 && y0 + y > 0 && y0 + y < this->height)
				if (this->zbuffer[(y0 + y)*this->width + x0 - x] < z)
				{
					this->isolid[(y0 + y)*this->width + x0 - x] = c;
					this->zbuffer[(y0 + y)*this->width + x0 - x] = z;
				}
			if (x0 + x < this->width && x0 + x > 0 && y0 - y > 0 && y0 - y < this->height)
				if (this->zbuffer[(y0 - y)*this->width + x0 + x] < z)
				{
					this->isolid[(y0 - y)*this->width + x0 + x] = c;
					this->zbuffer[(y0 - y)*this->width + x0 + x] = z;
				}
			if (x0 - x < this->width && x0 - x > 0 && y0 - y > 0 && y0 - y < this->height)
				if (this->zbuffer[(y0 - y)*this->width + x0 - x] < z)
				{
					this->isolid[(y0 - y)*this->width + x0 - x] = c;
					this->zbuffer[(y0 - y)*this->width + x0 - x] = z;
				}
		}
		if(c < 0x00FFFF00)
			c += 0x00003300;
	}
}

void Render::fillFaces(Vertex A, Vertex B, Vertex C, Normal normA, Normal normB, Normal normC, COLORREF color, Vertex light, Camera cam, float t)
{
	if (A.Y == B.Y && A.Y == C.Y) return;
	if (A.Y > B.Y) { std::swap(A, B); std::swap(normA, normB); }
	if (A.Y > C.Y) { std::swap(A, C); std::swap(normA, normC); }
	if (B.Y > C.Y) { std::swap(B, C); std::swap(normB, normC); }

	if (int(A.Y + .5) == int(B.Y + .5) && B.X < A.X) { std::swap(A, B); std::swap(normA, normB); }

	int x1 = int(A.X + .5);
	int x2 = int(B.X + .5);
	int x3 = int(C.X + .5);
	int y1 = int(A.Y + .5);
	int y2 = int(B.Y + .5);
	int y3 = int(C.Y + .5);
	int z1 = int(A.Z + .5);
	int z2 = int(B.Z + .5);
	int z3 = int(C.Z + .5);

	if ((y1 == y2) && (x1 > x2)) { std::swap(A, B); std::swap(normA, normB); }
	x1 = int(A.X + .5);
	x2 = int(B.X + .5);
	y1 = int(A.Y + .5);
	y2 = int(B.Y + .5);

	double dx13 = 0, dx12 = 0, dx23 = 0;
	double dz13 = 0, dz12 = 0, dz23 = 0;
	Normal dn13;
	Normal dn12;
	Normal dn23;

	if (y3 != y1)
	{
		dz13 = (z3 - z1) / (double)(y3 - y1);
		dx13 = (x3 - x1) / (double)(y3 - y1);
		dn13 = (normC - normA) / (y3 - y1);
	}
	if (y2 != y1)
	{
		dz12 = (z2 - z1) / (double)(y2 - y1);
		dx12 = (x2 - x1) / (double)(y2 - y1);
		dn12 = (normB - normA) / (double)(y2 - y1);
	}
	if (y3 != y2)
	{
		dz23 = (z3 - z2) / (double)(y3 - y2);
		dx23 = (x3 - x2) / (double)(y3 - y2);
		dn23 = (normC - normB) / (double)(y3 - y2);
	}

	double z = 0;
	double dz = 0;

	Normal normP;
	Normal dnorm;

	double wx1 = x1;
	double wx2 = x1;
	double wz1 = z1;
	double wz2 = z1;
	Normal wn1(normA);
	Normal wn2(normA);

	Normal _dn13(dn13);
	double _dx13 = dx13;
	double _dz13 = dz13;

	if (dx13 > dx12)
	{
		std::swap(dn13, dn12);
		std::swap(dx13, dx12);
		std::swap(dz13, dz12);
	}

	if (y1 == y2) {
		wx1 = x1;
		wx2 = x2;
		wz1 = z1;
		wz2 = z2;
		wn1 = normA;
		wn2 = normB;
	}

	if (_dx13 < dx23)
	{
		std::swap(_dn13, dn23);
		std::swap(_dx13, dx23);
		std::swap(_dz13, dz23);
	}

	for (int yCoord = y1; yCoord < y3; yCoord++)
	{
		z = wz1;
		normP = wn1;
		
		if (wx1 != wx2)
		{
			dz = (wz2 - wz1) / (double)(wx2 - wx1);
			dnorm = (wn2 - wn1) / (double)(wx2 - wx1);
		}

		for (int xCoord = wx1; xCoord < wx2; xCoord++)
		{
			if (xCoord < this->width && xCoord > 0 && yCoord > 0 && yCoord < this->height && z < cam.cposition.length())
			{
				int pix = yCoord * this->width + xCoord;
				if (this->zbuffer[pix] < z)
				{
					double I = this->intencity(xCoord, yCoord, z, normP, light, cam);
					if (t == 1)
					{
						this->zbuffer[pix] = z;
						this->isolid[pix] = RGB(GetBValue(color) * I, GetGValue(color) * I, GetRValue(color) * I);
					}
					else
					{
						this->c_buf[pix] = t + this->c_buf[pix] - t*this->c_buf[pix];
						this->itransparent[pix] = RGB(
							GetBValue(this->itransparent[pix]) * (1 - this->c_buf[pix]) + GetBValue(color) * I * t,
							GetGValue(this->itransparent[pix]) * (1 - this->c_buf[pix]) + GetGValue(color) * I * t,
							GetRValue(this->itransparent[pix]) * (1 - this->c_buf[pix]) + GetRValue(color) * I * t);
						
						
					}
				}
			}
			z += dz;
			normP = normP + dnorm;
		}
		if (yCoord < y2)
		{
			wx1 += dx13;
			wx2 += dx12;
			wz1 += dz13;
			wz2 += dz12;
			wn1 = wn1 + dn13;
			wn2 = wn2 + dn12;
		}
		else
		{
			wx1 += _dx13;
			wx2 += dx23;
			wz1 += _dz13;
			wz2 += dz23;
			wn1 = wn1 + _dn13;
			wn2 = wn2 + dn23;
		}
	}
}

void Render::actBrickIntencity()
{
	if (this->activeGrow)
	{
		this->activeIntencity += 0.007;
		if (this->activeIntencity > 0.1)
		{
			this->activeGrow = false;
		}
	}
	else
	{
		this->activeIntencity -= 0.007;
		if (this->activeIntencity < -0.1)
		{
			this->activeGrow = true;
		}
	}
}

double Render::intencity(double X, double Y, double Z, GVector N, Vertex light, Camera cam)
{
	GVector D(light.X - X, light.Y - Y, light.Z - Z, 0);
	D.normalize();
	N.normalize();
	double I;
	double Iconst = 0.20;
	double Idiff = 0.60 * max(0, GVector::scalar(N, D));


	GVector v(cam.cposition);
	v.normalize();
	GVector h(v);
	h = h + D;
	h.normalize();
	double Iblinn = 0.20 * pow(max(0, GVector::scalar(h, N)), 5);

	I = Iconst + Idiff + Iblinn;
	if (this->activeBrick)
	{
		I += this->activeIntencity;
		//if (I < 0) I = 0;
		//if (I > 1) I = 1;
	}
	return I;
}
