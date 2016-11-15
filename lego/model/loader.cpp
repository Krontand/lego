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
	int tmpnA, tmpnB, tmpnC;

	if (fscanf_s(this->file, " %d//%d %d//%d %d//%d", &tmpA, &tmpnA, &tmpB, &tmpnB, &tmpC, &tmpnC) != 6)
	{
		throw LoaderBadFile();
	}

	Face f(tmpA, tmpnA, tmpB, tmpnB, tmpC, tmpnC);

	return f;
}

GVector Loader::readNormal()
{
	double tmpX, tmpY, tmpZ;

	if (fscanf_s(this->file, " %lf %lf %lf", &tmpX, &tmpY, &tmpZ) != 3)
	{
		throw LoaderBadFile();
	}

	GVector N(tmpX, tmpY, tmpZ, 0);

	return N;
}

Brick* Loader::load(Composite* obj)
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

			case 'n':
				brick->addNormal(this->readNormal());
				break;

			case '#':
				while (linetype != '\0' && linetype != '\n')
				{
					fscanf_s(f, "%c", &linetype);
				}
				break;
			}
		}

		vector<int> facesGroup;
		vector<int> usedVertices;
		for (int i = 0; i < brick->facesCount() - 1; i++)
		{
			facesGroup.clear();

			Face c1Face = brick->faces[i];
			int c1Vertex = c1Face.getVertex();

			facesGroup.push_back(i);
			
			for (int k = 0; k < 3; k++)
			{
				bool found = false;
				for (int uv = 0; uv < usedVertices.size() && !found; uv++)
				{
					if (c1Vertex == usedVertices[uv])
					{
						found = true;
					}
				}
				if (!found)
				{
					usedVertices.push_back(c1Vertex);
					for (int j = i + 1; j < brick->facesCount(); j++)
					{
						Face c2Face = brick->faces[j];
						int c2Vertex = c2Face.getVertex();
						for (int l = 0; l < 3; l++)
						{
							if (c1Vertex == c2Vertex)
							{
								double angle = GVector::angle(brick->FNormal[c1Face.getNormal() - 1], brick->FNormal[c2Face.getNormal() - 1]);
								if (angle <= 30 && angle > 0)
								{
									facesGroup.push_back(j);
								}
							}
							c2Vertex = c2Face.getNextVertex();
						}
					}
				}
				c1Vertex = c1Face.getNextVertex();
			}

			vector<GVector> usedNormals;
			GVector RNormal = brick->FNormal[c1Face.getNormal() - 1];
			usedNormals.push_back(RNormal);
			for (int fgIndex = 1; fgIndex < facesGroup.size(); fgIndex++)
			{
				Face f = brick->faces[facesGroup[fgIndex]];
				GVector N = brick->FNormal[f.getNormal() - 1];
				bool found = false;
				for (int i = 0; i < usedNormals.size() && !found; i++)
				{
					if (N == usedNormals[i])
					{
						found = true;
					}
				}
				if (!found)
				{
					RNormal = (RNormal + N) / 2;
					usedNormals.push_back(N);
				}
			}

			for (int fgIndex = 0; fgIndex < facesGroup.size(); fgIndex++)
			{
				Face currentFace = brick->faces[facesGroup[fgIndex]];
				for (int vi = 0; vi < 3; vi++)
				{
					if (currentFace.getVertex() == c1Vertex)
					{
						brick->VNormal[facesGroup[fgIndex]][vi] = RNormal;
					}
					currentFace.getNextVertex();
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
		throw;
	}

	this->closeFile();

	return brick;
}
