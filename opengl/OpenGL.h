// OpenGL.h: interface for the COpenGL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGL_H__E5995580_D8B1_4938_ADFE_4A915C808FF2__INCLUDED_)
#define AFX_OPENGL_H__E5995580_D8B1_4938_ADFE_4A915C808FF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "gl\glut.h"
#include "Camera068.h"
#include "Quaternion.h"
#include "Vector068.h"
#include "Euler.h"
#include "Control068.h"
#include "Matrix068.h"
class COpenGL  
{
public:
	virtual void InDraw();
	void OnView();
	bool PreTranslateMessage(unsigned int message,unsigned int wParam,unsigned int lParam);
	void OnSize(int w,int h);
	void OnPaint();
	virtual void PostInit();
	bool Init(HWND hWnd);
	COpenGL();
	virtual ~COpenGL();
	virtual bool OnKey(unsigned int nChar,bool bDown);
	virtual bool OnMouse(int message,CPoint pt);
	friend class CglControl;
	HDC m_hDC;
	HGLRC m_hglrc;
	float m_PerspectiveParam[4];
	Control068 *m_pControl;
	HWND m_hWnd;
	Camera068 *m_pCamera;
	float m_fps;
};

#endif // !defined(AFX_OPENGL_H__E5995580_D8B1_4938_ADFE_4A915C808FF2__INCLUDED_)
