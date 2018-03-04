// Matrix3D.h: interface for the Matrix3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIX3D_H__0224DBE1_CDC0_4240_9456_8F874BC5430A__INCLUDED_)
#define AFX_MATRIX3D_H__0224DBE1_CDC0_4240_9456_8F874BC5430A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <memory.h>
#define MSIZE 4
#include "Vector3D.h"

class Matrix3D  
{
	friend class Vector3D;
	double matrix[MSIZE][MSIZE];
public:
	Matrix3D() { ZeroMatrix(); }
	virtual ~Matrix3D();
	inline void ZeroMatrix() { for ( register int i = 0; i < MSIZE; ++i ) memset(matrix[i], 0, sizeof(double)*MSIZE); }
	inline void LoadIdentity() { ZeroMatrix(); matrix[0][0]=1; matrix[1][1]=1; matrix[2][2]=1; matrix[3][3]=1; }
	Matrix3D(Matrix3D & rhs) { for ( register int i = 0; i < MSIZE; ++i ) memcpy(matrix[i], rhs.matrix[i], sizeof(double) * MSIZE); }

	Vector3D operator * (Vector3D & rhs);
	inline Matrix3D operator * (Matrix3D & rhs) {
		Matrix3D temp;
		for(register int i=0;i<MSIZE;i++)
			for(register int j=0;j<MSIZE;j++)
				for(register int k=0;k<MSIZE;k++)
					temp.matrix[i][j] += matrix[i][k] * rhs.matrix[k][j];
		return temp;
	}
	inline Matrix3D operator + (Matrix3D & rhs) {
		Matrix3D temp;
		for(register int i=0;i<MSIZE;i++)
			for(register int j=0;j<MSIZE;j++)
				temp.matrix[i][j] = matrix[i][j] + rhs.matrix[i][j];
		return temp;
	}
	inline Matrix3D operator - (Matrix3D & rhs) {
		Matrix3D temp;
		for(register int i=0;i<MSIZE;i++)
			for(register int j=0;j<MSIZE;j++)
				temp.matrix[i][j] = matrix[i][j] - rhs.matrix[i][j];
		return temp;
	}

	inline Matrix3D & operator += (Matrix3D & rhs) {
		for(register int i=0;i<MSIZE;i++)
			for(register int j=0;j<MSIZE;j++)
				matrix[i][j] += rhs.matrix[i][j];
		return *this;
	}

	inline void Diagonal(double x, double y, double z, double w) {
		ZeroMatrix();
		matrix[0][0] = y;
		matrix[1][1] = y;
		matrix[2][2] = z;
		matrix[3][3] = w;
	}

	inline Matrix3D & operator -= (Matrix3D & rhs) {
		for(register int i=0;i<MSIZE;i++)
			for(register int j=0;j<MSIZE;j++)
				matrix[i][j] -= rhs.matrix[i][j];
		return *this;
	}
	inline double * operator[](int index) { return (matrix[index]); }
};

#endif // !defined(AFX_MATRIX3D_H__0224DBE1_CDC0_4240_9456_8F874BC5430A__INCLUDED_)
