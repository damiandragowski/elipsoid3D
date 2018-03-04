// Mesh3D.cpp: implementation of the Mesh3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mesh3D.h"
#include "Vector3D.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define DTOR 0.01745329252

void Mesh3D::Generate(double r0=100.0, double r1=20.0, int du=20, int dv=20)
{
				int u,v;
				double theta,phi;
				double x,y,z;

				size = (360/dv)*(360/du)*4;
				points = new Vector3D[size];

				int i=0;
				for (u=0;u<360;u+=du) {
				  for (v=0;v<360;v+=dv) {

					 theta = (u) * DTOR;
					 phi   = (v) * DTOR;
					 x = cos(theta) * ( r0 + r1 * cos(phi) );
					 y = sin(theta) * ( r0 + r1 * cos(phi) );
					 z = r1 * sin(phi);
					 points[i++].setVector(x,y,z);

					 theta = (u+du) * DTOR;
					 phi   = (v) * DTOR;
					 x = cos(theta) * ( r0 + r1 * cos(phi) );
					 y = sin(theta) * ( r0 + r1 * cos(phi) );
					 z = r1 * sin(phi);
					 points[i++].setVector(x,y,z);

					 theta = (u+du) * DTOR;
					 phi   = (v+dv) * DTOR;
					 x = cos(theta) * ( r0 + r1 * cos(phi) );
					 y = sin(theta) * ( r0 + r1 * cos(phi) );
					 z = r1 * sin(phi);
					 points[i++].setVector(x,y,z);

					 theta = (u) * DTOR;
					 phi   = (v+dv) * DTOR;
					 x = cos(theta) * ( r0 + r1 * cos(phi) );
					 y = sin(theta) * ( r0 + r1 * cos(phi) );
					 z = r1 * sin(phi);
					 points[i++].setVector(x,y,z);

				  }
				}

}

Mesh3D::~Mesh3D()
{
	if ( points ) delete [] points;
}

void Mesh3D::Draw(HDC hdc, int cx, int cy)
{
	 static int i;
	 static POINT pt[4];
	 static Vector3D temp;
	 static bool skip1, skip2, skip3, skip4;

	 for ( i=0; i < size;  ) {
		 {
		 temp = points[i]*Modification;
		 skip1 = false;
		 if ( temp[2] >= Z )
			skip1 = true;

		 temp = (stereoLeft*Projection)*temp;
		 ++i;

		 pt[0].x = (long)(temp[0]*temp[3]);
		 pt[0].y = (long)(temp[1]*temp[3]);

		 
		 temp = points[i]*Modification;
		 skip2 = false;
		 if ( temp[2] >= Z )
			skip2 = true;

		 temp = (stereoLeft*Projection)*temp;
		 ++i;

		 pt[1].x = (long)(temp[0]*temp[3]);
		 pt[1].y = (long)(temp[1]*temp[3]);

		 

		 temp = points[i]*Modification;
		 skip3 = false;
		 if ( temp[2] >= Z )
			skip3 = true;

		 temp = (stereoLeft*Projection)*temp;
		 ++i;

		 pt[2].x = (long)(temp[0]*temp[3]);
		 pt[2].y = (long)(temp[1]*temp[3]);



		 temp = points[i]*Modification;
		 skip4 = false;
		 if ( temp[2] >= Z )
			skip4 = true;

		 temp = (stereoLeft*Projection)*temp;
		 ++i;

		 pt[3].x = (long)(temp[0]*temp[3]);
		 pt[3].y = (long)(temp[1]*temp[3]);


		 POINT p;

		 if ( !skip1 && !skip2 ) {
  			MoveToEx(hdc, pt[0].x+cx, pt[0].y+cy, &p);
			LineTo(hdc, pt[1].x+cx, pt[1].y+cy);  			
		 } 
		 if ( !skip2 && !skip3 ) {
  			MoveToEx(hdc, pt[1].x+cx, pt[1].y+cy, &p);
			LineTo(hdc, pt[2].x+cx, pt[2].y+cy);  			
		 } 
		 if ( !skip3 && !skip4 ) {
  			MoveToEx(hdc, pt[2].x+cx, pt[2].y+cy, &p);
			LineTo(hdc, pt[3].x+cx, pt[3].y+cy);  			
		 } 
		 if ( !skip1 && !skip4 ) {
  			MoveToEx(hdc, pt[3].x+cx, pt[3].y+cy, &p);
			LineTo(hdc, pt[0].x+cx, pt[0].y+cy);  			
		 }


		 }
		int saveDC = SaveDC(hdc);
		HPEN pen = CreatePen(PS_SOLID, 1, RGB(255,0,0));
		SelectObject(hdc, pen);
		SetROP2(hdc, R2_MERGEPEN);
		 // right
		i-=4;
		 {
		 temp = points[i]*Modification;
		 skip1 = false;
		 if ( temp[2] >= Z )
			skip1 = true;

		 temp = (Projection*stereoRight)*temp;
		 ++i;

		 pt[0].x = (long)(temp[0]*temp[3]);
		 pt[0].y = (long)(temp[1]*temp[3]);

		 
		 temp = points[i]*Modification;
		 skip2 = false;
		 if ( temp[2] >= Z )
			skip2 = true;

		 temp = (Projection*stereoRight)*temp;
		 ++i;

		 pt[1].x = (long)(temp[0]*temp[3]);
		 pt[1].y = (long)(temp[1]*temp[3]);

		 

		 temp = points[i]*Modification;
		 skip3 = false;
		 if ( temp[2] >= Z )
			skip3 = true;

		 temp = (Projection*stereoRight)*temp;
		 ++i;

		 pt[2].x = (long)(temp[0]*temp[3]);
		 pt[2].y = (long)(temp[1]*temp[3]);



		 temp = points[i]*Modification;
		 skip4 = false;
		 if ( temp[2] >= Z )
			skip4 = true;

		 temp = (Projection*stereoRight)*temp;
		 ++i;

		 pt[3].x = (long)(temp[0]*temp[3]);
		 pt[3].y = (long)(temp[1]*temp[3]);


		 POINT p;

		 if ( !skip1 && !skip2 ) {
  			MoveToEx(hdc, pt[0].x+cx, pt[0].y+cy, &p);
			LineTo(hdc, pt[1].x+cx, pt[1].y+cy);  			
		 } 
		 if ( !skip2 && !skip3 ) {
  			MoveToEx(hdc, pt[1].x+cx, pt[1].y+cy, &p);
			LineTo(hdc, pt[2].x+cx, pt[2].y+cy);  			
		 } 
		 if ( !skip3 && !skip4 ) {
  			MoveToEx(hdc, pt[2].x+cx, pt[2].y+cy, &p);
			LineTo(hdc, pt[3].x+cx, pt[3].y+cy);  			
		 } 
		 if ( !skip1 && !skip4 ) {
  			MoveToEx(hdc, pt[3].x+cx, pt[3].y+cy, &p);
			LineTo(hdc, pt[0].x+cx, pt[0].y+cy);  			
		 }

		 }
		DeleteObject(pen);
		RestoreDC(hdc, saveDC);

	 }
}