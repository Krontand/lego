/*!
\file gvector.h "geometry/gvector.h"
\brief  Define geometric vector
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 2.0
\date 02 November 2016

Provide interface for geometric vector with 4 items
*/

#pragma once

#include "exception.h"

using std::vector;

class GMatrix;

/*!
\class GVector gvector.h "geometry/gvector.h"
\brief  Define geometric vector

Geometric vector specified with 3 coordinates and length value
*/
class GVector 
{
public:
	/*!
	Emty constructor. Creates vector and sets it with zero values
	*/
	GVector();

	/*!
	Constructor. Creates vector and sets it with incoming values
	\param[in] X X coordinate
	\param[in] Y Y coordinate
	\param[in] Z Z coordinate
	\param[in] length Length of vector
	*/
	GVector(double X, double Y, double Z, double lenglth);
	
	/*!
	Constructor. Copies incoming vector.
	\param[in] other Source vector to copy.
	*/
	GVector(const GVector& other);

	/*!
	Constructor. Transfer incoming vector.
	\param[in] other Source vector to transfer.
	*/
	GVector(GVector&& other);

	/*!
	Destructor. Clears current vector.
	*/
	~GVector();

	/*!
	Sets vector with sourse`s vector values
	\param[in] other Source vector to copy
	\return GVector current vector
	*/
	GVector& operator=(GVector& other);

	/*!
	Sets vector with sourse`s vector values
	\param[in] other Source vector to copy
	\return GVector current vector
	*/
	GVector& operator=(const GVector& other);

	/*!
	Sets vector with sourse`s vector values
	\param[in] other Source vector to transfer
	\return GVector current vector
	*/
	GVector& operator=(GVector&& other);

	/*!
	Sum this vector with incoming vector values
	\param[in] other Source vector to sum
	\return GVector vector after sum
	*/
	GVector& operator+(const GVector other);

	/*!
	Divide this vector with incoming value
	\param[in] value Value to divide
	\return GVector vector after divide
	*/
	GVector& operator/(const double value);

	/*!
	Chooses coordinate by index: 0-X; 1-Y; 2-Z; 3-length
	\param[in] index Index of choosen coordinate
	\return value of choosen coordinate
	*/
	double& operator[](const size_t index);

	/*!
	Const method. Chooses coordinate by index: 0-X; 1-Y; 2-Z; 3-length
	\param[in] index Index of choosen coordinate
	\return value of choosen coordinate
	*/
	const double& operator[](const size_t index) const;

	/*!
	Returns current vector
	\return Current vector
	*/
	vector<double> getVec() const;

	/*!
	Geometric length of vector
	\return Length of vector
	*/
	double length();

	/*!
	Normalize current vector
	\return Normalized vector
	*/
	GVector normalize();

	/*!
	Vector product
	\param[in] first First vector to multiply
	\param[in] second Second vector to multiply
	\return Vector after cross product
	*/
	static GVector cross(GVector first, GVector second);

	/*!
	Scalar product
	\param[in] first First vector to multiply
	\param[in] second Second vector to multiply
	\return Double value after production
	*/
	static double scalar(GVector first, GVector second);

	/*!
	Angle between two vectors
	\param[in] first First vector
	\param[in] second Second vector
	\return Angle between vectors in degrees
	*/
	static double angle(GVector first, GVector second);

	/*!
	Multiply this vector by matrix
	\param[in] matrix Matrix to multiply
	\return Vector multiplied by matrix
	*/
	GVector operator*(GMatrix matrix);

private:
	vector<double> vec;	/*!< Vector contains coordinates */
};