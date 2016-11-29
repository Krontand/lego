/*!
\file interface.h "interface/interface.h"
\brief  Common draw interface class
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 1.0
\date 09 October 2016

Provide interface for drawing common interface
*/

#pragma once
using std::vector;

/*!
\class BaseDrawInterfaceElement drawinterface.h "interface/drawinterface.h"
\brief  Base draw interface class. Parent of basic draw classes.

Contains global HDC.
Provide interface for children by virtual methods
*/
class BaseDrawInterfaceElement
{
public:
	/*!
	Empty constructor. No action.
	*/
	BaseDrawInterfaceElement();

	/*!
	Constructor fills static variables HWND and HINSTANCE.
	\param[in] hdc global HDC
	*/
	BaseDrawInterfaceElement(HDC hdc);

	/*!
	Destructor. No action.
	*/
	~BaseDrawInterfaceElement();

	/*!
	Creating interface element. Virtual.
	\param[in] X1 start X coordinate
	\param[in] Y1 start Y coordinate
	\param[in] X2 end X coordinate
	\param[in] Y2 end Y coordinate
	\param[in] TEXT Text which is displaying on element
	\return bool result of drawing element
	*/
	virtual bool display(int X1 = 0, int Y1 = 0, int X2 = 0, int Y2 = 0, WCHAR* TEXT = NULL) = 0;

	/*!
	Redraw existed element
	*/
	virtual bool redraw() = 0;
protected:
	static HDC hdc;		/*!< Global HDC */
};

/*!
\class BaseInterfaceItemInit interface.h "interface/interface.h"
\brief  Initialisation interface class.

Run BaseInterfaceItem constructor to initialise HWND, HINSTANCE and HDC variables.

Example of initialisation:
\code
InterfaceItemInit(hWnd, hInst);
\endcode

\warning Must be placed before creating elements!
*/
class InterfaceDrawInit : public BaseDrawInterfaceElement
{
public:
	/*!
	Empty constructor. No action.
	*/
	InterfaceDrawInit() {};

	/*!
	Constructor runs BaseInterfaceCtrl constructor
	\param[in] hWnd HWND of main (parent) window
	\param[in] hInst Global instance
	*/
	InterfaceDrawInit(HDC hdc) : BaseDrawInterfaceElement(hdc) {};

	/*! Overrided emty method. No action. */
	virtual bool display(int X1 = 0, int Y1 = 0, int X2 = 0, int Y2 = 0, WCHAR* TEXT = NULL) override { return false; };

	/*! Overrided emty method. No action. */
	virtual bool redraw() override { return false; };
};

/// List of interface elements types with CAP comments :D
enum InterfaceDrawType {
	EDTEXT,		///< Text
	EDLINE,		///< Line
	EDRECTANGLE	///< Rectangle
};

/*!
\struct BaseInterfaceCtrl interface.h "interface/interface.h"
\brief Each element (button, editfield etc) has own structure.
*/
typedef struct InterfaceDraw
{
	enum InterfaceDrawType type;					///< Interface Element type
	int id;											///< Unique ID of element
	BaseDrawInterfaceElement* _BaseInterfaceDraw;	///< Pointer to object of element
};

#include "text.h"
#include "rectangle.h"
class Text;
class URectangle;

/*!
\class BaseDrawInterface drawinterface.h "interface/drawinterface.h"
\brief  Main drwa interface class. Provides access to create/remove/update elements.

Contains list of all interface elemets.

Example of creating and removing button with ID = 1111:
\code
interface = new BaseInterface;
interface->button(1111)->create(10,10,100,200,TEXT("MY BUTTON")); // created
interface->button(1111)->remove(); // removed (memory still allocated in interfaceCtrlLists)
\endcode
*/
class BaseDrawInterface
{
public:
	/*!
	Empty constructor. No action.
	*/
	BaseDrawInterface();
	/*!
	Destructor. Removes all interface items and dealocates memory.
	(Cleans interfaceCtrlsList)
	*/
	~BaseDrawInterface();

	/*!
	Provides access to text with unique ID
	\param[in] ID unique ID of text
	\return Pointer to text object
	*/
	Text* text(int ID);

	/*!
	Provides access to draw rectangle with unique ID
	\param[in] ID unique ID of rectangle
	\return Pointer to rectangle object
	*/
	URectangle* rectangle(int ID);
	

	/*!
	Redraw all elements in array
	\return true if all elements redrawed
	*/
	bool redraw(int ID = -1);

	/*!
	Will remove item with requested ID and free memory
	*/
	void remove(int ID);

private:
	vector<InterfaceDraw*> interfaceDrawList; /*!< List of all interface items */
};

