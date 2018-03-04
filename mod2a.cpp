// mod2a.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include <math.h>
#include "Matrix3D.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

// dane GDI i Okna i startu
static HDC dc;
static HBITMAP bit;
bool ready=false;
HWND hWndMain;
bool wait=false;

void  Normalize(Vector3D & t)
{
	double sq=0.0;
	sq += t[0]*t[0];
	sq += t[1]*t[1];
	sq += t[2]*t[2];
	t[0] /= sqrt(sq);
	t[1] /= sqrt(sq);
	t[2] /= sqrt(sq);
}

void DrawRect(HDC hdc, int x, int y, int du, COLORREF color)
{
	int saveDC = SaveDC(hdc);

	HBRUSH brush = CreateSolidBrush(color);
	HPEN pen = CreatePen(PS_SOLID, 1, color);
	SelectObject(hdc, brush);
	SelectObject(hdc, pen);

	Rectangle(hdc, x, y, x+du, y+du);

	DeleteObject(pen);
	DeleteObject(brush);

	RestoreDC(hdc, saveDC);
}


// dane obiektu
Matrix3D Modification;
double alfa = 20;
double a2= 10*10;
double b2= 13*13;
double c2= 14*14;
int du=16;


// funkcje obrotu 

inline void RotZ(double alfa)
{
	Matrix3D rot;
	rot[0][0] = cos(alfa);
	rot[1][1] = cos(alfa);
	rot[2][2] = 1;
	rot[3][3] = 1;
	rot[1][0] = sin(alfa);
	rot[0][1] = -sin(alfa);
	Modification = Modification*rot;
}
inline void RotX(double alfa)
{
	Matrix3D rot;
	rot[0][0] = 1;
	rot[1][1] = cos(alfa);
	rot[2][2] = cos(alfa);
	rot[3][3] = 1;
	rot[2][1] = -sin(alfa);
	rot[1][2] = sin(alfa);
	Modification = Modification*rot;
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
	Modification = Modification*rot;
}
inline void TransX(int pos)
{
	Matrix3D rot;
	rot[0][0] = 1;
	rot[1][1] = 1;
	rot[2][2] = 1;
	rot[3][3] = 1;
	rot[3][0] = pos;
	Modification = Modification*rot;
}
inline void TransY(int pos)
{
	Matrix3D rot;
	rot[0][0] = 1;
	rot[1][1] = 1;
	rot[2][2] = 1;
	rot[3][3] = 1;
	rot[3][1] = pos;
	Modification = Modification*rot;
}

inline void TransZ(int pos)
{
	Matrix3D rot;
	rot[0][0] = 1;
	rot[1][1] = 1;
	rot[2][2] = 1;
	rot[3][3] = 1;
	rot[3][2] = pos;
	Modification = Modification*rot;
}

inline void ScaleX(double scale)
{
	Matrix3D rot;
	rot[0][0] = scale;
	rot[1][1] = 1;
	rot[2][2] = 1;
	rot[3][3] = 1;
	Modification = Modification*rot;
}

inline void ScaleY(double scale)
{
	Matrix3D rot;
	rot[0][0] = 1;
	rot[1][1] = scale;
	rot[2][2] = 1;
	rot[3][3] = 1;
	Modification = Modification*rot;
}
inline void ScaleZ(double scale)
{
	Matrix3D rot;
	rot[0][0] = 1;
	rot[1][1] = 1;
	rot[2][2] = scale;
	rot[3][3] = 1;
	Modification = Modification*rot;
}



