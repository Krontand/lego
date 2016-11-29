#include "stdafx.h"
#include "../stdafx.h"
#include "text.h"
#include "drawinterface.h"

HDC BaseDrawInterfaceElement::hdc;

BaseDrawInterfaceElement::BaseDrawInterfaceElement()
{

}

BaseDrawInterfaceElement::BaseDrawInterfaceElement(HDC hdc)
{
	this->hdc = hdc;
}

BaseDrawInterfaceElement::~BaseDrawInterfaceElement()
{

}

BaseDrawInterface::BaseDrawInterface()
{

}

BaseDrawInterface::~BaseDrawInterface()
{
	for (int i = 0; i < this->interfaceDrawList.size(); i++)
	{
		delete this->interfaceDrawList[i]->_BaseInterfaceDraw;
	}
	this->interfaceDrawList.clear();
}

Text* BaseDrawInterface::text(int ID)
{
	for (int i = 0; i < this->interfaceDrawList.size(); i++)
	{
		if ((this->interfaceDrawList[i]->id == ID) && (this->interfaceDrawList[i]->type == EDTEXT))
		{
			return (Text*)this->interfaceDrawList[i]->_BaseInterfaceDraw;
		}
	}
	InterfaceDraw* txt = new InterfaceDraw;
	txt->type = EDTEXT;
	txt->id = ID;
	txt->_BaseInterfaceDraw = new Text();
	this->interfaceDrawList.push_back(txt);
	return (Text*)txt->_BaseInterfaceDraw;
}

URectangle* BaseDrawInterface::rectangle(int ID)
{
	for (int i = 0; i < this->interfaceDrawList.size(); i++)
	{
		if ((this->interfaceDrawList[i]->id == ID) && (this->interfaceDrawList[i]->type == EDRECTANGLE))
		{
			return (URectangle*)this->interfaceDrawList[i]->_BaseInterfaceDraw;
		}
	}
	InterfaceDraw* txt = new InterfaceDraw;
	txt->type = EDRECTANGLE;
	txt->id = ID;
	txt->_BaseInterfaceDraw = new URectangle();
	this->interfaceDrawList.push_back(txt);
	return (URectangle*)txt->_BaseInterfaceDraw;
}

bool BaseDrawInterface::redraw(int ID)
{
	bool flag = true;
	for (int i = 0; i < this->interfaceDrawList.size(); i++)
	{
		if (ID == -1 || this->interfaceDrawList[i]->id == ID)
		{
			if (!this->interfaceDrawList[i]->_BaseInterfaceDraw->redraw())
			{
				flag = false;
			}
		}
	}
	return flag;
}

void BaseDrawInterface::remove(int ID)
{
	for (int i = 0; i < this->interfaceDrawList.size(); i++)
	{
		if (this->interfaceDrawList[i]->id == ID)
		{
			delete this->interfaceDrawList[i]->_BaseInterfaceDraw;
			this->interfaceDrawList.erase(this->interfaceDrawList.begin() + i);
		}
	}
}
