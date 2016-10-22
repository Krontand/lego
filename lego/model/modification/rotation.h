#pragma once
#include "modification.h"

class Rotation : public Modification
{
public:
	Rotation();
	~Rotation();

	void rotateX(Vertex* vertex);
	void rotateY(Vertex* vertex);
	void rotateZ(Vertex* vertex);

	virtual void setCenter(Vertex* center) override;

	virtual void run(Vertex* vertex) = 0;

protected:
	Vertex* center;
	double angle;
};

class RotationX : public Rotation
{
public:
	RotationX();
	RotationX(double angle);
	~RotationX();

	virtual void run(Vertex* vertex) override;
};

class RotationY : public Rotation
{
public:
	RotationY();
	RotationY(double angle);
	~RotationY();

	virtual void run(Vertex* vertex) override;
};

class RotationZ : public Rotation
{
public:
	RotationZ();
	RotationZ(double angle);
	~RotationZ();

	virtual void run(Vertex* vertex) override;
};

