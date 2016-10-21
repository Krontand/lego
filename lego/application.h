#include "scene\scene.h"
#include "action.h"
#include "exception.h"

class Application
{
public:
	Application();
	Application(HWND hWnd, int x, int y, int width, int height);
	~Application();

	void call(Action &act, int id);

private:
	Scene* scene;
	Composite* loadedBricks;
};