#pragma once
#include "opengl\OpenGL.h"
class CMyOpenGL :public COpenGL
{
public:
	CMyOpenGL(void);
	~CMyOpenGL(void);
	virtual void PostInit(void);
	virtual void InDraw(void);
	bool OnKey(unsigned char nChar, bool  bDown);
	bool flag;
	int g_iCurFrame;//�������߽ڵ�
	int g_mode;//�켣�����ģʽ
	float g_angle;//x0yƽ����ת�Ƕ�
	float g_t[360];//��ֵϵ��
	int g_n;//��ֵ��
	int g_count;//��ֵ������
	bool g_isSlerp;//��ǰ�Ƿ��ֵ

	CVector068 g_prepos;//�����˵���һ��λ��
	CVector068 g_predir;//�����˵���һ������

	CQuaternion g_prevQua;//ԭλ����Ԫ��
	CQuaternion g_curQua;//��ǰλ����Ԫ��
	CQuaternion g_result[360];//��ֵ���

	/*�����ֹ켣��ȫ�ֱ���*/
	CVector068 g_pos[129];//��¼�ڵ������
	CVector068 g_circle[20];//��¼ÿ���ڵ��ϵ������
	CVector068 g_allpos[129*20];//��¼���е������

	/*���ƻ������ٶȵ�ȫ��*/
	CVector068 g_ballpos,g_balldir;//С���λ�úͷ���
	float g_ballspeed ;	   //����ٶ�
	float g_ballspeed1;		   //��ķ����ٶ�
	int g_ballindex;		   //��ǰ�����ڵ����߽ڵ��λ��
	int change;				   //�ӵ����

	//�ӵ�λ�úͷ���
	float mx,my,mz,rx,ry,rz;//ƽ�ƺ���ת
	float sx,sy,sz;					//����
	float mspeed;							//ƽ���ٶ�
	float rspeed;							//�����ٶ�
	float g_IEyeMat[16];//��ʼ������
	float g_EyeMat[16];
	float EyeMat[16];
	int mode;//�ӵ����ģʽ

	int pers2;//����ģʽ����
	float robotspeed;//С�����ӵ�ľ���
	void update();
	void DrawRobot(int type);
	void RenderWorld();
	void SetView();
	void SetRC();
	void myDisplay();
};

