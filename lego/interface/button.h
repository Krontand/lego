/*!
\file button.h "interface/button.h"
\brief  Button interface class
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 1.0
\date 23 September 2016

Provide interface for creating/removing button
*/

#pragma once
#include "interface.h"

/*!
\class Button button.h "interface/button.h"
\brief  Button interface class
Provide interface for creating/removing button

\todo Customise button style
*/

class Button : public BaseInterfaceItem
{
public:
	/*! Empty constructor. No action. */
	Button();

	/*!
	Constructor sets ID in 'id' variable
	\param[in] ID Unique identify of button
	*/
	Button(int ID);

	/*!
	Constructor create and display button
	\param[in] X X coordinate
	\param[in] Y Y coordinate
	\param[in] HEIGHT Height of the window
	\param[in] WIDTH Width of the window
	\param[in] TEXT Text which is displaying on element
	*/
	Button(int X, int Y, int HEIGHT, int WIDTH, WCHAR* TEXT = NULL);

	/*!
	Destructor. Removes button (Does not free memory)
	*/
	~Button();

	/*!
	Create and display button
	\param[in] X X coordinate
	\param[in] Y Y coordinate
	\param[in] HEIGHT Height of the window
	\param[in] WIDTH Width of the window
	\param[in] TEXT Text which is displaying on element
	\return HWND of created window
	*/
	HWND create(int X, int Y, int HEIGHT, int WIDTH, WCHAR* TEXT) override;

	/*!
	Set image on button
	\param[in] rID Resourse ID (in resource.h)
	\return Value specifies the result of the message processing
	*/
	LRESULT setImage(int rID);

	/*!
	Removes button (Does not free memory)
	*/
	void remove() override;

	HWND bhWnd = NULL;	/*!< HWND of created window */

private:
	int ID;				/*!< Unique identify of button */
};