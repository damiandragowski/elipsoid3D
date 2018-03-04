// Vector3D.h: interface for the Vector3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTOR3D_H__3C8439F0_9151_4568_9935_F0A9DADF26EF__INCLUDED_)
#define AFX_VECTOR3D_H__3C8439F0_9151_4568_9935_F0A9DADF26EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <memory.h>
#ifndef MSIZE
#define MSIZE 4
#endif
#include "Matrix3D.h"

class Vector3D  
{
	friend class Matrix3D;
	double vector[MSIZE];
public:
	Vector3D() { ZeroVector(); }
	Vector3D(double x, double y, double z) { vector[0] = x; vector[1] = y; vector[2] = z; vector[3] = 1; }
	void setVector(double x, double y, double z) { vector[0] = x; vector[1] = y; vector[2] = z; vector[3] = 1; }
	Vector3D(Vector3D & rhs) { memcpy(vector, rhs.vector, sizeof(double)*MSIZE); }
	inline Vector3D operator * (double s) { 
		Vector3D temp;
		for ( register int i=0; i < MSIZE; ++i ) temp.vector[i] = vector[i]*s; 
		return temp;
	}
	Vector3D operator * (Matrix3D & rhs);
	inline Vector3D operator + (Vector3D & rhs) { 
		Vector3D temp;
		for ( register int i=0; i < MSIZE; ++i ) temp.vector[i] = vector[i] + rhs.vector[i]; 	
		return temp;
	}
	inline Vector3D operator - (Vector3D & rhs) { 
		Vector3D temp;
		for ( register int i=0; i < MSIZE; ++i ) temp.vector[i] = vector[i] - rhs.vector[i]; 	
		return temp;
	}

	inline Vector3D & operator += (Vector3D & rhs) { for ( register int i=0; i < MSIZE; ++i ) vector[i] += rhs.vector[i]; return *this; } 
	inline Vector3D & operator -= (Vector3D & rhs) { for ( register int i=0; i < MSIZE; ++i ) vector[i] -= rhs.vector[i]; return *this; } 



	inline double & operator [] ( int index ) { return vector[index]; }

	virtual ~Vector3D();
	inline void ZeroVector() { memset(vector, 0, sizeof(double)*MSIZE); }
	
};

#endif // !defined(AFX_VECTOR3D_H__3C8439F0_9151_4568_9935_F0A9DADF26EF__INCLUDED_)
