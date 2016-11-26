#pragma once
#include "../scene/scene.h"

using std::vector;

class Render
{
public:
	Render(unsigned long* pixels, int height, int width);
	~Render();

	void run(Brick* brick, Camera* cam, Vertex light);

private:
	void line(int x0, int y0, int x1, int y1);
	void fillFaces(Vertex A, Vertex B, Vertex C, Normal nA, Normal nB, Normal nC, COLORREF color, Vertex light);
	double intencity(double X, double Y, double Z, GVector N, Vertex light);
	
	unsigned long* pixels;
	int height;
	int width;

	int* zbuffer;

}; 
