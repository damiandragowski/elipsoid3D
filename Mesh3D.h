// Mesh3D.h: interface for the Mesh3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESH3D_H__276B8132_3AF1_42A9_9FDF_9D50E2195F46__INCLUDED_)
#define AFX_MESH3D_H__276B8132_3AF1_42A9_9FDF_9D50E2195F46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Matrix3D.h"
#include <math.h>

class Mesh3D  
{
	Matrix3D Projection;
	Matrix3D Modification;
	Matrix3D stereoLeft;
	Matrix3D stereoRight;
	Vector3D * points;
	int size;
	int d;
	int Z;
public:
	Mesh3D(int _d,int _Z):d(_d), Z(_Z)
	{ 
		points = 0; 
		Modification.LoadIdentity(); 
		Projection.Diagonal(1,1,0,1);  
		Projection[3][2] = (double)1/(double)d;
		stereoRight.LoadIdentity();
		stereoLeft.LoadIdentity();		
		stereoLeft[0][3] = -3;
		stereoRight[0][3] = 3;
	}
	virtual ~Mesh3D();
	void Generate(double , double , int , int );
	void setProjection(int d) { Projection.Diagonal(1,1,0,1); Projection[3][2]=(double)1/(double)d; }
	void Draw(HDC hdc, int cx, int cy);
	inline void RotX(double alfa)
	{
		Matrix3D rot;
		rot[0][0] = 1;
	    rot[1][1] = cos(alfa);
	    rot[2][2] = cos(alfa);
	    rot[3][3] = 1;
	    rot[2][1] = -sin(alfa);
	    rot[1][2] = sin(alfa);
		Modification = rot*Modification;
	}
	inline void RotY(double alfa)
	{
		Matrix3D rot;
		rot[0][0] = cos(alfa);
	    rot[1][1] = 1;
	    rot[2][2] = cos(alfa);
	    rot[3][3] = 1;
	    rot[2][0] = sin(alfa);
	    rot[0][2] = -sin(alfa);
		Modification = rot*Modification;
	}

};

#endif // !defined(AFX_MESH3D_H__276B8132_3AF1_42A9_9FDF_9D50E2195F46__INCLUDED_)
