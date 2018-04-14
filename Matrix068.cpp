#include "stdafx.h"

#define Pi 3.1415926
CMatrix068::CMatrix068(void)
{

}


CMatrix068::~CMatrix068(void)
{
}

//************************************
// Method:    Set
// FullName:  CMatrix068::Set
// Access:    public
// Returns:   void
// Qualifier: /*设置矩阵16个元素 */
// Parameter: float * p
//************************************
void CMatrix068::Set(float *p)	//设置矩阵16个元素
{
	this->m00=p[0];this->m10=p[1];this->m20=p[2];this->m30=p[3];
	this->m01=p[4];this->m11=p[5];this->m21=p[6];this->m31=p[7];
	this->m02=p[8];this->m12=p[9];this->m22=p[10];this->m32=p[11];
	this->m03=p[12];this->m13=p[13];this->m23=p[14];this->m33=p[15];
}

//************************************
// Method:    operator=
// FullName:  CMatrix068::operator=
// Access:    public
// Returns:   CMatrix068&
// Qualifier: /*矩阵赋值 */
// Parameter: const CMatrix068 & p
//************************************
CMatrix068& CMatrix068::operator=(const CMatrix068& p)//矩阵赋值
{
	m00=p.m00;m10=p.m10;m20=p.m20;m30=p.m30;
	m01=p.m01;m11=p.m11;m21=p.m21;m31=p.m31;
	m02=p.m02;m12=p.m12;m22=p.m22;m32=p.m32;
	m03=p.m03;m13=p.m13;m23=p.m23;m33=p.m33;
	return *this;
}

//************************************
// Method:    operator*
// FullName:  CMatrix068::operator*
// Access:    public
// Returns:   CMatrix068
// Qualifier: /*矩阵数乘 */
// Parameter: float d
//************************************
CMatrix068 CMatrix068::operator*(float d)//矩阵数乘
{
	CMatrix068 CMatrix068_T;
	CMatrix068_T.m00=m00*d;CMatrix068_T.m10=m10*d;CMatrix068_T.m20=m20*d;CMatrix068_T.m30=m30*d;
	CMatrix068_T.m01=m01*d;CMatrix068_T.m11=m11*d;CMatrix068_T.m21=m21*d;CMatrix068_T.m31=m31*d;
	CMatrix068_T.m02=m02*d;CMatrix068_T.m12=m12*d;CMatrix068_T.m22=m22*d;CMatrix068_T.m32=m32*d;
	CMatrix068_T.m03=m03*d;CMatrix068_T.m13=m13*d;CMatrix068_T.m23=m23*d;CMatrix068_T.m33=m33*d;
	return CMatrix068_T;
}

CMatrix068 CMatrix068::operator*(CMatrix068& p)//矩阵相乘
{
		CMatrix068 CMatrix068_T;
		CMatrix068_T.m00=m00*p.m00+m01*p.m10+m02*p.m20+m03*p.m30;
		CMatrix068_T.m10=m10*p.m00+m11*p.m10+m12*p.m20+m13*p.m30;
		CMatrix068_T.m20=m20*p.m00+m21*p.m10+m22*p.m20+m23*p.m30;
		CMatrix068_T.m30=m30*p.m00+m31*p.m10+m32*p.m20+m33*p.m30;

		CMatrix068_T.m01=m00*p.m01+m01*p.m11+m02*p.m21+m03*p.m31;
		CMatrix068_T.m11=m10*p.m01+m11*p.m11+m12*p.m21+m13*p.m31;
		CMatrix068_T.m21=m20*p.m01+m21*p.m11+m22*p.m21+m23*p.m31;
		CMatrix068_T.m31=m30*p.m01+m31*p.m11+m32*p.m21+m33*p.m31;

		CMatrix068_T.m02=m00*p.m02+m01*p.m12+m02*p.m22+m03*p.m32;
		CMatrix068_T.m12=m10*p.m02+m11*p.m12+m12*p.m22+m13*p.m32;
		CMatrix068_T.m22=m20*p.m02+m21*p.m12+m22*p.m22+m23*p.m32;
		CMatrix068_T.m32=m30*p.m02+m31*p.m12+m32*p.m22+m33*p.m32;

		CMatrix068_T.m03=m00*p.m03+m01*p.m13+m02*p.m23+m03*p.m33;
		CMatrix068_T.m13=m10*p.m03+m11*p.m13+m12*p.m23+m13*p.m33;
		CMatrix068_T.m23=m20*p.m03+m21*p.m13+m22*p.m23+m23*p.m33;
		CMatrix068_T.m33=m30*p.m03+m31*p.m13+m32*p.m23+m33*p.m33;

		return CMatrix068_T;
}

