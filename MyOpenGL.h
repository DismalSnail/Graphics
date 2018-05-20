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
	CVector068 g_ballpos,g_balldir;//球位置和方向。
	CVector068 g_oldballdir,g_nballdir,g_Nballdir;
	float g_ballspeed;//球速度
	float g_old_ballspeed;
	int g_ballindex;//当前球所在的曲线节点位置。
	int look,look2;
	bool mykey[25];//多键盘控制
	CEuler abd;
	int mode,ACBD;
	bool SL;//机器人转身时的控制量
	CQuaternion Result[25];
	CVector068 g_oldballpos;//用于保存机器人上一帧的位置
	float bx;//机器人与飞船变形控制
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

