/*!
\file rectangle.h "interface/rectangle.h"
\brief  Rectangle interface class
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 1.0
\date 29 November 2016

Provide interface for creating/removing rectangle. (Somthing stupied xD)
*/

#pragma once
#include "drawinterface.h"
class BaseDrawInterfaceElement;

/*!
\class URectangle rectangle.h "interface/rectangle.h"
\brief  Rectangle interface class
Provide interface for creating/removing custom rectangle

\todo Customise rectangle style
*/

class URectangle : public BaseDrawInterfaceElement
{
public:
	/*! Empty constructor. No action. */
	URectangle();

	/*!
	Constructor display rectangle
	\param[in] X1 left X coordinate
	\param[in] Y1 top Y coordinate
	\param[in] X2 right X coordinate
	\param[in] Y2 bottom Y coordinate
	\param[in] color color of rectangle
	*/
	URectangle(int X1, int Y1, int X2, int Y2, COLORREF color);

	/*!
	Constructor display rectangle
	\param[in] X1 left X coordinate
	\param[in] Y1 top Y coordinate
	\param[in] X2 right X coordinate
	\param[in] Y2 bottom Y coordinate
	*/
	bool display(int X1, int Y1, int X2, int Y2, WCHAR* TEXT) override;

	/*!
	Redraw rectangle
	*/
	bool redraw() override;

	/*!
	Set rectangle color
	\param[in] color Rectangle color
	*/
	URectangle* SetColor(COLORREF color);

	/*!
	Set rectangle border color
	\param[in] color Rectangle border color
	*/
	URectangle* SetBorderColor(COLORREF color);

	/*!
	Set rectangle border width
	\param[in] w Rectangle border width
	*/
	URectangle* SetBorderWidth(int w);

private:
	int X1;			/*!< X coordinate */
	int Y1;			/*!< Y coordinate */
	int X2;			/*!< X coordinate */
	int Y2;			/*!< Y coordinate */
	int bWidth;		/*!< Border width */
	COLORREF COLOR;		/*!< Rectangle color */
	COLORREF bCOLOR;	/*!< Border color */
};