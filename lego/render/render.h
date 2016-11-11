#pragma once
#include "../scene/scene.h"

using std::vector;

class Render
{
public:
	Render(unsigned long* pixels, int height, int width);
	~Render();

	void run(Brick* brick, Camera* cam, Light* light);

private:
	void line(int x0, int y0, int x1, int y1);
	void fillFaces(Vertex A, Vertex B, Vertex C, GVector nA, GVector nB, GVector nC, int color, Light light);
	double intencity(double X, double Y, double Z, GVector N, Light light);
	
	unsigned long* pixels;
	int height;
	int width;

	int* zbuffer;

}; 
