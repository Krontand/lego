/*!
\file normal.h "model/normal.h"
\brief  Define normal (object container for GVector)
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 2.0
\date 19 November 2016

Provide interface for geometric vector like base object
*/

#pragma once

#include "modification\modification.h"
#include "baseobject.h"
#include "../geometry\gmatrix.h"

/*!
\class Normal normal.h "model/normal.h"
\brief  Define normal (object container for GVector)

Provide interface for geometric vector like base object
*/
class Normal : public GVector, public BaseObject
{
public:
	Normal();
	Normal(const GVector& v);
	Normal(GVector&& v);
	Normal(const Normal& other);
	Normal(Normal&& other);
	Normal(double X, double Y, double Z, double length);
	~Normal();

	Normal& operator=(Normal other);
	Normal operator+(const Normal& other);
	Normal operator-(const Normal& other);
	Normal operator/(const double value);
	Normal operator*(const double value);
	double& operator[](const size_t index);
	const double& operator[](const size_t index) const;
	Normal operator*(GMatrix matrix);

	virtual BaseObject* modificate(Modification* modification, Vertex* center) override;

	virtual void applyModification() override {};
};