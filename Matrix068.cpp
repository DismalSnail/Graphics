#include "StdAfx.h"
#include "Matrix068.h"


CMatrix068::CMatrix068(void)
{

}


CMatrix068::~CMatrix068(void)
{
}

void CMatrix068::Set(float *p)	//给矩阵16个元素赋值
{
	this->m00=p[0];this->m10=p[1];this->m20=p[2];this->m30=p[3];
	this->m01=p[4];this->m11=p[5];this->m21=p[6];this->m31=p[7];
	this->m02=p[8];this->m12=p[9];this->m22=p[10];this->m32=p[11];
	this->m03=p[12];this->m13=p[13];this->m23=p[14];this->m33=p[15];
}

CMatrix068& CMatrix068::operator=(const CMatrix068& p)//矩阵赋值
{
	m00=p.m00;m10=p.m10;m20=p.m20;m30=p.m30;
	m01=p.m01;m11=p.m11;m21=p.m21;m31=p.m31;
	m02=p.m02;m12=p.m12;m22=p.m22;m32=p.m32;
	m03=p.m03;m13=p.m13;m23=p.m23;m33=p.m33;
	return *this;
}

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

		CMatrix068_T.m03=m00*p.m30+m01*p.m31+m02*p.m32+m03*p.m33;
		CMatrix068_T.m13=m10*p.m30+m11*p.m31+m12*p.m32+m13*p.m33;
		CMatrix068_T.m23=m20*p.m30+m21*p.m31+m22*p.m32+m23*p.m33;
		CMatrix068_T.m33=m30*p.m30+m31*p.m31+m32*p.m32+m33*p.m33;

		return CMatrix068_T;

}

// CVector068 CMatrix068::vecMul(CVector068& p) //矩阵与向量相乘
// {
//
// }
//
// CVector068 CMatrix068::posMul(CVector068& p)//矩阵与点相乘
// {
//
// }
//
// void CMatrix068::SetRotate(float seta,CVector068 axis)	//设置为旋转矩阵
// {
//
// }
//
// void CMatrix068::SetTrans(CVector068 trans)		//设置为平移矩阵
// {
//
// }
//
// void CMatrix068::SetScale(CVector068 p)		//设置为缩放矩阵
// {
//
// }
//
// float CMatrix068::Inverse()//矩阵求逆,成功返回行列式的值，否则返回0
// {
//
// }
//
// CMatrix068 CMatrix068::GetInverse()//返回逆矩阵
// {
//
// }
