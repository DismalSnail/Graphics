#pragma once

#include"afxver_.h"

class CEuler;
class CVector068;
class CMatrix068;

class AFX_CLASS_EXPORT CVector068
{
public:
	float x;
	float y;
	float z;
	CVector068(float fx,float fy,float fz);
public:
	void Set(float x,float y,float z);					//设置向量（x，y，z）的值
	CVector068 operator+(CVector068 &p);				//重载向量加法
	CVector068 operator-(CVector068 &p);				//重载向量减法
	void operator=(CVector068 &p);						//重载向量赋值
	bool operator==(CVector068 &p);						//重载向量 ==
	bool operator!=(CVector068 &p);						//重载向量 !=
    CVector068 operator*(float n);	//向量数乘
	float dotMul(CVector068 &n);						//向量点乘
	CVector068 crossMul(CVector068 &n);					//向量叉乘
	void Normalize();									//向量标准化
	float len();										//向量求模
	CVector068 project(CVector068 &n);					//向量投影操作

	CEuler CVector068::ToEuler();//向量转欧拉角


	operator float*(){return &x;}							//自动转换类型
	CVector068(void);
	~CVector068(void);
};

