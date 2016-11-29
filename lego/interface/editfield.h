/*!
\file button.h "interface/editfield.h"
\brief  Editfield interface class
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 1.0
\date 23 September 2016

Provide interface for creating/removing editfield
*/

#pragma once
#include "interface.h"
class BaseInterfaceCtrl;

/*!
\class Editfield editfield.h "interface/editfield.h"
\brief  Editfield interface class
Provide interface for creating/removing editfield

\todo Customise editfield style
*/

class Editfield : public BaseInterfaceCtrl
{
public:
	/*! Empty constructor. No action. */
	Editfield();

	/*!
	Constructor sets ID in 'id' variable
	\param[in] ID Unique identify of editfield
	*/
	Editfield(int ID);

	/*!
	Constructor create and display editfield
	\param[in] X X coordinate
	\param[in] Y Y coordinate
	\param[in] HEIGHT Height of the window
	\param[in] WIDTH Width of the window
	\param[in] TEXT Text which is displaying on element
	*/
	Editfield(int X, int Y, int HEIGHT, int WIDTH, WCHAR* TEXT = NULL);

	/*!
	Destructor. Removes editfield (Does not free memory)
	*/
	~Editfield();

	/*!
	Create and display editfield
	\param[in] X X coordinate
	\param[in] Y Y coordinate
	\param[in] HEIGHT Height of the window
	\param[in] WIDTH Width of the window
	\param[in] TEXT Text which is displaying on element
	\return HWND of created window
	*/
	HWND create(int X, int Y, int HEIGHT, int WIDTH, WCHAR* TEXT) override;

	/*!
	Get text from editfield
	\return text
	*/
	WCHAR* getText();

	/*!
	Get integer value from editfield
	\return integer value
	*/
	int getInt();

	HWND getHWND();

	/*!
	Removes editfield (Does not free memory)
	*/
	void remove() override;

private:
	int ID;				/*!< Unique identify of editfield */
	HWND ehWnd = NULL;	/*!< HWND of created window */
};