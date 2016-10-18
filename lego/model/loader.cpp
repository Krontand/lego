#include "stdafx.h"
#include "../stdafx.h"
#include "loader.h"

Loader::Loader()
{
}

Loader::Loader(char* filename)
{
	this->filename = filename;
}

Loader::~Loader()
{
}

void Loader::openFile()
{
	if ((this->file = fopen(this->filename, "r")) == NULL)
	{
		throw LoaderOpenFileError();
	}
}

void Loader::closeFile()
{
	fclose(this->file);
}

Vertex Loader::readVertex()
{
	double tmpX, tmpY, tmpZ;

	if (fscanf_s(this->file, " %lf %lf %lf", &tmpX, &tmpY, &tmpZ) != 3)
	{
		throw LoaderBadFile();
	}
	Vertex v(tmpX, tmpY, tmpZ);

	return v;
}

Face Loader::readFace()
{
	int tmpA, tmpB, tmpC;

	if (fscanf_s(this->file, " %d %d %d", &tmpA, &tmpB, &tmpC) != 3)
	{
		throw LoaderBadFile();
	}

	Face f(tmpA, tmpB, tmpC);

	return f;
}

Brick* Loader::load(BaseObject* obj)
{
	Brick* brick = new Brick;

	this->openFile();
	FILE* f = this->file;

	char linetype;
	try
	{
		while (!feof(f))
		{
			fscanf_s(f, "%c", &linetype);
			switch (linetype)
			{
			case 'v':
				brick->addVertex(this->readVertex());
				break;

			case 'f':
				brick->addFace(this->readFace());
				break;

			case '#':
				while (linetype != '\0' && linetype != '\n')
				{
					fscanf_s(f, "%c", &linetype);
				}
				break;
			}
		}
		brick->setID(obj->getID());
		obj->add(brick);
	}
	catch (BaseException& err)
	{
		delete brick;
		brick = nullptr;
		throw LoaderError();
	}

	this->closeFile();

	return brick;
}
