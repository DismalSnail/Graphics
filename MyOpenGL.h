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
	int g_iCurFrame;//计算曲线节点
	int g_mode;//轨迹的填充模式
	float g_angle;//x0y平面旋转角度
	float g_t[360];//插值系数
	int g_n;//插值量
	int g_count;//插值计数器
	bool g_isSlerp;//当前是否插值

	CVector068 g_prepos;//机器人的下一个位置
	CVector068 g_predir;//机器人的下一个方向

	CQuaternion g_prevQua;//原位置四元数
	CQuaternion g_curQua;//当前位置四元数
	CQuaternion g_result[360];//插值结果

	/*画名字轨迹的全局变量*/
	CVector068 g_pos[129];//记录节点的数组
	CVector068 g_circle[20];//记录每个节点上点的数组
	CVector068 g_allpos[129*20];//记录所有点的数组

	/*控制机器人速度的全局*/
	CVector068 g_ballpos,g_balldir;//小球的位置和方向
	float g_ballspeed ;	   //球的速度
	float g_ballspeed1;		   //球的反向速度
	int g_ballindex;		   //当前球所在的曲线节点的位置
	int change;				   //视点控制

	//视点位置和方向
	float mx,my,mz,rx,ry,rz;//平移和旋转
	float sx,sy,sz;					//缩放
	float mspeed;							//平移速度
	float rspeed;							//缩放速度
	float g_IEyeMat[16];//初始眼坐标
	float g_EyeMat[16];
	float EyeMat[16];
	int mode;//视点控制模式

	int pers2;//跟踪模式控制
	float robotspeed;//小球与视点的距离
	void update();
	void DrawRobot(int type);
	void RenderWorld();
	void SetView();
	void SetRC();
	void myDisplay();
};

