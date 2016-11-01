#pragma once

class GVector;
class GMatrix;

class Camera
{
public:
	Camera();
	Camera(GVector position, GVector direction);
	
	void rotateHorizontalSphere(double angle);
	void rotateVerticalSphere(double angle);

	GVector position;
	GVector target;

	GMatrix cameraview();

private:
	GVector right;
	GVector up;
	GVector direction;

};
