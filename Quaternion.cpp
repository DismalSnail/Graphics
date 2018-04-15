#include "stdafx.h"
#include "Quaternion.h"


CQuaternion::CQuaternion(void)
{
}


CQuaternion::~CQuaternion(void)
{
}

//************************************
// Method:    operator=
// FullName:  CQuaternion::operator=
// Access:    public
// Returns:   CQuaternion&
// Qualifier:
// Parameter: const CQuaternion & p
//************************************
CQuaternion& CQuaternion::operator=(const CQuaternion& p)
{
	x=p.x;
	y=p.y;
	z=p.z;
	w=p.w;
	return *this;
}

//************************************
// Method:    Set
// FullName:  CQuaternion::Set
// Access:    public
// Returns:   void
// Qualifier:
// Parameter: float x
// Parameter: float y
// Parameter: float z
// Parameter: float w
//************************************
void CQuaternion::Set(float x,float y,float z,float w)
{
	this->x=x;
	this->y=y;
	this->z=z;
	this->w=w;
}
//************************************
// Method:    ToMatrix
// FullName:  CQuaternion::ToMatrix
// Access:    public
// Returns:   CMatrix068
// Qualifier:
//************************************
CMatrix068 CQuaternion::ToMatrix()
{
	CMatrix068 CMA;
	CMA.m00=1-2*y*y-2*z*z;CMA.m01=2*x*y-2*w*z;CMA.m02=2*x*z+2*w*y;CMA.m03=0;
	CMA.m10=2*x*y+2*w*z;CMA.m11=1-2*x*x-2*z*z;CMA.m12=2*y*z+2*w*x;CMA.m13=0;
	CMA.m20=2*x*z-2*w*y;CMA.m21=2*y*z+2*w*x;CMA.m22=1-2*x*x-2*y*y;CMA.m23=0;
	CMA.m30=0;CMA.m31=0;CMA.m32=0;CMA.m33=1;
	return CMA;
}

//************************************
// Method:    ToEuler
// FullName:  CQuaternion::ToEuler
// Access:    public
// Returns:   CEuler
// Qualifier:
//************************************
CEuler CQuaternion::ToEuler()
{
	CEuler CEU;
	float p=asin(2*w*x-2*y*z);
	if (abs(cos(p)-0)<0.0005)
	{
		CEU.h=atan2(2*w*y-2*z*x,1-2*z*z-2*y*y);
		CEU.b=0;
	}
	else
	{
		CEU.h=atan2(2*z*x+2*w*y,1-2*x*x-2*y*y)*180/PI;
		CEU.b=atan2(2*x*y+2*w*z,1-2*z*z-2*x*x)*180/PI;
	}
	CEU.p=p*180/PI;
	return CEU;
}

//************************************
// Method:    SetAngle
// FullName:  SetAngle
// Access:    public
// Returns:   void
// Qualifier:
// Parameter: float angle
// Parameter: CVector068 axis
//************************************
void CQuaternion::SetAngle(float angle,CVector068 axis)
{
	angle=angle*PI/180;
	w=cos(angle/2);
	x=sin(angle/2)*axis.x;
	y=sin(angle/2)*axis.y;
	z=sin(angle/2)*axis.z;
}

//************************************
// Method:    operator+
// FullName:  operator+
// Access:    public
// Returns:   CQuaternion
// Qualifier:
// Parameter: const CQuaternion & p
//************************************
CQuaternion CQuaternion::operator+(const CQuaternion& p)
{
	CQuaternion CQU;
	CQU.x=this->x+p.x;
	CQU.y=this->y+p.y;
	CQU.z=this->z+p.z;
	CQU.w=this->w+p.w;
	return CQU;
}

//************************************
// Method:    operator*
// FullName:  CQuaternion::operator*
// Access:    public
// Returns:   CQuaternion
// Qualifier:
// Parameter: float data
//************************************
CQuaternion CQuaternion::operator*(float data)
{
	CQuaternion CQU;
	CQU.x=this->x*data;
	CQU.y=this->y*data;
	CQU.z=this->z*data;
	CQU.w=this->x*data;
	return CQU;
}

//************************************
// Method:    operator*
// FullName:  CQuaternion::operator*
// Access:    public
// Returns:   CQuaternion
// Qualifier:
// Parameter: const CQuaternion & p
//************************************
CQuaternion CQuaternion::operator*(const CQuaternion&p)
{
	CQuaternion CQU;
	CQU.w=this->w*p.w - this->x*p.x - this->y*p.y - this->z*p.z;
	CQU.x=this->w*p.x + this->x*p.w + this->z*p.y - this->y*p.z;
	CQU.y=this->w*p.y + this->y*p.w + this->x*p.z - this->z*p.x;
	CQU.z=this->w*p.z + this->z*p.w + this->y*p.x - this->x*p.y;
	return CQU;
}

