#pragma once
#include "Vector068.h"
class CMatrix068
{
public:
	CMatrix068(void);
	~CMatrix068(void);

	float m00,m10,m20,m30;
	float m01,m11,m21,m31;
	float m02,m12,m22,m32;
	float m03,m13,m23,m33;

	operator float*(){return &m00;}

	void Set(float *p);	//给矩阵16个元素赋值

	CMatrix068& operator=(const CMatrix068& p);//矩阵赋值

	CMatrix068 operator*(float d);//矩阵数乘

	CMatrix068 operator*(CMatrix068& p);//矩阵相乘

	CVector068 vecMul(CVector068& p); //矩阵与向量相乘

	CVector068 posMul(CVector068& p);//矩阵与点相乘

	void SetRotate(float seta,CVector068 axis);	//设置为旋转矩阵

	void SetTrans(CVector068 trans);		//设置为平移矩阵

	void SetScale(CVector068 p);		//设置为缩放矩阵

	float Inverse();//矩阵求逆,成功返回行列式的值，否则返回0

	CMatrix068 GetInverse();//返回逆矩阵


};

