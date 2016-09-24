#include "stdafx.h"
#include "../stdafx.h"
#include "button.h"
#include "interface.h"

HWND BaseInterfaceItem::hWnd;
HINSTANCE BaseInterfaceItem::hInst;

BaseInterfaceItem::BaseInterfaceItem()
{

}

BaseInterfaceItem::BaseInterfaceItem(HWND hWnd, HINSTANCE hInst)
{
	this->hWnd = hWnd;
	this->hInst = hInst;
}

BaseInterfaceItem::~BaseInterfaceItem()
{

}

BaseInterface::BaseInterface()
{

}

BaseInterface::~BaseInterface()
{
	for (int i = 0; i < this->interfaceItemList.size(); i++)
	{
		this->interfaceItemList[i]->_BaseInterfaceItem->remove();
		delete this->interfaceItemList[i]->_BaseInterfaceItem;
	}
	this->interfaceItemList.clear();
}

Button* BaseInterface::button(int ID)
{
	for (int i = 0; i < this->interfaceItemList.size(); i++)
	{
		if ((this->interfaceItemList[i]->id == ID) && (this->interfaceItemList[i]->type == EBUTTON))
		{
			return (Button*)this->interfaceItemList[i]->_BaseInterfaceItem;
		}
	}
	InterfaceItem* btn = new InterfaceItem;
	btn->type = EBUTTON;
	btn->id = ID;
	btn->_BaseInterfaceItem = new Button(ID);
	this->interfaceItemList.push_back(btn);
	return (Button*)btn->_BaseInterfaceItem;
}

void BaseInterface::remove(int ID)
{
	for (int i = 0; i < this->interfaceItemList.size(); i++)
	{
		if (this->interfaceItemList[i]->id == ID)
		{
			this->interfaceItemList[i]->_BaseInterfaceItem->remove();
			this->interfaceItemList.erase(this->interfaceItemList.begin() + i);
		}
	}
}
