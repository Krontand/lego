/*!
\file combobox.h "interface/combobox.h"
\brief  Combobox interface class
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 1.0
\date 29 November 2016

Provide interface for creating/removing/updating combobox
*/

#pragma once
#include <windowsx.h>

#include "interface.h"
class BaseInterfaceCtrl;

/*!
\class Combobox combobox.h "interface/combobox.h"
\brief  Combobox interface class
Provide interface for creating/removing/updating combobox
*/

class Combobox : public BaseInterfaceCtrl
{
public:
	/*! Empty constructor. No action. */
	Combobox();

	/*!
	Constructor sets ID in 'id' variable
	\param[in] ID Unique identify of combobox
	*/
	Combobox(int ID);

	/*!
	Constructor create and display combobox
	\param[in] X X coordinate
	\param[in] Y Y coordinate
	\param[in] HEIGHT Height of the window
	\param[in] WIDTH Width of the window
	\param[in] TEXT Text which is displaying on element
	*/
	Combobox(int X, int Y, int HEIGHT, int WIDTH, WCHAR* TEXT = NULL);

	/*!
	Destructor. Removes button (Does not free memory)
	*/
	~Combobox();

	/*!
	Create and display combobox
	\param[in] X X coordinate
	\param[in] Y Y coordinate
	\param[in] HEIGHT Height of the window
	\param[in] WIDTH Width of the window
	\param[in] TEXT Text which is displaying on element
	\return HWND of created window
	*/
	HWND create(int X, int Y, int HEIGHT, int WIDTH, WCHAR* TEXT) override;

	void addItem(WCHAR* item);

	int getCurrentItem();

	HWND getHWND();

	/*!
	Removes combobox (Does not free memory)
	*/
	void remove() override;

private:
	int ID;				/*!< Unique identify of combobox */
	HWND chWnd = NULL;	/*!< HWND of created window */
};