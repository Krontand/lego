/*!
\file interface.h "interface/interface.h"
\brief  Common interface class
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 1.0
\date 23 September 2016

Provide interface for creating/removing/updating common interface items
*/

#pragma once
using namespace std;

/*!
\class BaseInterfaceItem interface.h "interface/interface.h"
\brief  Base interface class. Parent of basic items.

Contains HWND of parent (main) window and HINSTANCE.
Provide interface for children by virtual methods
*/
class BaseInterfaceCtrl
{
public:
	/*!
	Empty constructor. No action.
	*/
	BaseInterfaceCtrl();

	/*!
	Constructor fills static variables HWND and HINSTANCE.
	\param[in] hWnd HWND of main (parent) window
	\param[in] hInst Global instance
	*/
	BaseInterfaceCtrl(HWND hWnd, HINSTANCE hInst);

	/*!
	Destructor. No action.
	*/
	~BaseInterfaceCtrl();

	/*!
	Creating interface element. Virtual.
	\param[in] X X coordinate
	\param[in] Y Y coordinate
	\param[in] HEIGHT Height of the window
	\param[in] WIDTH Width of the window
	\param[in] TEXT Text which is displaying on element
	\return HWND of created window
	*/
	virtual HWND create(int X = 0, int Y = 0, int HEIGHT = 0, int WIDTH = 0, WCHAR* TEXT = NULL) = 0;
	
	/*!
	Will destroy item. Function does not free memory.
	*/
	virtual void remove() = 0;

protected:
	static HWND hWnd;		/*!< HWND of main (parent) window */
	static HINSTANCE hInst;	/*!< Global instance */
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
class InterfaceCtrlInit : public BaseInterfaceCtrl
{
public:
	/*!
	Empty constructor. No action.
	*/
	InterfaceCtrlInit() {};

	/*!
	Constructor runs BaseInterfaceCtrl constructor
	\param[in] hWnd HWND of main (parent) window
	\param[in] hInst Global instance
	*/
	InterfaceCtrlInit(HWND hWnd, HINSTANCE hInst) : BaseInterfaceCtrl(hWnd, hInst) {};
	
	/*! Overrided emty method. No action. */
	virtual HWND create(int X = 0, int Y = 0, int HEIGHT = 0, int WIDTH = 0, WCHAR* TEXT = NULL) override { return NULL; };
	
	/*! Overrided emty method. No action. */
	virtual void remove() override {};
};

/// List of interface elements types
enum InterfaceCtrlType { 
	EBUTTON,	///< Button
	EEDITFIELD,	///< Edit field 
	ETEXT		///< Text
};

/*!
\struct BaseInterfaceCtrl interface.h "interface/interface.h"
\brief Each element (button, editfield etc) has own structure.
*/
typedef struct InterfaceCtrl
{
	enum InterfaceCtrlType type;			///< Interface Element type
	int id;									///< Unique ID of element
	BaseInterfaceCtrl* _BaseInterfaceCtrl;	///< Pointer to object of Ctrl
};

class Button;

/*!
\class BaseInterface interface.h "interface/interface.h"
\brief  Main interface class. Provides access to create/remove/update elements.

Contains list of all interface elemets.

Example of creating and removing button with ID = 1111:
\code
interface = new BaseInterface;
interface->button(1111)->create(10,10,100,200,TEXT("MY BUTTON")); // created
interface->button(1111)->remove(); // removed (memory still allocated in interfaceCtrlLists)
\endcode
*/
class BaseInterface
{
public:
	/*!
	Empty constructor. No action.
	*/
	BaseInterface();
	/*!
	Destructor. Removes all interface items and dealocates memory.
	(Cleans interfaceCtrlsList)
	*/
	~BaseInterface();

	/*!
	Provides access to button with unique ID
	\param[in] ID unique ID of button
	\return Pointer to button object
	*/
	Button* button(int ID);
	//Editfield editfield(int ID);

	/*!
	Will destroy item with requested ID and free memory
	*/
	void remove(int ID);

private:
	vector<InterfaceCtrl*> interfaceCtrlList; /*!< List of all interface items */
};

