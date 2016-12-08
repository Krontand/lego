/*!
\file gvector.h "scene/scene.h"
\brief  Main scene 
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 2.0
\date 21 October 2016

Provide interface to bricks on scene and camera
*/

#pragma once

#include "../geometry\gmatrix.h"
#include "../geometry\stereometry.h"
#include "../model/composite.h"
#include "camera.h"
//#include "light.h"

class Render;

#include "../render/render.h"

/*!
\class Scene scene.h "scene/scene.h"
\brief Main scene 

Provide interface to bricks on scene, camera. Launchs render.
*/
class Scene
{
public:
	/*!
	Emty constructor. Set up scene with NULL values (but why? ._.)
	*/
	Scene();

	/*!
	Constructor. Set up scene with incoming values.
	\param[in] hWnd HWND of global window
	\param[in] x X coordinate of bitmap
	\param[in] y Y coordinate of bitmap
	\param[in] width Bitmap width
	\param[in] height Bitmap height
	*/
	Scene(HWND hWnd, int x, int y, int width, int height);

	/*!
	Destructor. Free memory.
	*/
	~Scene();

	/*!
	Draws background and launch render to draw bricks
	*/
	void DrawScene(int ActiveBrick = -1);

	/*!
	Add brick into scene bricks array. Set model in (0,0,0) monitor coordinates
	\param[in] brick Brick to add
	*/
	bool AddBrick(Brick brick, int X, int Y, int Z, COLORREF color);

	/*!
	Transfer vertices from world to camera coordinates
	*/
	void toCam();

	bool checkCollision(int ID);
	
	Composite* bricks;	/*!< Scene bricks array */
	Camera* cam;		/*!< Camera object */
	Vertex light;		/*!< Light object */
	Vertex slight;		/*!< Light object in scene coordinates */

private:
	/*!
	Set up bitmap with user values. Initialize pixels array
	*/
	void InitBitmap();

	int X;		/*!< X coordinate of bitmap */
	int Y;		/*!< Y coordinate of bitmap */
	int width;	/*!< Bitmap width */
	int height;	/*!< Bitmap height */

	vector<Vertex> floorX; /*!< Array of x vertices -> sharped floor */
	vector<Vertex> floorZ; /*!< Array of x vertices -> sharped floor */

	vector<Vertex> floorXSC; /*!< Array of x vertices -> sharped floor */
	vector<Vertex> floorZSC; /*!< Array of x vertices -> sharped floor */
	
	/*!
	Fills floor array with vertices coordinates
	*/
	void initFloor();
	
	/*!
	Fill background with blue color
	*/
	void drawBG();

	/*!
	Draw floor lines from array
	*/
	void drawFloor();

	bool checkFaceVisibility(Brick* nbrick, int faceIndex, GMatrix nresult);

	unsigned long* pixels;	/*!< Direct access to bitmap. Filling array = drawing */

	BITMAPINFO sBmInfo;	/*! Bitmap settings */
	HBITMAP sBmp;		/*! Bimap (cap) */
	HDC hdc;			/*! Bitmap hdc */
	HDC hdcMem;			/*! Memory hdc */
	HWND hWnd;			/*! Global HWND */

	Render* render;		/*! Render class. Calculate image */

};