#pragma once
#include "opengl\OpenGL.h"
class CMyOpenGL :public COpenGL
{
public:
	CMyOpenGL(void);
	~CMyOpenGL(void);
	virtual void PostInit(void);
	virtual void InDraw(void);
	bool OnKey(unsigned char nChar, bool  bDown);
};