int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MOD2A, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_MOD2A);


	BOOL done = FALSE;

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			if ( ready ) {

				static RECT rt;
				GetClientRect(hWndMain, &rt);

				if ( !wait ) {

					// renderowanie elipsoidy 
					SetWindowText(hWndMain, "Wait for rendering..");
					static double a = 1/(a2*a2);
					static double b = 1/(b2*b2);
					static double c = 1/(c2*c2);
					static double z;
					static double A,B,C;
					static double delta;
					static double x2, y2;

					A = a*Modification[2][0]*Modification[2][0]+b*Modification[2][1]*Modification[2][1]
						+c*Modification[2][2]*Modification[2][2]
						-Modification[2][3]*Modification[2][3];

					for ( int i=-rt.right>>1; i < rt.right>>1; i+=du )
						for (int j=-rt.bottom>>1; j < rt.bottom>>1; j+=du)
						{
							x2=i*i;
							y2=j*j;
							B =	2*(a*(i*Modification[0][0]*Modification[2][3] +j*Modification[1][0]*Modification[2][0]+Modification[2][0]*Modification[3][0])+b*(i*Modification[0][1]*Modification[2][1]
								+j*Modification[1][1]*Modification[2][1] +Modification[2][1]*Modification[3][1])+c*(i*Modification[0][2]*Modification[2][2]+j*Modification[1][2]*Modification[2][2]
								+Modification[2][2]*Modification[3][2])	-i*Modification[0][3]*Modification[2][3]-j*Modification[1][3]*Modification[3][3]-Modification[2][3]*Modification[3][3]);
							C =	a*x2*Modification[0][0]*Modification[0][0]+a*y2*Modification[1][0]*Modification[1][0]+a*Modification[3][0]*Modification[3][0]
								+2*a*(i*j*Modification[0][0]*Modification[1][0]+i*Modification[0][0]*Modification[3][0]+j*Modification[1][0]*Modification[3][0])
								+b*x2*Modification[0][1]*Modification[0][1]+b*y2*Modification[1][1]*Modification[1][1]+b*Modification[3][1]*Modification[3][1]
								+2*b*(i*j*Modification[0][1]*Modification[1][1]+i*Modification[0][1]*Modification[3][1]+j*Modification[1][1]*Modification[3][1])
								+c*x2*Modification[0][2]*Modification[0][2]+c*y2*Modification[1][2]*Modification[1][2]+c*Modification[3][2]*Modification[3][2]
								+2*c*(i*j*Modification[0][2]*Modification[1][2]+i*Modification[0][2]*Modification[3][2]+j*Modification[1][2]*Modification[3][2])
								-x2*Modification[0][3]*Modification[0][3]-y2*Modification[1][3]*Modification[1][3]-Modification[3][3]*Modification[3][3]
								-2*i*j*Modification[0][3]*Modification[1][3]-2*i*Modification[0][3]*Modification[3][3]-2*j*Modification[1][3]*Modification[3][3];

							delta=B*B-4*A*C;
							if(delta<0)
							{
								z = 0.0;
							}
							z = (-B-sqrt(delta))/(2*A);


							int rgb=0;
							if ( z < 0  ) 
								rgb=(int)z*255;

							if ( du != 1 ) {
								DrawRect(dc, i+(rt.right>>1), j+(rt.bottom>>1), du, RGB(rgb, 0, 0));
							} else {
								SetPixelV(dc, i+(rt.right>>1), j+(rt.bottom>>1), RGB(rgb, 0, 0));
							}
						}
						InvalidateRect(hWndMain, 0, false);
						if ( du != 1 ) {
							du >>= 1;
						} else {
							wait=true;
						}
					SetWindowText(hWndMain, "Ready go operate");
				}
		}

	}


	}

	// Main message loop:
	/*
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
*/
	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_MOD2A);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_MOD2A;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWndMain = hWnd = CreateWindow(szWindowClass, szTitle, WS_POPUP|WS_CAPTION,
      0, 0, 512, 512, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	static bool active=false;
	static POINT old,old1;
	static bool bactive=false;
	static bool zactive=false;
	static bool factive=false;
	static bool sactive=false;


	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{

		case WM_SIZE:
			{
				int cx = LOWORD(lParam);
				int cy = HIWORD(lParam);

				DeleteObject(dc);
				DeleteObject(bit);
				hdc = GetDC(hWnd);
				dc = CreateCompatibleDC(hdc);
				bit = CreateCompatibleBitmap(hdc, cx, cy);
				SelectObject(dc, bit);
				HBRUSH brush = CreateSolidBrush(RGB(0,0,0));
				HPEN pen = CreatePen(PS_SOLID, 1, RGB(255,0,0));
				SelectObject(dc, brush);
				SelectObject(dc, pen);
				ReleaseDC(hWnd, hdc);
				ready = true;
			}
			break;

		case WM_CREATE:	
			{
			Modification.LoadIdentity();

			hdc = GetDC(hWnd);
			dc = CreateCompatibleDC(hdc);
			bit = CreateCompatibleBitmap(hdc, 10, 10);
			SelectObject(hdc, bit);
			ReleaseDC(hWnd, hdc);

			}
			break;
		case WM_KEYDOWN:
			if ( wParam == 'z' || wParam == 'Z' ) 
				zactive = true;
			if ( wParam == 's' || wParam == 'S' ) 
				sactive = true;
			if ( wParam == 'f' || wParam == 'F' ) 
				factive = true;

			break;
		case WM_KEYUP:
			if ( wParam == 'z' || wParam == 'Z' ) 
				zactive = false;
			if ( wParam == 's' || wParam == 'S' ) 
				sactive = false;
			if ( wParam == 'f' || wParam == 'F' ) 
				factive = false;
			break;

		case WM_LBUTTONDOWN:
			active = true;
			old.x = LOWORD(lParam);
			old.y = HIWORD(lParam);
			break;
		case WM_LBUTTONUP:
			active = false;
			break;

		case WM_RBUTTONDOWN:
			bactive = true;
			old1.x = LOWORD(lParam);
			old1.y = HIWORD(lParam);
			break;
		case WM_RBUTTONUP:
			bactive = false;
			break;

		case WM_MOUSEMOVE:
			if ( active ) {
				if ( sactive ) {
					if ( zactive ) { 
						if ( old.y-HIWORD(lParam) ) {
							if ( old.y-HIWORD(lParam) > 0 )
								ScaleZ(1.05);
							else
								ScaleZ(0.95);
						} 
					} else {
						if ( old.y-HIWORD(lParam) ) {
							if ( old.y-HIWORD(lParam) > 0 )
								ScaleY(1.05);
							else
								ScaleY(0.95);
						}
						if ( old.x-LOWORD(lParam) ) {
							if ( old.x-LOWORD(lParam) > 0 )
								ScaleX(1.05);
							else
								ScaleX(0.95);
						}
					}

				} else {
					if ( zactive ) { 
						if ( old.y-HIWORD(lParam) ) {
							double beta = (old.y-HIWORD(lParam))*0.01;
							RotZ(beta);
						} 
					} else {
						if ( old.y-HIWORD(lParam) ) {
							double beta = (old.y-HIWORD(lParam))*0.01;
							RotX(beta);
						} 
						if ( old.x-LOWORD(lParam) ) {
     						double alfa = (LOWORD(lParam)-old.x)*0.01;
							RotY(alfa);
						}
					}
				}
				old.y = HIWORD(lParam);
				old.x = LOWORD(lParam);
				du=16;
				wait=false;
				InvalidateRect(hWnd, 0, false);
			}
			if ( bactive ) {
				if ( zactive ) {
					if ( old1.x-LOWORD(lParam) ) {
					   TransZ(LOWORD(lParam)-old1.x);
					}
				} else {
					if ( old1.x-LOWORD(lParam) ) {
					   TransX(LOWORD(lParam)-old1.x);
					}

					if ( old1.y-HIWORD(lParam) ) {
					   TransY(HIWORD(lParam)-old1.y);				
					}
				}
				old1.y = HIWORD(lParam);
				old1.x = LOWORD(lParam);
				du=16;
				wait=false;
				InvalidateRect(hWnd, 0, false);
			}
			break;

		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
	 	case WM_PAINT:
			{

			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			BitBlt(hdc, 0, 0, rt.right, rt.bottom, dc, 0, 0, SRCCOPY);

			EndPaint(hWnd, &ps);
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
