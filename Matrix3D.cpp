// Matrix3D.cpp: implementation of the Matrix3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Matrix3D.h"
#include "Vector3D.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Vector3D Matrix3D::operator * (Vector3D & rhs)
{
	Vector3D temp;
	temp.vector[0] = matrix[0][0] * rhs.vector[0] + matrix[0][1] * rhs.vector[1] + matrix[0][2] * rhs.vector[2] + matrix[0][3] * rhs.vector[3];
	temp.vector[1] = matrix[1][0] * rhs.vector[0] + matrix[1][1] * rhs.vector[1] + matrix[1][2] * rhs.vector[2] + matrix[1][3] * rhs.vector[3];
	temp.vector[2] = matrix[2][0] * rhs.vector[0] + matrix[2][1] * rhs.vector[1] + matrix[2][2] * rhs.vector[2] + matrix[2][3] * rhs.vector[3];
	temp.vector[3] = matrix[3][0] * rhs.vector[0] + matrix[3][1] * rhs.vector[1] + matrix[3][2] * rhs.vector[2] + matrix[3][3] * rhs.vector[3];
	return temp;
}

Matrix3D::~Matrix3D()
{

}
