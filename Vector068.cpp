#include "StdAfx.h"
#include <math.h>
#include "Vector068.h"


CVector068::CVector068(void)
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}


CVector068::~CVector068(void)
{
}


void CVector068::Set(float x,float y,float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
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
	CVector068_T.x = this->x + p.x;
	CVector068_T.y = this->y + p.y;
	CVector068_T.z = this->z + p.z;

	return CVector068_T;
}

CVector068 CVector068::operator-(CVector068 &p)
{
	CVector068 CVector068_T;
	CVector068_T.x = this->x - p.x;
	CVector068_T.y = this->y - p.y;
	CVector068_T.z = this->z - p.z;

	return CVector068_T;
}

void CVector068::operator=(CVector068 &p)
{
	this->x = p.x;
	this->y = p.y;
	this->z = p.z;
}

bool CVector068::operator==(CVector068 &p)
{
	if (this->x != p.x)
	{
		return false;
	} 
	if (this->y != p.y)
	{
		return false;
	}
	if(this->z != p.z)
	{
		return false;
	}
	return true;
}


bool CVector068::operator!=(CVector068 &p)
{

	if (this->x != p.x)
	{
		return true;
	} 
	if (this->y != p.y)
	{
		return true;
	}
	if(this->z != p.z)
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
