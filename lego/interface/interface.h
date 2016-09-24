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
class BaseInterfaceItem
{
public:
	/*!
	Empty constructor. No action.
	*/
	BaseInterfaceItem();

	/*!
	Constructor fills static variables.
	\param[in] hWnd HWND of main (parent) window
	\param[in] hInst Global instance
	*/
	BaseInterfaceItem(HWND hWnd, HINSTANCE hInst);

	/*!
	Destructor. No action.
	*/
	~BaseInterfaceItem();

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

Run BaseInterfaceItem constructor to initialise HWND and HINSTANCE variables.

Example of initialisation:
\code
InterfaceItemInit(hWnd, hInst);
\endcode

\warning Must be placed before creating elements!
*/
class InterfaceItemInit : public BaseInterfaceItem
{
public:
	/*!
	Constructor runs BaseInterfaceItem constructor
	\param[in] hWnd HWND of main (parent) window
	\param[in] hInst Global instance
	*/
	InterfaceItemInit(HWND hWnd, HINSTANCE hInst) : BaseInterfaceItem(hWnd, hInst) {};
	
	/*! Overrided emty method. No action. */
	virtual HWND create(int X = 0, int Y = 0, int HEIGHT = 0, int WIDTH = 0, WCHAR* TEXT = NULL) override { return NULL; };
	
	/*! Overrided emty method. No action. */
	virtual void remove() override {};
};

/// List of interface elements types
enum InterfaceItemType { 
	EBUTTON,	///< Button
	EEDITFIELD,	///< Edit field 
	ETEXT		///< Text
};

/*!
\struct BaseInterfaceItem interface.h "interface/interface.h"
\brief Each element (button, editfield etc) has own structure.
*/
typedef struct InterfaceItem
{
	enum InterfaceItemType type;			///< Interface Element type
	int id;									///< Unique ID of element
	BaseInterfaceItem* _BaseInterfaceItem;	///< Pointer to object of item
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
interface->button(1111)->remove(); // removed (memory still allocated in interfaceItemLists)
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
	(Cleans interfaceItemsList)
	*/
	~BaseInterface();

	/*!
	Provides access to button with unique ID
	\param[in] ID unique ID of button
	\return Pointer to button object
	*/
	Button* button(int ID);
	//Editfield editfield(int ID);
	//Text text(int ID);
private:
	vector<InterfaceItem*> interfaceItemList; /*!< List of all interface items */

};

