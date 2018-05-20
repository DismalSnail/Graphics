#pragma once
#include "opengl\OpenGL.h"
#include "glaux.h"
#pragma comment(lib,"opengl/SCENE.lib")
#pragma comment(lib,"glaux.lib")
class CMyOpenGL : public COpenGL
{
public:

	int g_mode;
	int g_iCurFrame;
	float g_angle;
	CVector068 g_pos[129];
	CVector068 g_circle[20];
	CVector068 g_allpos[129*20];
	CVector068 g_ballpos,g_balldir;//��λ�úͷ���
	CVector068 g_oldballdir,g_nballdir,g_Nballdir;
	float g_ballspeed;//���ٶ�
	float g_old_ballspeed;
	int g_ballindex;//��ǰ�����ڵ����߽ڵ�λ�á�
	int look,look2;
	bool mykey[25];//����̿���
	CEuler abd;
	int mode,ACBD;
	bool SL;//������ת��ʱ�Ŀ�����
	CQuaternion Result[25];
	CVector068 g_oldballpos;//���ڱ����������һ֡��λ��
	float bx;//��������ɴ����ο���
	CMyOpenGL(void);
	~CMyOpenGL(void);
	virtual void PostInit(void);
	virtual void InDraw(void);
	virtual bool OnKey(unsigned int nChar, bool bDown);
	void update();
	void SetRC();
	void DrawRobot(int type);
	int rerobot;
	CMatrix068 f_pos;
	int robotpos(CVector068 pos);
	float EYElen;
	CVector068 g_updir,g_rightdir;
	bool wenli();
	char *resource_path[2];
	GLuint texture[1],Texture[1];
};

