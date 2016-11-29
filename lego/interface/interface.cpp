#include "stdafx.h"
#include "../stdafx.h"
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

Combobox* BaseInterface::combobox(int ID)
{
	for (int i = 0; i < this->interfaceCtrlList.size(); i++)
	{
		if ((this->interfaceCtrlList[i]->id == ID) && (this->interfaceCtrlList[i]->type == ECOMBO))
		{
			return (Combobox*)this->interfaceCtrlList[i]->_BaseInterfaceCtrl;
		}
	}
	InterfaceCtrl* cb = new InterfaceCtrl;
	cb->type = ECOMBO;
	cb->id = ID;
	cb->_BaseInterfaceCtrl = new Combobox(ID);
	this->interfaceCtrlList.push_back(cb);
	return (Combobox*)cb->_BaseInterfaceCtrl;
}

Editfield* BaseInterface::editfield(int ID)
{
	for (int i = 0; i < this->interfaceCtrlList.size(); i++)
	{
		if ((this->interfaceCtrlList[i]->id == ID) && (this->interfaceCtrlList[i]->type == EEDITFIELD))
		{
			return (Editfield*)this->interfaceCtrlList[i]->_BaseInterfaceCtrl;
		}
	}
	InterfaceCtrl* cb = new InterfaceCtrl;
	cb->type = EEDITFIELD;
	cb->id = ID;
	cb->_BaseInterfaceCtrl = new Editfield(ID);
	this->interfaceCtrlList.push_back(cb);
	return (Editfield*)cb->_BaseInterfaceCtrl;
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

COLORREF colorDialog()
{
	CHOOSECOLOR cc = { 0 };
	cc.lStructSize = sizeof(cc);
	COLORREF cust_colors[16] = { 0 };
	cc.lpCustColors = cust_colors;

	if (ChooseColor(&cc)) {
		return cc.rgbResult;
	}

	return RGB(255, 255, 255);
}
