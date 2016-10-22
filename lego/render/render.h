#pragma once
#include "../scene/scene.h"

using namespace std;

class Render
{
public:
	Render(unsigned long* pixels, int height, int width);
	~Render();

	void run(Brick* brick, Camera* cam);

private:
	void line(int x0, int y0, int x1, int y1);

	unsigned long* pixels;
	int height;
	int width;

};