#include "stdafx.h"
#include "../stdafx.h"
#include "loader.h"

Loader::Loader()
{
}

Loader::Loader(char* filename)
{
	this->filename = filename;

	this->maxX = 0;
	this->maxY = 0;
	this->maxZ = 0;
	this->minX = 0;
	this->minY = 0;
	this->minZ = 0;
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

	tmpX *= 0.7;
	tmpY *= 0.7;
	tmpZ *= 0.7;

	Vertex v(tmpX, tmpY, tmpZ);

	if (tmpX < this->minX) this->minX = tmpX;
	if (tmpY < this->minY) this->minY = tmpY;
	if (tmpZ < this->minZ) this->minZ = tmpZ;
	if (tmpX > this->maxX) this->maxX = tmpX;
	if (tmpY > this->maxY) this->maxY = tmpY;
	if (tmpZ > this->maxZ) this->maxZ = tmpZ;

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

Brick* Loader::load(Composite* obj)
{
	Brick* brick = new Brick;

	this->openFile();
	FILE* f = this->file;

	Face face;
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
				face = this->readFace();
				face.calcNormal(
					brick->vertex[face.getA() - 1], 
					brick->vertex[face.getB() - 1],
					brick->vertex[face.getC() - 1]
				);

				brick->addFace(face);
				break;

			case '#':
				while (linetype != '\0' && linetype != '\n')
				{
					fscanf_s(f, "%c", &linetype);
				}
				break;
			}
		}

		for (int i = 0; i < brick->facesCount() - 1; i++)
		{
			Face c1Face = brick->faces[i];
			for (int j = i + 1; j < brick->facesCount(); j++)
			{
				Face c2Face = brick->faces[j];
				int c1Vertex = c1Face.getCurrent();
				for (int k = 0; k < 3; k++)
				{
					int c2Vertex = c2Face.getCurrent();
					for (int l = 0; l < 3; l++)
					{
						if (c1Vertex == c2Vertex)
						{
							double angle = GVector::angle(c1Face.Normal, c2Face.Normal);
							if (angle > 130)
							{
								brick->faces[i].VNormal[k] = (brick->faces[i].VNormal[k] + c2Face.Normal) / 2.0;
								brick->faces[j].VNormal[l] = (brick->faces[j].VNormal[l] + c1Face.Normal) / 2.0;
							}
						}
						c2Vertex = c2Face.getNext();
					}
					c1Vertex = c1Face.getNext();
				}
			}
		}

		brick->ID = obj->ID;
		
		double cX = this->maxX - (this->maxX - this->minX) / 2;
		double cY = this->maxY - (this->maxY - this->minY) / 2;
		double cZ = this->maxZ - (this->maxZ - this->minZ) / 2;

		Vertex center(cX, cY, cZ);
		brick->center = center;

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
