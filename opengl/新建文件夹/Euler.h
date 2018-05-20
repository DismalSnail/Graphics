#pragma once

class CMatrix068;
class CVector068;
class CQuaternion;
class CEuler
{
public:
	CEuler(void);
	~CEuler(void);
	float h,p,b;
	void Set(float h,float p,float b);
	operator float*(){return &h;}

	/*欧拉角转为向量*/
	CVector068 CEuler::ToVector068(CVector068 *updir);//如果传入updir指针不为0，则输出向量同时输出上方向量到updir中。

	CMatrix068 CEuler::ToMatrix068();//欧拉角转换为矩阵

	CQuaternion CEuler::ToQuaternion();//欧拉角转换为四元数

	/*欧拉角规范化*/
	void CEuler::Normal();//h,r角度在-180~180，p角度在-90~90。万向锁时,h代替所有r的度数。

};

