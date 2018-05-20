#pragma once
#include"afxver_.h"

class CQuaternion;
class CEuler;
class CVector068;
class AFX_CLASS_EXPORT CMatrix068
{
public:
	CMatrix068(void);
	~CMatrix068(void);

	float m00,m10,m20,m30;
	float m01,m11,m21,m31;
	float m02,m12,m22,m32;
	float m03,m13,m23,m33;

	operator float*(){return &m00;}

	void Set(float *p);	//������16��Ԫ�ظ�ֵ

	CMatrix068& operator=(const CMatrix068& p);//����ֵ

	CMatrix068 operator*(float d);//��������

	CMatrix068 operator*(CMatrix068& p);//�������

	CVector068 vecMul(CVector068& p); //�������������

	CVector068 posMul(CVector068& p);//����������

	void SetRotate(float seta,CVector068 axis);	//����Ϊ��ת����

	void SetTrans(CVector068 trans);		//����Ϊƽ�ƾ���

	void SetScale(CVector068 p);		//����Ϊ���ž���

	CMatrix068& SetRotate(float seta,int axis);//0��ʾx����ת��1��ʾy��,2��ʾz��

	float Inverse();//��������,�ɹ���������ʽ��ֵ�����򷵻�0

	CMatrix068 GetInverse();//���������

	CEuler CMatrix068::ToEuler();//����ת��Ϊŷ����

	CQuaternion CMatrix068::ToQuaternion();//����ת��Ϊ��Ԫ��

};
