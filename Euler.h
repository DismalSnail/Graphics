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

	/*ŷ����תΪ����*/
	CVector068 CEuler::ToVector068(CVector068 *updir);//�������updirָ�벻Ϊ0�����������ͬʱ����Ϸ�������updir�С�

	CMatrix068 CEuler::ToMatrix068();//ŷ����ת��Ϊ����

	CQuaternion CEuler::ToQuaternion();//ŷ����ת��Ϊ��Ԫ��

	/*ŷ���ǹ淶��*/
	void CEuler::Normal();//h,r�Ƕ���-180~180��p�Ƕ���-90~90��������ʱ,h��������r�Ķ�����

};

