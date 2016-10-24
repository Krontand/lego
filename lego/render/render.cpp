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
#pragma omp parallel for
	for (int faceIndex = 0; faceIndex < brick->facesCount(); faceIndex++)
	{
		Face face = brick->getFaces()[faceIndex];
		for (int vertexIndex = 0; vertexIndex < 3; vertexIndex++)
		{
			Vertex v0 = brick->getVertex()[face.getCurrent() - 1];
			Vertex v1 = brick->getVertex()[face.getNext() - 1];

			int x0 = (v0.getX());
			int y0 = (v0.getY());
			int x1 = (v1.getX());
			int y1 = (v1.getY());

			this->line(x0, y0, x1, y1);

		}
	}
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