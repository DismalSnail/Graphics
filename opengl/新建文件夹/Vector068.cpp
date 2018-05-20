#include "stdafx.h"

CVector068::CVector068(float fx,float fy,float fz)
{
	x=fx;
	y=fy;
	z=fz;
}

CVector068::CVector068(void)
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}


CVector068::~CVector068(void)
{
}


void CVector068::Set(float fx,float fy,float fz)
{
	x = fx;
	y = fy;
	z = fz;
}
float CVector068::dotMul(CVector068 &n)
{
	return this->x*n.x + this->y*n.y +this->z*n.z;
}

CVector068 CVector068::crossMul(CVector068 &n)
{
	CVector068 CVector068_T;
	CVector068_T.x = this->y*n.z - n.y*this->z;
	CVector068_T.y = n.x*this->z - this->x*n.z;
	CVector068_T.z = this->x*n.y - n.x*this->y;
	return CVector068_T;
}

void CVector068::Normalize()
{
	float x1=this->x;
	float y1=this->y;
	float z1=this->z;
	this->x= this->x*(1/sqrt(x1*x1+y1*y1+z1*z1));
	this->y= this->y*(1/sqrt(x1*x1+y1*y1+z1*z1));
	this->z= this->z*(1/sqrt(x1*x1+y1*y1+z1*z1));
}

float CVector068::len()
{
	float x1=this->x;
	float y1=this->y;
	float z1=this->z;
	return sqrt(x1*x1+y1*y1+z1*z1);
}


CVector068 CVector068::project(CVector068 &n)
{
	CVector068 CVector068_T;
	float length;
	length = ((this->x*n.x + this->y*n.y +this->z*n.z)/n.len());
	n.Normalize();
	CVector068_T = n*length;
	return CVector068_T;
}


CVector068 CVector068::operator+(CVector068 &p)
{
	CVector068 CVector068_T;
	CVector068_T.x = x + p.x;
	CVector068_T.y = y + p.y;
	CVector068_T.z = z + p.z;

	return CVector068_T;
}

CVector068 CVector068::operator-(CVector068 &p)
{
	CVector068 CVector068_T;
	CVector068_T.x = x - p.x;
	CVector068_T.y = y - p.y;
	CVector068_T.z = z - p.z;

	return CVector068_T;
}

void CVector068::operator=(CVector068 &p)
{
	x = p.x;
	y = p.y;
	z = p.z;
}

bool CVector068::operator==(CVector068 &p)
{
	if (x != p.x)
	{
		return false;
	} 
	if (y != p.y)
	{
		return false;
	}
	if(z != p.z)
	{
		return false;
	}
	return true;
}


bool CVector068::operator!=(CVector068 &p)
{

	if (x != p.x)
	{
		return true;
	} 
	if (y != p.y)
	{
		return true;
	}
	if(z != p.z)
	{
		return true;
	}
	return false;
}

CVector068 operator*(CVector068 &p,float n)
{
	CVector068 CVector068_T;
	CVector068_T.x = p.x * n;
	CVector068_T.y = p.y * n;
	CVector068_T.z = p.z * n;
	return CVector068_T;
}

CVector068 operator*(float n,CVector068 &p)
{
	CVector068 CVector068_T;
	CVector068_T.x = p.x * n;
	CVector068_T.y = p.y * n;
	CVector068_T.z = p.z * n;
	return CVector068_T;
}

//************************************
// Method:    ToEuler
// FullName:  CVector068::ToEuler
// Access:    public 
// Returns:   CEuler
// Qualifier:
//************************************
CEuler CVector068::ToEuler()
{
	CEuler ans;
	//向量只能得到物体的模型运动方向，而滚转方向则未知
	ans.b = 0;
	CVector068 h, nz;
	//求heading角
	h.x = x;
	h.y = 0;
	h.z = z;
	if (h.x == 0 && h.z == 0)
	{
		ans.h = 0;
		if (this->y > 0)
		{
			ans.p = 90;
		}
		else if (this->y < 0)
		{
			ans.p = -90;
		}
		else
		{
			ans.p = 0;
		}
		return ans;
	}
	nz.z=-1;
	float radianH = acosf(nz.dotMul(h) / (h.len() * nz.len()));
	float angleH = radianH * 180 / acosf(-1);
	if (x > 0)
	{
		ans.h = -1 * angleH;
	}
	else
	{
		ans.h = angleH;
	}
	//求pitch角
	float radianP = fabs(acosf(this->dotMul(h) / (this->len() * h.len())));
	float angleP = radianP * 180 / acosf(-1);
	if (x > 0)
	{
		if (y > 0)
		{
			ans.p = angleP;
		}
		else
		{
			ans.p = -angleP;
		}
	}
	else if (x < 0)
	{
		if (y > 0)
		{
			ans.p = angleP;
		}
		else
		{
			ans.p = -angleP;
		}
	}
	ans.Normal();
	return ans;
}

