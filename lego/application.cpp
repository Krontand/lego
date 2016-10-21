#include "stdafx.h"
#include "application.h"
#include "model\loader.h"
#include "scene\scene.h"

Application::Application()
{
}

Application::Application(HWND hWnd, int x, int y, int width, int height)
{
	this->scene = new Scene(hWnd, x, y, width, height);
	if (!this->scene)
	{
		throw AllocationMemoryError();
	}

	this->loadedBricks = new Composite;
	if (!this->loadedBricks)
	{
		delete this->scene;
		this->scene = nullptr;
		throw AllocationMemoryError();
	}

	Loader first("objs/one.obj");

	first.load(this->loadedBricks);
}

Application::~Application()
{
	delete this->scene;
	delete this->loadedBricks;
	this->scene = nullptr;
	this->loadedBricks = nullptr;
}

void Application::call(Action& act, int ID)
{
	act.Execute(this->scene, this->loadedBricks, ID);
}