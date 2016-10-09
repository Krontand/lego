/*!
\file text.h "interface/text.h"
\brief  Text interface class
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 1.0
\date 23 September 2016

Provide interface for creating/removing custom text
*/

#pragma once
#include "drawinterface.h"

/*!
\class Text text.h "interface/text.h"
\brief  Button interface class
Provide interface for creating/removing custom text

\todo Customise button style
*/

class Text : public BaseDrawInterfaceElement
{
public:
	/*! Empty constructor. No action. */
	Text();

	/*!
	Constructor display text
	\param[in] X X coordinate
	\param[in] Y Y coordinate
	\param[in] TEXT Text to display
	*/
	Text(int X, int Y, WCHAR* TEXT);

	/*!
	Display text
	\param[in] X1 X coordinate
	\param[in] Y1 Y coordinate
	\param[in] X2 not used
	\param[in] Y2 not used
	\param[in] TEXT Text to display
	*/
	bool display(int X1, int Y1, int X2, int Y2, WCHAR* TEXT) override;

	/*!
	Redraw text
	*/
	bool redraw() override;

	/*!
	Set text color
	\param[in] color Text color
	*/
	Text* SetColor(COLORREF color);

	/*!
	Set text weight
	\param[in] w Text weight
	*/
	Text* SetWeight(int w);

	/*!
	Set text height
	\param[in] h Text height
	*/
	Text* SetHeight(int h);

	/*!
	Set symbol width
	\param[in] h Text height
	*/
	Text* SetSymbolWidth(int w);
	
private:
	LOGFONT font;	/*!< Font style */
	int X;			/*!< X coordinate */
	int Y;			/*!< Y coordinate */
	WCHAR* TEXT;	/*!< Text to display */
	COLORREF COLOR;	/*!< Text color */
};