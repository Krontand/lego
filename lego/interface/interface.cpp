#include "stdafx.h"
#include "../stdafx.h"
#include "button.h"
#include "interface.h"

HWND BaseInterfaceCtrl::hWnd;
HINSTANCE BaseInterfaceCtrl::hInst;

BaseInterfaceCtrl::BaseInterfaceCtrl()
{

}

BaseInterfaceCtrl::BaseInterfaceCtrl(HWND hWnd, HINSTANCE hInst)
{
	this->hWnd = hWnd;
	this->hInst = hInst;
}

BaseInterfaceCtrl::~BaseInterfaceCtrl()
{

}

BaseInterface::BaseInterface()
{

}

BaseInterface::~BaseInterface()
{
	for (int i = 0; i < this->interfaceCtrlList.size(); i++)
	{
		this->interfaceCtrlList[i]->_BaseInterfaceCtrl->remove();
		delete this->interfaceCtrlList[i]->_BaseInterfaceCtrl;
	}
	this->interfaceCtrlList.clear();
}

Button* BaseInterface::button(int ID)
{
	for (int i = 0; i < this->interfaceCtrlList.size(); i++)
	{
		if ((this->interfaceCtrlList[i]->id == ID) && (this->interfaceCtrlList[i]->type == EBUTTON))
		{
			return (Button*)this->interfaceCtrlList[i]->_BaseInterfaceCtrl;
		}
	}
	InterfaceCtrl* btn = new InterfaceCtrl;
	btn->type = EBUTTON;
	btn->id = ID;
	btn->_BaseInterfaceCtrl = new Button(ID);
	this->interfaceCtrlList.push_back(btn);
	return (Button*)btn->_BaseInterfaceCtrl;
}

void BaseInterface::remove(int ID)
{
	for (int i = 0; i < this->interfaceCtrlList.size(); i++)
	{
		if (this->interfaceCtrlList[i]->id == ID)
		{
			this->interfaceCtrlList[i]->_BaseInterfaceCtrl->remove();
			delete this->interfaceCtrlList[i]->_BaseInterfaceCtrl;
			this->interfaceCtrlList.erase(this->interfaceCtrlList.begin() + i);
		}
	}
}