//************************************
// Method:    vecMul
// FullName:  CMatrix068::vecMul
// Access:    public
// Returns:   CVector068
// Qualifier: /*矩阵乘向量 */
// Parameter: CVector068 & p
//************************************
CVector068 CMatrix068::vecMul(CVector068& p) //矩阵乘向量
{
		CVector068 CVector068_T;
		CVector068_T.x=m00*p.x+m01*p.y+m02*p.z+m03*0.0;
		CVector068_T.y=m10*p.x+m11*p.y+m12*p.z+m13*0.0;
		CVector068_T.z=m20*p.x+m21*p.y+m22*p.z+m23*0.0;
		return CVector068_T;
}

CVector068 CMatrix068::posMul(CVector068& p)//矩阵乘数
{
	CVector068 CVector068_T;
	CVector068_T.x=m00*p.x+m01*p.y+m02*p.z+m03*1.0;
	CVector068_T.y=m10*p.x+m11*p.y+m12*p.z+m13*1.0;
	CVector068_T.z=m20*p.x+m21*p.y+m22*p.z+m23*1.0;
	return CVector068_T;
}

void CMatrix068::SetRotate(float seta,CVector068 axis)	//设置旋转矩阵
{
		float nx;
		float ny;
		float nz;
		float seta_r;
		seta_r=seta*(Pi/180);
		axis.Normalize();
		nx=axis.x;ny=axis.y;nz=axis.z;
		m03=0.0;m13=0.0;m23=0.0;m33=1.0;m30=0.0;m31=0.0;m32=0.0;

		m00=nx*nx*(1-cos(seta_r))+cos(seta_r);
		m01=nx*ny*(1-cos(seta_r))-nz*sin(seta_r);
		m02=nx*nz*(1-cos(seta_r))+ny*sin(seta_r);

		m10=nx*ny*(1-cos(seta_r))+nz*sin(seta_r);
		m11=ny*ny*(1-cos(seta_r))+cos(seta_r);
		m12=ny*nz*(1-cos(seta_r))-nx*sin(seta_r);

		m20=nx*nz*(1-cos(seta_r))-ny*sin(seta_r);
		m21=ny*nz*(1-cos(seta_r))+nx*sin(seta_r);
		m22=nz*nz*(1-cos(seta_r))+cos(seta_r);
}

 void CMatrix068::SetTrans(CVector068 trans)//设置为平移矩阵
 {
	  m00=1;m10=0;m20=0;m30=0;
	  m01=0;m11=1;m21=0;m31=0;
	  m02=0;m12=0;m22=1;m32=0;
	  m03=trans.x;m13=trans.y,m23=trans.z,m33=1;
 }

 void CMatrix068::SetScale(CVector068 p)//设置为缩放矩阵
 {
	 m00=p.x;m10=0;m20=0;m30=0;
	 m01=0;m11=p.y;m21=0;m31=0;
	 m02=0;m12=0;m22=p.z;m32=0;
	 m03=0;m13=0,m23=0,m33=1;
 }

 float CMatrix068::Inverse()//矩阵求逆
 {
	 float value00;
	 float value01;
	 float value02;
	 float value03;
	 float value;
	 value00=m11*m22*m33+m12*m23*m31+m21*m32*m13-m13*m22*m31-m21*m12*m33-m32*m23*m11;
	 value01=m10*m22*m33+m12*m23*m30+m20*m32*m13-m13*m22*m30-m12*m20*m33-m23*m32*m10;
	 value02=m10*m21*m33+m11*m23*m30+m20*m31*m13-m13*m21*m30-m20*m11*m33-m31*m23*m10;
	 value03=m10*m21*m32+m11*m22*m30+m20*m31*m12-m12*m21*m30-m20*m11*m32-m22*m31*m10;
	 value = m00*value00-m01*value01+m02*value02-m03*value03;
	 return value;
 }

