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
#include "../model/composite.h"
#include "camera.h"
#include "light.h"

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
	void DrawScene();

	/*!
	Add brick into scene bricks array. Set model in (0,0,0) monitor coordinates
	\param[in] brick Brick to add
	*/
	void AddBrick(Brick brick);
	
	Composite* bricks;	/*!< Scene bricks array */
	Camera* cam;		/*!< Camera object */
	Light* light;		/*!< Light object */

private:
	/*!
	Set up bitmap with user values. Initialize pixels array
	*/
	void InitBitmap();

	int X;		/*!< X coordinate of bitmap */
	int Y;		/*!< Y coordinate of bitmap */
	int width;	/*!< Bitmap width */
	int height;	/*!< Bitmap height */

	unsigned long* pixels;	/*!< Direct access to bitmap. Filling array = drawing */

	BITMAPINFO sBmInfo;	/*! Bitmap settings */
	HBITMAP sBmp;		/*! Bimap (cap) */
	HDC hdc;			/*! Bitmap hdc */
	HDC hdcMem;			/*! Memory hdc */
	HWND hWnd;			/*! Global HWND */

	Render* render;		/*! Render class. Calculate image */

};