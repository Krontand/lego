#pragma once
#include "../scene/scene.h"

using std::vector;

class Render
{
public:
	Render(unsigned long* pixels, int height, int width);
	~Render();

	void run(Composite* bricks, Camera cam, Vertex light, int activeBrick);

	void line(int x0, int y0, int x1, int y1, int z0, int z1);
	void sun(int x0, int y0, int r, int z);

private:
	void fillFaces(Vertex A, Vertex B, Vertex C, Normal nA, Normal nB, Normal nC, COLORREF color, Vertex light, Camera cam, float t);
	void actBrickIntencity();
	double intencity(double X, double Y, double Z, GVector N, Vertex light, Camera cam);
	
	unsigned long* pixels;
	int height;
	int width;

	int* zbuffer;
	
	unsigned long* isolid;
	unsigned long* itransparent;
	float* c_buf;

	double activeIntencity;
	bool activeGrow;
	bool activeBrick;

}; 