CMatrix068 CMatrix068::GetInverse()//矩阵求逆
{
	CMatrix068 CMatrix068_T;
	float value=Inverse();
	float value00;float value01;float value02;float value03;
	float value10;float value11;float value12;float value13;
	float value20;float value21;float value22;float value23;
	float value30;float value31;float value32;float value33;

	value00 = m11*m22*m33 + m12*m23*m31 + m21*m32*m13 - m13*m22*m31 - m21*m12*m33 - m32*m23*m11;
	value10 = -(m10*m22*m33 + m12*m23*m30 + m20*m32*m13 - m13*m22*m30 - m12*m20*m33 - m23*m32*m10);
	value20 = m10*m21*m33 + m11*m23*m30 + m20*m31*m13 - m13*m21*m30 - m20*m11*m33 - m31*m23*m10;
	value30 = -(m10*m21*m32 + m11*m22*m30 + m20*m31*m12 - m12*m21*m30 - m20*m11*m32 - m22*m31*m10);

	value01 = -(m01*m22*m33 + m02*m23*m31 + m21*m32*m03 - m03*m22*m31 - m21*m02*m33 - m32*m23*m01);
	value11 = m00*m22*m33 + m02*m23*m30 + m20*m32*m03 - m03*m22*m30 - m02*m20*m33 - m23*m32*m00;
	value21 = -(m00*m21*m33 + m01*m23*m30 + m20*m31*m03 - m03*m21*m30 - m20*m01*m33 - m31*m23*m00);
	value31 = m00*m21*m32 + m01*m22*m30 + m20*m31*m02 - m02*m21*m30 - m20*m01*m32 - m22*m31*m00;

	value02 = m01*m12*m33 + m02*m13*m31 + m11*m32*m03 - m03*m12*m31 - m11*m02*m33 - m32*m13*m01;
	value12 = -(m00*m12*m33 + m02*m13*m30 + m10*m32*m03 - m03*m12*m30 - m10*m02*m33 - m13*m32*m00);
	value22 = m00*m11*m33 + m10*m31*m03 + m10*m13*m30 - m03*m11*m30 - m10*m01*m33 - m31*m13*m00;
	value32 = -(m00*m11*m32 + m10*m31*m02 + m01*m12*m30 - m02*m11*m30 - m10*m01*m32 - m12*m31*m00);

	value03 = -(m01*m12*m23 + m11*m22*m03 + m21*m02*m13 - m03*m21*m12 - m22*m13*m01 - m02*m23*m11);
	value13 = m00*m12*m23 + m10*m22*m03 + m20*m02*m13 - m03*m20*m12 - m22*m13*m00 - m02*m23*m10;
	value23 = -(m00*m11*m23 + m10*m21*m03 + m20*m01*m13 - m03*m20*m11 - m21*m13*m00 - m01*m23*m10);
	value33 = m00*m11*m22 + m10*m21*m02 + m20*m01*m12 - m02*m20*m11 - m21*m12*m00 - m01*m22*m10;

	CMatrix068_T.m00=value00/value;CMatrix068_T.m10=value10/value;CMatrix068_T.m20=value20/value;CMatrix068_T.m30=value30/value;
	CMatrix068_T.m01=value01/value;CMatrix068_T.m11=value11/value;CMatrix068_T.m21=value21/value;CMatrix068_T.m31=value31/value;
	CMatrix068_T.m02=value02/value;CMatrix068_T.m12=value12/value;CMatrix068_T.m22=value22/value;CMatrix068_T.m32=value32/value;
	CMatrix068_T.m03=value03/value;CMatrix068_T.m13=value13/value;CMatrix068_T.m23=value23/value;CMatrix068_T.m33=value33/value;
	for (int i = 0; i < 16; i++) {
		if (CMatrix068_T[i]==0.0) {
			CMatrix068_T[i]=0.0;
		}
	}
	return CMatrix068_T;
}

