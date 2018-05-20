#pragma once

class CEuler;
class CMatrix068;
class CVector068;

class CQuaternion
{
public:
	CQuaternion(void);
	~CQuaternion(void);
	float x,y,z,w;
	void Set(float x,float y,float z,float w);
	operator float*(){return &x;}

	CEuler CQuaternion::ToEuler();			//��Ԫ��ת��Ϊŷ����
	CMatrix068 CQuaternion::ToMatrix();		//��Ԫ��ת��Ϊ����

	void SetAngle(float angle,CVector068 axis);		//��Ԫ������
	CQuaternion& operator=(const CQuaternion& p);	//���ظ�ֵ
	CQuaternion operator+(const CQuaternion& p);		//���ء�+��
	CQuaternion operator*(float data);			//��������
	CQuaternion operator*(const CQuaternion&p);		//��Ԫ���˷�
	float dotMul(const CQuaternion&p);				//���
	float len();									//��ģ
	CQuaternion Normalize();								//���׼��
	void Inverse();							//������Ԫ��,��ı�����
	CQuaternion GetInverse();						//������Ԫ��,���ı����������µ���Ԫ��
	CQuaternion Div(const CQuaternion&b);			//��� ��ǰΪa,��c=a-b
	void GetAngle(float& angle,CVector068& axis);	//����ת��ͽǶ�
	CQuaternion Slerp(CQuaternion& Vend,float t);					   //��ֵ���ӵ�ǰ��Ԫ����ֵ��Vend��Ԫ��,t�ǲ���[0,1]
	void Slerp(CQuaternion& Vend,int n,float *t,CQuaternion *Result);//��ֵ��һ�β�ֵ��n�����ݡ���ֵ��������������t�У�������ص�����Result�С�
	CQuaternion power(float n); //����

};

