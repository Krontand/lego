/*!
\file gmatrix.h "geometry/gmatrix.h"
\brief  Define geometric matrix
\author Dmitry Zaitsev
\copyright © BMSTU All rights violated.
\version 2.0
\date 02 November 2016

Provide interface for geometric marix 4x4
*/

#pragma once
 
#include "gvector.h"

using std::vector;

/*!
\class GMatrix gvector.h "geometry/gmatrix.h"
\brief  Define geometric matrix

Geometric matrix 4x4
*/
class GMatrix
{
public:
	/*!
	Emty constructor. Creates matrix and sets it with zero values
	*/
	GMatrix();

	/*!
	Constructor. Copies incoming matrix.
	\param[in] other Source matrix to copy.
	*/
	GMatrix(const GMatrix& other);

	/*!
	Constructor. Transfer incoming matrix.
	\param[in] other Source matrix to transfer.
	*/
	GMatrix(GMatrix&& other);

	/*!
	Destructor. Clears current matrix.
	*/
	~GMatrix();

	/*!
	Sets matrix with sourse`s matrix values
	\param[in] other Source matrix to copy
	\return GMatrix Current matrix
	*/
	GMatrix& operator=(GMatrix& other);

	/*!
	Sets matrix with sourse`s matrix values
	\param[in] other Source matrix to transfer
	\return GMatrix Current matrix
	*/
	GMatrix& operator=(GMatrix&& other);

	/*!
	Chooses row by index
	\param[in] index Index of choosen row
	\return Row defined by GVector
	*/
	GVector& operator[](const unsigned long index);

	/*!
	Const method. Chooses row by index
	\param[in] index Index of choosen row
	\return Row defined by GVector
	*/
	const GVector& operator[](const unsigned long index) const;

	/*!
	Multiply each item of matrix by (-1)
	\return Matrix after multiply
	*/
	GMatrix& operator-();

	/*!
	Multiply each item of matrix by incoming value
	\param[in] value Value to multiply
	\return Matrix after multiply
	*/
	GMatrix& operator*(const double value);

	/*!
	Multiply matrix with incoming matrix
	\param[in] other Matrix to multiply
	\return Matrix after multiply
	*/
	GMatrix& operator*(const GMatrix& other);

private:
	vector<GVector> matrix;	/*! Geometric matrix ¯\_(ツ)_/¯ */
};