CMatrix068& CMatrix068::SetRotate(float seta,int axis)//0表示x轴旋转，1表示y轴,2表示z轴
{
	float c = cos(seta);
	float s = sin(seta);
	if(axis==0)
	{
		m00=1;m01=0;m02=0;m03=0;
		m10=0;m11=c;m12=-s;m13=0;
		m20=0;m21=s;m22=c;m23=0;
		m30=0;m31=0;m32=0;m33=1;
	}
	else if(axis==1)
	{
		m00=c;m01=0;m02=s;m03=0;
		m10=0;m11=1;m12=0;m13=0;
		m20=-s;m21=0;m22=c;m23=0;
		m30=0;m31=0;m32=0;m33=1;
	}
	else
	{
		m00=c;m01=-s;m02=0;m03=0;
		m10=s;m11=c;m12=0;m13=0;
		m20=0;m21=0;m22=1;m23=0;
		m30=0;m31=0;m32=0;m33=1;
	}
	return *this;
}

//************************************
// Method:    ToEuler
// FullName:  CMatrix068::ToEuler
// Access:    public
// Returns:   CEuler
// Qualifier:
//************************************
CEuler CMatrix068::ToEuler()
{
	CEuler CEU;
	float p;
	float h;
	float b;
	h=atan2(m02,m22)*180/PI;
	p=asin(-m12)*180/PI;
	b=atan2(m10,m11)*180/PI;
	if (abs(cos(asin(-m12))-0)<0.0005)
	{
		h=atan2(-m20,m00)*180/PI;
		b=0;
	}
	if (h > 180)
	{
		h-=360;
	}
	if (h<-180)
	{
		h+=360;
	}
	if (p>90)
	{
		p-=180;
	}
	if (p<-90)
	{
		p+=180;
	}
	CEU.h=h;
	CEU.p=p;
	CEU.b=b;
	return CEU;
}


//************************************
// Method:    ToQuaternion
// FullName:  CMatrix068::ToQuaternion
// Access:    public
// Returns:   CQuaternion
// Qualifier:
//************************************
CQuaternion CMatrix068::ToQuaternion()
{
	CQuaternion CQU;
	float w=sqrt(m00+m11+m22+1)/2;
	float x=sqrt(m00-m11-m22+1)/2;
	float y=sqrt(-m00+m11-m22+1)/2;
	float z=sqrt(-m00-m11+m22+1)/2;
	if (w >=x && w >= y && w >= z)
	{
		x=(m21-m12)/(4*w);
		y=(m02-m20)/(4*w);
		z=(m10-m01)/(4*w);
	}
	if (x >=w && x >= y && x >= z)
	{
		x=(m21-m12)/(4*x);
		y=(m10+m01)/(4*x);
		z=(m02+m20)/(4*x);
	}
	if (y >=x && y >= w && y >= z)
	{
		x=(m02-m20)/(4*y);
		y=(m10+m01)/(4*y);
		z=(m21+m12)/(4*y);
	}
	if (z >=x && z >= y && z >= w)
	{
		x=(m10-m01)/(4*z);
		y=(m02+m21)/(4*z);
		z=(m21+m12)/(4*z);
	}
	CQU.x=x;
	CQU.y=y;
	CQU.z=z;
	CQU.w=w;
	return CQU;
}
