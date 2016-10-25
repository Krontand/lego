#pragma once
#include "../scene/scene.h"

using namespace std;

class Render
{
public:
	Render(unsigned long* pixels, int height, int width);
	~Render();

	void run(Brick* brick, Camera* cam);

	void InitRenderedFaces(Vertex A, Vertex B, Vertex C);

	struct RFace {
		Vertex A, B, C;

		float xCA;
		float xCB;
		float xBA;
		float yCA;
		float yCB;
		float yBA;

		float nxA, nxB, nxC;
		float nyA, nyB, nyC;
		float nzA, nzB, nzC;

		unsigned long color;
		bool visible;
	};

private:
	void line(int x0, int y0, int x1, int y1);
	void fillFaces(Vertex A, Vertex B, Vertex C);

	unsigned long* pixels;
	int height;
	int width;

	vector<RFace> RenderedFaces;

}; 