//************************************
// Method:    dotMul
// FullName:  CQuaternion::dotMul
// Access:    public
// Returns:   float
// Qualifier:
// Parameter: const CQuaternion & p
//************************************
float CQuaternion::dotMul(const CQuaternion&p)
{
	return this->w*p.w+this->x*p.x+this->y*p.y+this->z*p.z;
}

//************************************
// Method:    len
// FullName:  CQuaternion::len
// Access:    public
// Returns:   float
// Qualifier:
//************************************
float CQuaternion::len()
{
	return sqrt(z*z+y*y+x*x+w*w);
}

//************************************
// Method:    Normalize
// FullName:  CQuaternion::Normalize
// Access:    public 
// Returns:   CQuaternion
// Qualifier:
//************************************
CQuaternion CQuaternion::Normalize()
{
	CQuaternion CQU;
	float len=sqrt(z*z+y*y+x*x+w*w);
	CQU.x=x/len;
	CQU.y=y/len;
	CQU.z=z/len;
	CQU.w=w/len;
	return CQU;
}


//************************************
// Method:    Inverse
// FullName:  CQuaternion::Inverse
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void CQuaternion::Inverse()
{
	float len2=z*z+y*y+x*x+w*w;
	z=-z;
	x=-x;
	y=-y;
	w=w/len2;
	z=z/len2;
	x=x/len2;
	y=y/len2;
}

//************************************
// Method:    GetInverse
// FullName:  CQuaternion::GetInverse
// Access:    public
// Returns:   CQuaternion
// Qualifier:
//************************************
CQuaternion CQuaternion::GetInverse()
{
	float len2=z*z+y*y+x*x+w*w;
	CQuaternion CQU;

	CQU.x=-x/len2;
	CQU.y=-y/len2;
	CQU.z=-z/len2;
	CQU.w=w/len2;

	return CQU;
}

//************************************
// Method:    Div
// FullName:  Div
// Access:    public
// Returns:   CQuaternion
// Qualifier:
// Parameter: const CQuaternion & b
//************************************
CQuaternion CQuaternion::Div(const CQuaternion&b)
{
	float len2=z*z+y*y+x*x+w*w;
	CQuaternion CQU;
	CQU.x=-x/len2;
	CQU.y=-y/len2;
	CQU.z=-z/len2;
	CQU.w=w/len2;

	CQU=CQU*b;
	return CQU;
}

//************************************
// Method:    GetAngle
// FullName:  CQuaternion::GetAngle
// Access:    public
// Returns:   void
// Qualifier:
// Parameter: float & angle
// Parameter: CVector068 & axis
//************************************
void CQuaternion::GetAngle(float& angle,CVector068& axis)
{
	CQuaternion CQU;
	float len=sqrt(z*z+y*y+x*x+w*w);
	CQU.x=x/len;
	CQU.y=y/len;
	CQU.z=z/len;
	CQU.w=w/len;

	angle=acos(CQU.w);
	axis.x=CQU.x/sin(angle);
	axis.y=CQU.y/sin(angle);
	axis.z=CQU.z/sin(angle);

	angle=2*angle*180/PI;
}


//************************************
// Method:    Slerp
// FullName:  CQuaternion::Slerp
// Access:    public 
// Returns:   CQuaternion
// Qualifier:
// Parameter: const CQuaternion & Vend
// Parameter: float t
//************************************
CQuaternion CQuaternion::Slerp(CQuaternion& Vend,float t)
{
	CQuaternion CQU;
	CQuaternion CQU1;
	Vend=Vend.Normalize();
	CQuaternion T;
	CQU.w=w;CQU.x=x;CQU.y=y;CQU.z=z;
	CQU=CQU.Normalize();
	CQU1=CQU.GetInverse();
	T=CQU1*Vend;
	CQU1=T.power(t);
	CQU=CQU*CQU1;
	return CQU;

}

//************************************
// Method:    power
// FullName:  CQuaternion::power
// Access:    public 
// Returns:   CQuaternion
// Qualifier:
// Parameter: const CQuaternion & b
//************************************
CQuaternion CQuaternion::power(float n)
{
	float seta;
	seta=acos(w);
	CQuaternion CQU;
	CQU.w=cos(n*seta);
	CQU.x=x/sin(seta)*sin(n*seta);
	CQU.y=y/sin(seta)*sin(n*seta);
	CQU.z=z/sin(seta)*sin(n*seta);
	return CQU;
}

//************************************
// Method:    Slerp
// FullName:  CQuaternion::Slerp
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const CQuaternion & Vend
// Parameter: int n
// Parameter: float * t
// Parameter: CQuaternion * Result
//************************************
void CQuaternion::Slerp( CQuaternion& Vend,int n,float *t,CQuaternion *Result)
{
	//CQuaternion CQU;
	//CQU.w=w;CQU.x=x;CQU.y=y;CQU.z=z;
	for (int i=0;i<n;i++)
	{
		Result[i]=this->Slerp(Vend,t[i]);
	}
}