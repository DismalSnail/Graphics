#include "stdafx.h"



CEuler::CEuler(void)
{
}


CEuler::~CEuler(void)
{
}

//************************************
// Method:    Set
// FullName:  CEuler::Set
// Access:    public
// Returns:   void
// Qualifier:
// Parameter: float h
// Parameter: float p
// Parameter: float b
//************************************
void CEuler::Set(float h,float p,float b)
{
	this->h=h;
	this->p=p;
	this->b=b;
}


//************************************
// Method:    ToVector068
// FullName:  CEuler::ToVector068
// Access:    public
// Returns:   CVector068
// Qualifier:
// Parameter: CVector068 * updir
//************************************
CVector068 CEuler::ToVector068(CVector068 *updir=0)
{
	CMatrix068 rot1;
	CVector068 init;
	init.Set(0,1,0);
	float setax=p*PI/180;
	float setay=h*PI/180;
	float setaz=b*PI/180;
	if (updir != 0){
		rot1=rot1.SetRotate(setaz,2);
		init=rot1.vecMul(init);
		rot1=rot1.SetRotate(setax,0);
		init=rot1.vecMul(init);
		rot1=rot1.SetRotate(setay,1);
		init=rot1.vecMul(init);
		*updir=init;

		init.Set(0,0,-1);
		rot1=rot1.SetRotate(setaz,2);
		init=rot1.vecMul(init);
		rot1=rot1.SetRotate(setax,0);
		init=rot1.vecMul(init);
		rot1=rot1.SetRotate(setay,1);
		init=rot1.vecMul(init);
		return init;
	}else{
		init.Set(0,0,-1);
		rot1=rot1.SetRotate(setaz,2);
		init=rot1.vecMul(init);
		rot1=rot1.SetRotate(setax,0);
		init=rot1.vecMul(init);
		rot1=rot1.SetRotate(setay,1);
		init=rot1.vecMul(init);
		return init;
	}
}

//************************************
// Method:    ToMatrix068
// FullName:  CEuler::ToMatrix068
// Access:    public
// Returns:   CMatrix068
// Qualifier:
//************************************
CMatrix068 CEuler::ToMatrix068()
{
	CMatrix068 rot1;
	CMatrix068 rot2;
	float setax=p*PI/180;
	float setay=h*PI/180;
	float setaz=b*PI/180;
	rot2=rot1.SetRotate(setay,1);
	rot1=rot2*rot1.SetRotate(setax,0);
	rot1=rot1*rot2.SetRotate(setaz,2);
	return rot1;
}

//************************************
// Method:    ToQuaternion
// FullName:  CEuler::ToQuaternion
// Access:    public
// Returns:   CQuaternion
// Qualifier:
//************************************
CQuaternion CEuler::ToQuaternion()
{
	CQuaternion CQU;
	float h=this->h*PI/180;
	float p=this->p*PI/180;
	float b=this->b*PI/180;

	 CQU.w=cos(h/2)*cos(p/2)*cos(b/2)+sin(h/2)*sin(p/2)*sin(b/2);
	 CQU.x=cos(h/2)*sin(p/2)*cos(b/2)+sin(h/2)*cos(p/2)*sin(b/2);
	 CQU.y=sin(h/2)*cos(p/2)*cos(b/2)-cos(h/2)*sin(p/2)*sin(b/2);
	 CQU.z=cos(h/2)*cos(p/2)*sin(b/2)-sin(h/2)*sin(p/2)*cos(b/2);

	 return CQU;
}

//************************************
// Method:    Normal
// FullName:  CEuler::Normal
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void CEuler::Normal()
{
	while (h > 180)
	{
		h-=360;
	}
	while (h <-180)
	{
		h+=360;
	}

	while (b > 180)
	{
		b-=360;
	}
	while (b <-180)
	{
		b+=360;
	}

	while (p > 90)
	{
		p-=180;
	}
	while (p <-90)
	{
		p+=180;
	}
	if (p==90 || p==-90)
	{
		b=0;
	}
}