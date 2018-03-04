// Vector3D.cpp: implementation of the Vector3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Vector3D.h"
#include "Matrix3D.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Vector3D Vector3D::operator * ( Matrix3D & rhs )
{
	Vector3D temp;
	temp.vector[0] = rhs.matrix[0][0] * vector[0] + rhs.matrix[1][0] * vector[1] + rhs.matrix[2][0] * vector[2] + rhs.matrix[3][0] * vector[3];
	temp.vector[1] = rhs.matrix[0][1] * vector[0] + rhs.matrix[1][1] * vector[1] + rhs.matrix[2][1] * vector[2] + rhs.matrix[3][1] * vector[3];
	temp.vector[2] = rhs.matrix[0][2] * vector[0] + rhs.matrix[1][2] * vector[1] + rhs.matrix[2][2] * vector[2] + rhs.matrix[3][2] * vector[3];
	temp.vector[3] = rhs.matrix[0][3] * vector[0] + rhs.matrix[1][3] * vector[1] + rhs.matrix[2][3] * vector[2] + rhs.matrix[3][3] * vector[3];
	return temp;
}


Vector3D::~Vector3D()
{

}
