#pragma once

class CEuler;
class CVector068;
class CMatrix068;

class CVector068
{
public:
	float x;
	float y;
	float z;
	CVector068(float fx,float fy,float fz);
public:
	void Set(float x,float y,float z);					//����������x��y��z����ֵ
	CVector068 operator+(CVector068 &p);				//���������ӷ�
	CVector068 operator-(CVector068 &p);				//������������
	void operator=(CVector068 &p);						//����������ֵ
	bool operator==(CVector068 &p);						//�������� ==
	bool operator!=(CVector068 &p);						//�������� !=
	friend CVector068 operator*(CVector068 &p,float n);	//��������
	friend CVector068 operator*(float n,CVector068 &p);
	float dotMul(CVector068 &n);						//�������
	CVector068 crossMul(CVector068 &n);					//�������
	void Normalize();									//������׼��
	float len();										//������ģ
	CVector068 project(CVector068 &n);					//����ͶӰ����

	CEuler CVector068::ToEuler();//����תŷ����


	operator float*(){return &x;}							//�Զ�ת������
	CVector068(void);
	~CVector068(void);
};

