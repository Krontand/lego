#pragma once
#include "model\loader.h"
#include "model\modification\rotation.h"
#include "model\modification\movement.h"

#define COLLISION_EPS 0.5

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
	ActionAddbrick(int X, int Y, int Z, COLORREF color, float trancparency)
	{
		this->X = X;
		this->Y = Y;
		this->Z = Z;
		this->color = color;
		this->trancparency = trancparency;
	}

	~ActionAddbrick()
	{
	}

	virtual void Execute(Scene* scene, Composite* loadedBricks, int ID) override
	{
		Brick brick = *(loadedBricks->objects[ID]);
		if (!scene->AddBrick(brick, this->X, this->Y, this->Z, this->color, this->trancparency))
		{
			throw AddBrickCollisionError();
		}
	}

private:
	int X, Y, Z;
	COLORREF color;
	float trancparency;
};

class ActionDeletebrick : public Action
{
public:
	ActionDeletebrick(int ID)
	{
		this->ID = ID;
	}

	~ActionDeletebrick()
	{
	}

	virtual void Execute(Scene* scene, Composite* loadedBricks, int ID) override
	{
		delete scene->bricks->objects[this->ID];
		scene->bricks->remove(this->ID);
	}

private:
	int ID;
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
		scene->DrawScene(ID);
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
			brick = bricks->get(ID);
		}
		brick->modificate(modification);
		Brick* currentBrick = (Brick*)brick;
		if (!scene->checkCollision(ID))
		{
			brick->applyModification();
		}
		else
		{
			this->angle /= 2;
			bool collision = false;
			while (abs(this->angle) > COLLISION_EPS)
			{
				Rotation* closer = new RotationX(this->angle);
				brick->modificate(closer);
				collision = (scene->checkCollision(ID) == 1);
				if (collision)
				{
					this->angle /= 2;
				}
				else
				{
					brick->applyModification();
				}
			}
		}
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
			brick = bricks->get(ID);
		}
		brick->modificate(modification);
		Brick* currentBrick = (Brick*)brick;
		if (!scene->checkCollision(ID))
		{
			brick->applyModification();
		}
		else
		{
			this->angle /= 2;
			bool collision = false;
			while (abs(this->angle) > COLLISION_EPS)
			{
				Rotation* closer = new RotationY(this->angle);
				brick->modificate(closer);
				collision = (scene->checkCollision(ID) == 1);
				if (collision)
				{
					this->angle /= 2;
				}
				else
				{
					brick->applyModification();
				}
			}
		}
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
			brick = bricks->get(ID);
		}
		brick->modificate(modification);
		Brick* currentBrick = (Brick*)brick;
		if (!scene->checkCollision(ID))
		{
			brick->applyModification();
		}
		else
		{
			this->angle /= 2;
			bool collision = false;
			while (abs(this->angle) > COLLISION_EPS)
			{
				Rotation* closer = new RotationZ(this->angle);
				brick->modificate(closer);
				collision = (scene->checkCollision(ID) == 1);
				if (collision)
				{
					this->angle /= 2;
				}
				else
				{
					brick->applyModification();
				}
			}
		}
	}

private:
	double angle;
};

class ActionBrickMoveX : public Action
{
public:
	ActionBrickMoveX(double shift)
	{
		this->shift = shift;
	}

	~ActionBrickMoveX()
	{
	}

	virtual void Execute(Scene* scene, Composite* loadedBricks, int ID) override
	{
		MovementX* modification = new MovementX(this->shift);
		BaseObject* brick = scene->bricks;
		if (ID >= 0)
		{
			Composite* bricks = (Composite*)brick;
			brick = bricks->get(ID);
		}
		brick->modificate(modification);
		Brick* currentBrick = (Brick*)brick;
		if (!scene->checkCollision(ID))
		{
			brick->applyModification();
		}
		else
		{
			this->shift /= 2;
			bool collision = false;
			while (abs(this->shift) > COLLISION_EPS)
			{
				Movement* closer = new MovementX(this->shift);
				brick->modificate(closer);
				collision = (scene->checkCollision(ID) == 1);
				if (collision)
				{
					this->shift /= 2;
				}
				else
				{
					brick->applyModification();
				}
			}
		}
	}

private:
	double shift;
};

class ActionBrickMoveY : public Action
{
public:
	ActionBrickMoveY(double shift)
	{
		this->shift = shift;
	}

	~ActionBrickMoveY()
	{
	}

	virtual void Execute(Scene* scene, Composite* loadedBricks, int ID) override
	{
		MovementY* modification = new MovementY(this->shift);
		BaseObject* brick = scene->bricks;
		if (ID >= 0)
		{
			Composite* bricks = (Composite*)brick;
			brick = bricks->get(ID);
		}
		brick->modificate(modification);
		Brick* currentBrick = (Brick*)brick;
		if (!scene->checkCollision(ID))
		{
			brick->applyModification();
		}
		else
		{
			this->shift /= 2;
			bool collision = false;
			while (abs(this->shift) > COLLISION_EPS)
			{
				Movement* closer = new MovementY(this->shift);
				brick->modificate(closer);
				collision = (scene->checkCollision(ID) == 1);
				if (collision)
				{
					this->shift /= 2;
				}
				else
				{
					brick->applyModification();
				}
			}
		}
	}

private:
	double shift;
};

class ActionBrickMoveZ : public Action
{
public:
	ActionBrickMoveZ(double shift)
	{
		this->shift = shift;
	}

	~ActionBrickMoveZ()
	{
	}

	virtual void Execute(Scene* scene, Composite* loadedBricks, int ID) override
	{
		MovementZ* modification = new MovementZ(this->shift);
		BaseObject* brick = scene->bricks;
		if (ID >= 0)
		{
			Composite* bricks = (Composite*)brick;
			brick = bricks->get(ID);
		}
		brick->modificate(modification);
		Brick* currentBrick = (Brick*)brick;
		if (!scene->checkCollision(ID))
		{
			brick->applyModification();
		}
		else
		{
			this->shift /= 2;
			bool collision = false;
			while (abs(this->shift) > COLLISION_EPS)
			{
				Movement* closer = new MovementZ(this->shift);
				brick->modificate(closer);
				collision = (scene->checkCollision(ID) == 1);
				if (collision)
				{
					this->shift /= 2;
				}
				else
				{
					brick->applyModification();
				}
			}
		}
	}

private:
	double shift;
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