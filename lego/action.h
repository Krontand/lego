#pragma once
#include "model\loader.h"
#include "model\modification\rotation.h"

class Action
{
public:
	virtual void Execute(Scene* scene, Composite* loadedBricks, int ID) = 0;
};

class ActionLoadbrick : public Action
{
public:
	ActionLoadbrick(char* filename)
	{
		this->filename = filename;
	}

	~ActionLoadbrick()
	{
	}

	virtual void Execute(Scene* scene, Composite* loadedBricks, int ID) override
	{
		Loader brick(this->filename);
		brick.load(loadedBricks);
	}

private:
	char* filename;
};

class ActionAddbrick : public Action
{
public:
	ActionAddbrick(int X, int Y, int Z, COLORREF color)
	{
		this->X = X;
		this->Y = Y;
		this->Z = Z;
		this->color = color;
	}

	~ActionAddbrick()
	{
	}

	virtual void Execute(Scene* scene, Composite* loadedBricks, int ID) override
	{
		Brick brick = *(loadedBricks->objects[ID]);
		scene->AddBrick(brick, this->X, this->Y, this->Z, this->color);
	}

private:
	int X, Y, Z;
	COLORREF color;
};

class ActionDraw : public Action
{
public:
	ActionDraw()
	{
	}

	~ActionDraw()
	{
	}

	virtual void Execute(Scene* scene, Composite* loadedBricks, int ID) override
	{
		scene->DrawScene();
	}
};

class ActionBrickRotateX : public Action
{
public:
	ActionBrickRotateX(double angle)
	{
		this->angle = angle;
	}

	~ActionBrickRotateX()
	{
	}

	virtual void Execute(Scene* scene, Composite* loadedBricks, int ID) override
	{
		RotationX* modification = new RotationX(this->angle);
		BaseObject* brick = scene->bricks;
		if (ID >= 0)
		{
			Composite* bricks = (Composite*)brick;
			brick = bricks->objects[ID];
		}
		brick->modificate(modification);
	}

private:
	double angle;
};

class ActionBrickRotateY : public Action
{
public:
	ActionBrickRotateY(double angle)
	{
		this->angle = angle;
	}

	~ActionBrickRotateY()
	{
	}

	virtual void Execute(Scene* scene, Composite* loadedBricks, int ID) override
	{
		RotationY* modification = new RotationY(this->angle);
		BaseObject* brick = scene->bricks;
		if (ID >= 0)
		{
			Composite* bricks = (Composite*)brick;
			brick = bricks->objects[ID];
		}
		brick->modificate(modification);
	}

private:
	double angle;
};

class ActionBrickRotateZ : public Action
{
public:
	ActionBrickRotateZ(double angle)
	{
		this->angle = angle;
	}

	~ActionBrickRotateZ()
	{
	}

	virtual void Execute(Scene* scene, Composite* loadedBricks, int ID) override
	{
		RotationZ* modification = new RotationZ(this->angle);
		BaseObject* brick = scene->bricks;
		if (ID >= 0)
		{
			Composite* bricks = (Composite*)brick;
			brick = bricks->objects[ID];
		}
		brick->modificate(modification);
	}

private:
	double angle;
};

class ActionCameraRotationHorizontal : public Action
{
public:
	ActionCameraRotationHorizontal(double angle)
	{
		this->angle = angle;
	}

	~ActionCameraRotationHorizontal()
	{
	}

	virtual void Execute(Scene* scene, Composite* loadedBricks, int ID) override
	{
		scene->cam->rotateHorizontalSphere(this->angle);
	}

private:
	double angle;
};

class ActionCameraRotationVertical : public Action
{
public:
	ActionCameraRotationVertical(double angle)
	{
		this->angle = angle;
	}

	~ActionCameraRotationVertical()
	{
	}

	virtual void Execute(Scene* scene, Composite* loadedBricks, int ID) override
	{
		scene->cam->rotateVerticalSphere(this->angle);
	}

private:
	double angle;
};