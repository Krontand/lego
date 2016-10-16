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

	if (fscanf_s(this->file, "%f %f %f", &tmpX, &tmpY, &tmpZ) != 3)
	{
		throw LoaderBadFile();
	}
	Vertex v(tmpX, tmpY, tmpZ);

	return v;
}

vector<int> Loader::readFace()
{
	double tmpA, tmpB, tmpC;

	if (fscanf_s(this->file, "%d %d %d", &tmpA, &tmpB, &tmpC) != 3)
	{
		throw LoaderBadFile();
	}

	vector<int> face(3);
	face[0] = tmpA;
	face[1] = tmpB;
	face[2] = tmpC;

	return face;
}

Brick* Loader::load()
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
