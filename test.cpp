﻿// test.cpp : Defines the entry point for the console application.
#include "stdafx.h"

void myDisplay(void);

bool flag=false;
int g_iCurFrame=0; //用于计算曲线节点
int g_mode = 0;	   //轨迹的填充模式
float g_angle = 0 ;//xOy平面旋转角度
float g_t[360];//插值系数
int g_n = 0;//插值量
int g_count = 0;//插值计数器
bool g_isSlerp = false;//当前是否在插值

CVector068 g_prepos;//小球的下一个位置
CVector068 g_predir;//机器人的下一个方向

CQuaternion g_prevQua;//原位置四元数
CQuaternion g_curQua;//当前位置四元数
CQuaternion g_result[360];//插值结果

/*画名字轨迹的全局变量*/
#define POINTNUM 129//笔画点的个数
#define CIRCLENUM 20//每个节点上的点个数
CVector068 g_pos[POINTNUM];//记录节点的数组
CVector068 g_circle[CIRCLENUM];//记录每个节点上点的数组
CVector068 g_allpos[POINTNUM*CIRCLENUM];//记录所有点的数组

/*控制小球速度的全局变量*/
CVector068 g_ballpos,g_balldir;//球的位置和方向
float g_ballspeed = 0.06;	   //球的速度
float g_ballspeed1 = 0;		   //球的反向速度
int g_ballindex;			   //当前球所在的曲线节点位置
int change=0;				   //视点控制

//视点位置和方向
float mx=0,my=5,mz=10,rx=0,ry=0,rz=0;//平移和旋转
float sx=1,sy=1,sz=1;					//缩放
float mspeed=1;							//平移速度
float rspeed=1;							//旋转速度
float g_IEyeMat[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};//初始眼坐标系
float g_EyeMat[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
float EyeMat[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
int mode=0;//视点控制模式

int pers2=0;//跟踪模式控制
float robotspeed=-10.0;//小球与视点的距离
void myKeyboardFunc(unsigned char key,int x, int y);
//////////////////////////////////////////////////////////////////////////
void myKeyboardUpFunc(unsigned char key,int x, int y)
{
	bool bChange=false;
	switch(key)
	{
	case 'w':
		//my+=mspeed;
		if (change==1)
		{
			break;
		}
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0,-mspeed,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			mx+=g_IEyeMat[4]*mspeed;
			my+=g_IEyeMat[5]*mspeed;
			mz+=g_IEyeMat[6]*mspeed;
		}
		break;
	case 's':
		//my-=mspeed;
		if (change==1)
		{
			break;
		}
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0,mspeed,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			mx-=g_IEyeMat[4]*mspeed;
			my-=g_IEyeMat[5]*mspeed;
			mz-=g_IEyeMat[6]*mspeed;
		}

		break;
	case 'a':
		//mx-=mspeed;
		if (change==1)
		{
			break;
		}
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(mspeed,0,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			mx-=g_IEyeMat[0]*mspeed;
			my-=g_IEyeMat[1]*mspeed;
			mz-=g_IEyeMat[2]*mspeed;
		}

		break;
	case 'd':
		if (change==1)
		{
			break;
		}
		//mx+=mspeed;
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(-mspeed,0,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			mx+=g_IEyeMat[0]*mspeed;
			my+=g_IEyeMat[1]*mspeed;
			mz+=g_IEyeMat[2]*mspeed;
		}

		break;
	case 'q':
		if (change==1)
		{
			robotspeed+=0.3;
			break;
		}
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0,0,mspeed);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			mx-=g_IEyeMat[8]*mspeed;
			my-=g_IEyeMat[9]*mspeed;
			mz-=g_IEyeMat[10]*mspeed;
		}
		//mz-=mspeed;

		break;
	case 'e':
		if (change==1)
		{
			robotspeed-=0.3;
			break;
		}
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0,0,-mspeed);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			mx+=g_IEyeMat[8]*mspeed;
			my+=g_IEyeMat[9]*mspeed;
			mz+=g_IEyeMat[10]*mspeed;
		}
		//mz+=mspeed;

		break;
	case 'i':
		if (change==1)
		{
			break;
		}
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glRotatef(-rspeed,1,0,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			rx+=rspeed;
			bChange = true;
		}
		break;
	case 'k':
		if (change==1)
		{
			break;
		}
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glRotatef(rspeed,1,0,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			rx-=rspeed;
			bChange = true;
		}

		break;
	case 'j':
		if (change==1)
		{
			break;
		}
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glRotatef(-rspeed,0,1,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			ry+=rspeed;
			bChange = true;
		}

		break;
	case 'l':
		if (change==1)
		{
			break;
		}
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glRotatef(rspeed,0,1,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			ry-=rspeed;
			bChange = true;
		}

		break;
	case 'u':
		if (change==1)
		{
			break;
		}
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glRotatef(rspeed,0,0,1);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			rz+=rspeed;
			bChange = true;
		}

		break;
	case 'o':
		if (change==1)
		{
			break;
		}
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glRotatef(-rspeed,0,0,1);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			rz-=rspeed;
			bChange = true;
		}
		break;
	}
}

void update()
{
	glutKeyboardUpFunc(&myKeyboardUpFunc);
	g_ballspeed1 = abs(g_ballspeed);
	if(g_ballspeed < 0)//速度为负
	{
		if(g_ballindex>0)
		{
			float leftlen = (g_pos[g_ballindex-1] - g_ballpos).len();
			 g_predir=g_balldir;
			 g_prepos=g_ballpos;
			g_balldir = g_pos[g_ballindex-1]-g_ballpos;
			g_balldir.Normalize();
			if(leftlen>=g_ballspeed1)
			{
				g_ballpos = g_ballpos + g_balldir * g_ballspeed1;
			}
			else
			{
				g_ballindex--;
				if(g_ballindex<0)
				{
					g_ballpos = g_ballpos + g_balldir * leftlen;
					g_balldir = g_pos[POINTNUM-1]-g_pos[g_ballindex+1];
					g_balldir.Normalize();
					g_ballindex=-1;
				}
				else
				{
					g_ballpos = g_ballpos + g_balldir * leftlen;
					g_balldir = g_pos[g_ballindex-1]-g_pos[g_ballindex];
					g_balldir.Normalize();
				}
				g_ballspeed1-=leftlen;
			}
		}
		else
		{
			g_balldir = g_pos[POINTNUM-1]-g_pos[g_ballindex];
			g_balldir.Normalize();
			g_ballindex=POINTNUM;
		}
	}
	else
	{
		if(g_ballindex<POINTNUM-1)
		{
			float leftlen = (g_pos[g_ballindex+1] - g_ballpos).len();
			g_predir=g_balldir;
			g_prepos=g_ballpos;
			g_balldir = g_pos[g_ballindex+1]-g_ballpos;
			g_balldir.Normalize();
			if(leftlen>=g_ballspeed1)
			{
				g_ballpos = g_ballpos + g_balldir * g_ballspeed1;
			}
			else
			{
				g_ballindex++;
				if(g_ballindex>=POINTNUM-1)
				{
					g_ballpos =g_ballpos + g_balldir * leftlen;
					g_balldir = g_pos[0]-g_pos[g_ballindex-1];
					g_balldir.Normalize();
					g_ballindex=-1;
				}
				else
				{
					g_ballpos = g_ballpos + g_balldir * leftlen;
					g_balldir = g_pos[g_ballindex+1]-g_pos[g_ballindex];
					g_balldir.Normalize();
				}
				g_ballspeed1-=leftlen;
			}
		}
		else
		{
			g_balldir = g_pos[0]-g_pos[g_ballindex];
			g_balldir.Normalize();
			g_ballindex=-1;
		}
	}

	float tmp = g_predir.dotMul(g_balldir) / (g_balldir.len() * g_predir.len());
	if (tmp > 1)
	{
		tmp = 1;
	}
	if (tmp < -1)
	{
		tmp = -1;
	}
	float angle_g = acosf(tmp);
	angle_g = angle_g * 180 / acosf(-1);
	if (angle_g > 10)
	{
		cout << angle_g << endl;
		g_n = floor(angle_g) / 3;
		for(int i = 1; i < g_n; i++){
			g_t[i - 1] = i * 1.0 / g_n;
		}
		g_prevQua = g_predir.ToEuler().ToQuaternion();
		g_curQua = g_balldir.ToEuler().ToQuaternion();
		g_prevQua.Normalize();
		g_curQua.Normalize();
		g_prevQua.Slerp(g_curQua, g_n - 1, g_t, g_result);
		g_isSlerp = true;
		g_count = 0;
	}
	else
	{g_isSlerp = false;}
}

/*画机器人*/
void DrawRobot(int type)
{
	float size=0.5;
	//头

	glColor3f(1,0,0);
	glPushMatrix();
	glTranslatef(0,0,0);
	glScalef(0.4,0.6,0.4);
	glutSolidCube(size);
	glPopMatrix();
	//身子
	glColor3f(1,0,0);
	glPushMatrix();
	glTranslatef(0,-size,0);
	glScalef(0.8,1,0.8);
	glutSolidCube(size);
	glPopMatrix();

	//胳膊
	glColor3f(0,1,0);
	glPushMatrix();
	glTranslatef(0,-size*0.7,-size*0.7);
	if(type==0)
		glRotatef(-45,0,0,1);
	else
		glRotatef(45,0,0,1);
	glTranslatef(0,-size*0.5,0);
	glScalef(0.2,1,0.2);
	glutSolidCube(size);
	glPopMatrix();
	//胳膊
	glColor3f(0,1,0);
	glPushMatrix();
	//glTranslatef(size*0.7,-size*0.7,0);
	glTranslatef(0,-size*0.7,size*0.7);
	if(type==0)
		glRotatef(45,0,0,1);
	else
		glRotatef(-45,0,0,1);
	glTranslatef(0,-size*0.5,0);
	glScalef(0.2,1,0.2);
	glutSolidCube(size);
	glPopMatrix();

	//腿
	glColor3f(0,0,1);
	glPushMatrix();
	glTranslatef(0,-size*1.5,-size*0.2);
	if(type==0)
		glRotatef(10,0,0,1);
	else
		glRotatef(-10,0,0,1);
	glTranslatef(0,-size*0.5,0);
	glScalef(0.2,1,0.2);
	glutSolidCube(size);
	glPopMatrix();
	//腿
	glColor3f(0,0,1);
	glPushMatrix();
	glTranslatef(0,-size*1.5,size*0.2);
	if(type==0)
		glRotatef(-10,0,0,1);
	else
		glRotatef(10,0,0,1);
	glTranslatef(0,-size*0.5,0);
	glScalef(0.2,1,0.2);
	glutSolidCube(size);
	glPopMatrix();
}

void RenderWorld()
{
	static int type=0;
	float b = 0.0;
	g_iCurFrame++;
	 glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//
	glPushMatrix();
	/*设置初始位置*/
	// glTranslatef(0,0,-25);
	// glRotatef(g_angle,0,1,0);


	/*控制机器人方向的向量，v2是机器人头的朝向*/
	CVector068 v1,v2,v3;
	v1.Set(0,0,1);
	v3.Set(0,1,0);
	v2 = v1.crossMul(g_balldir);
	float a = (v3.x*v2.x+v3.y*v2.y)/(sqrt(pow(v3.x,2)+pow(v3.y,2))*sqrt(pow(v2.x,2)+pow(v2.y,2)));
	b = 180/3.14*acosf(a);
	if(change == 1){
	  //glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		if(g_isSlerp)
		{
			CVector068 pos = g_ballpos + g_result[g_count].ToEuler().ToVector068(&v2)*robotspeed;
			gluLookAt(pos.x,pos.y,pos.z,g_prepos.x,g_prepos.y,g_prepos.z,v2.x,v2.y,v2.z);
		}
		else{
			CVector068 pos = g_ballpos + g_balldir*robotspeed;
			if (g_balldir.x > 0)
			{
				v2.x = -1 * g_balldir.y;
				v2.y = g_balldir.x;
				v2.z = 0;
			}
			else if (g_balldir.x < 0)
			{
				v2.x = g_balldir.y;
				v2.y = -1 * g_balldir.x;
				v2.z = 0;
			}
			else
			{
				v2.z = g_balldir.y;
				v2.y = 0;
			}
			gluLookAt(pos.x,pos.y,pos.z,g_ballpos.x,g_ballpos.y,g_ballpos.z,v2.x,v2.y,v2.z);
		}
	}

	//glPushMatrix();
	if(g_iCurFrame%20==0) type = 1-type;
	//glTranslatef(g_ballpos.x,g_ballpos.y,g_ballpos.z);
	// if(v2.x<0)
	// {
	// 	glRotatef(b,0,0,1);
	// }
	// else glRotatef(-b,0,0,1);
	// glPopMatrix();
	glPushMatrix();
	if (g_isSlerp)
	{
		glTranslatef(g_prepos.x,g_prepos.y,g_prepos.z);
		CEuler dir = g_result[g_count++].ToEuler();
		glRotatef(dir.h, 0, 1, 0);
		glRotatef(dir.p, 1, 0, 0);
		glRotatef(dir.b, 0, 0, 1);
	}
	else
	{
		glTranslatef(g_ballpos.x,g_ballpos.y,g_ballpos.z);
		CEuler dir = g_balldir.ToEuler();
		glRotatef(dir.h, 0, 1, 0);
		glRotatef(dir.p, 1, 0, 0);
		glRotatef(dir.b, 0, 0, 1);
	}

	DrawRobot(type);
	glPopMatrix();

	if(g_mode==0)
	{
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glColor3f(0.5,0.4,0.1);
		for(int i=0;i<POINTNUM;i++)
		{
			CVector068 dir;
			float rotang = 0;
			dir = g_pos[(i+1)%POINTNUM]-g_pos[i];
			dir.Normalize();//
			rotang = acos(dir.x)*180/3.14;
			if(dir.y<0) rotang = -rotang;

			glPushMatrix();
			glTranslatef(g_pos[i].x,g_pos[i].y,g_pos[i].z);
			glRotatef(rotang,0,0,1);
			glBegin(GL_LINE_STRIP);
			for(int j=0;j<CIRCLENUM;j++)
				glVertex3fv(g_circle[j]);
			glEnd();
			glPopMatrix();
		}
	}
	else if(g_mode==1)
	{
		int midlast = POINTNUM/2-1;//
		CMatrix068 mat;
		float lastrotang = 0;

		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glBegin(GL_TRIANGLE_STRIP);

		for(int i=0;i<POINTNUM-1;i++)
		{
			if(i==2 || i==6 || i==18 || i==25 ||i==32|| i==34 || i==36
			 ||i==46||i==56||i==66||i==76 || i==85 || i==94 || i==123 || i==124
			 ||i==100||i==104)//
			{
				glEnd();
				glColor4f(0.05,0.05,0.05,0.5);
				glBegin(GL_TRIANGLE_STRIP);
			}
			else
			{
				glColor3f(0.5,0.4,0.1);
			}
			for(int j=0;j<CIRCLENUM;j++)
			{
				int index1 = i*CIRCLENUM+j;
				int index2 = index1+CIRCLENUM;
				glVertex3fv(g_allpos[index1]);
				glVertex3fv(g_allpos[index2]);
			}
		}
		glEnd();
	}

	glPopMatrix();
}

/*刷新函数*/
void myTimerFunc(int val)
{
	if (!g_isSlerp)
	{
		update();
	}
	if (g_count >= g_n - 1)
	{
		g_isSlerp = false;
		g_n = 0;
		g_count = 0;
	}
	myDisplay();
	glutTimerFunc(10,myTimerFunc,0);
}

void SetView()
{
	if (change==0) {
		if(mode==0)
		{
			glLoadMatrixf(g_EyeMat);
		}
		else
		{
			glRotatef(-rz,0,0,1);
			glRotatef(-rx,1,0,0);
			glRotatef(-ry,0,1,0);
			glTranslatef(-mx,-my,-mz);
		}
	}

	if (pers2==1)
	{
		CVector068 dis = g_ballpos - g_prepos;
		if (mode == 0)
		{
			glPushMatrix();
			glLoadIdentity();
			glMultMatrixf(g_EyeMat);
			if (!g_isSlerp) {
			glTranslatef(-dis.x, -dis.y, -dis.z);
			}
			glGetFloatv(GL_MODELVIEW_MATRIX, g_EyeMat);
			glPopMatrix();
			glLoadMatrixf(g_EyeMat);
		}
		else
		{
			if(!g_isSlerp)
			{
				mx += dis.x;
				my += dis.y;
				mz += dis.z;
		  }
			glLoadIdentity();
			glRotatef(-rz,0,0,1);
			glRotatef(-rx,1,0,0);
			glRotatef(-ry,0,1,0);
			glTranslatef(-mx,-my,-mz);
		}
	}
}


/*构建名字轨迹的函数*/
void SetRC()
{
	glShadeModel(GL_FLAT);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_BACK,GL_LINE);
	for (int i = 0; i < 16; i++) {
		 g_IEyeMat[i]=EyeMat[i];
		 g_EyeMat[i]=EyeMat[i];
	}

	//定义了一个圆的路径。
	for(int i=0; i<CIRCLENUM; i++)
	{
		float angle = i*2*3.14/(CIRCLENUM-1);
		g_circle[i].x = 0;
		g_circle[i].y = 1*cos(angle);
		g_circle[i].z = 1*sin(angle);
	}
	//初始化位置向量
	float R=2,seta=0;
	int midlast = POINTNUM/2-1;//第一段的最后一个点
	//初始化位置向量
	int j = 0;
	for(int i=0; i<3; i++)
	{
		g_pos[i][0] = -12+i;
		g_pos[i][1] = 3-i;
		g_pos[i][2] = 0;
	}

	for(int i=3; i<7; i++)
	{
		j = i-3;
		g_pos[i][0] = -13+j;
		g_pos[i][1] = -5+j;
		g_pos[i][2] = 0;
	}

	for(int i=7; i<10; i++)
	{
		j = i-7;
		g_pos[i][0] = -6 - j;
		g_pos[i][1] = 4 - j;
		g_pos[i][2] = 0;
	}

	for(int i=10; i<16; i++)
	{
		j = i-10;
		g_pos[i][0] = -8 + j;
		g_pos[i][1] = 1;
		g_pos[i][2] = 0;
	}

	for(int i=16; i<19; i++)
	{
		j = i-16;
		g_pos[i][0] = -4 + j;
		g_pos[i][1] = 3-j;
		g_pos[i][2] = 0;
	}

	for(int i=19; i<26; i++)
	{
		j = i-19;
		g_pos[i][0] = -8 + j;
		g_pos[i][1] = -2;
		g_pos[i][2] = 0;
	}

	for(int i=26; i<33; i++)
	{
		j = i-26;
		g_pos[i][0] = -8 + j;
		g_pos[i][1] = -5;
		g_pos[i][2] = 0;
	}

	for(int i=33; i<35; i++)
	{
		j = i-33;
		g_pos[i][0] = -8 ;
		g_pos[i][1] = -4+j;
		g_pos[i][2] = 0;
	}

	for(int i=35; i<37; i++)
	{
		j = i-35;
		g_pos[i][0] = -2;
		g_pos[i][1] = -4+j;
		g_pos[i][2] = 0;
	}

	for(int i=37; i<47; i++)
	{
		j = i-37;
		g_pos[i][0] = 1;
		g_pos[i][1] = 4-j;
		g_pos[i][2] = 0;
	}

	for(int i=47; i<57; i++)
	{
		j = i-47;
		g_pos[i][0] = 5;
		g_pos[i][1] = 4-j;
		g_pos[i][2] = 0;
	}

	for(int i=57; i<67; i++)
	{
		j = i-57;
		g_pos[i][0] = 8;
		g_pos[i][1] = 4-j;
		g_pos[i][2] = 0;
	}

	for(int i=67; i<77; i++)
	{
		j = i-67;
		g_pos[i][0] = 12;
		g_pos[i][1] = 4-j;
		g_pos[i][2] = 0;
	}

	for(int i=77; i<80; i++)
	{
		j = i-77;
		g_pos[i][0] = 2+j;
		g_pos[i][1] = 4;
		g_pos[i][2] = 0;
	}

	for(int i=80; i<83; i++)
	{
		j = i-80;
		g_pos[i][0] = 2+j;
		g_pos[i][1] = 1;
		g_pos[i][2] = 0;
	}

	for(int i=83; i<86; i++)
	{
		j = i-83;
		g_pos[i][0] = 2+j;
		g_pos[i][1] = -2;
		g_pos[i][2] = 0;
	}

	for(int i=86; i<89; i++)
	{
		j = i-86;
		g_pos[i][0] = 9+j;
		g_pos[i][1] = 4;
		g_pos[i][2] = 0;
	}

	for(int i=89; i<92; i++)
	{
		j = i-89;
		g_pos[i][0] = 9+j;
		g_pos[i][1] = 1;
		g_pos[i][2] = 0;
	}

	for(int i=92; i<95; i++)
	{
		j = i-92;
		g_pos[i][0] = 9+j;
		g_pos[i][1] = -2;
		g_pos[i][2] = 0;
	}

	for (int i=95;i<97;i++)
	{
		j = i-95;
		g_pos[i][0] = 17-j;
		g_pos[i][1] = 6-j;
		g_pos[i][2] = 0;
	}

	for (int i=97;i<101;i++)
	{
		j = i-97;
		g_pos[i][0] = 15;
		g_pos[i][1] = 4-j;
		g_pos[i][2] = 0;
	}

	for (int i=101;i<105;i++)
	{
		j = i-101;
		g_pos[i][0] = 19;
		g_pos[i][1] = 4-j;
		g_pos[i][2] = 0;
	}

	for (int i=105;i<109;i++)
	{
		j = i-105;
		g_pos[i][0] = 15+j;
		g_pos[i][1] = 4;
		g_pos[i][2] = 0;
	}

	for (int i=109;i<116;i++)
	{
		j = i-109;
		g_pos[i][0] = 15+j;
		g_pos[i][1] = 0;
		g_pos[i][2] = 0;
	}

	for (int i=116;i<121;i++)
	{
		j = i-116;
		g_pos[i][0] = 21;
		g_pos[i][1] = -1-j;
		g_pos[i][2] = 0;
	}

	for (int i=121;i<124;i++)
	{
		j = i-120;
		g_pos[i][0] = 21-j;
		g_pos[i][1] = -5;
		g_pos[i][2] = 0;
	}

	for (int i=124;i<125;i++)
	{
		g_pos[i][0] = 17;
		g_pos[i][1] = 2;
		g_pos[i][2] = 0;
	}

	for (int i=125;i<129;i++)
	{
		j = i-125;
		g_pos[i][0] = 15+j;
		g_pos[i][1] = -2;
		g_pos[i][2] = 0;
	}

	CMatrix068 mat;
	for(int i=0; i<POINTNUM; i++)
	{
		CVector068 dir;
		float rotang = 0;
		if(i!=POINTNUM-1&&i!=midlast)
		{
			dir = g_pos[(i+1)%POINTNUM]-g_pos[i];
		}
		else
		{
			dir = g_pos[i] - g_pos[(i+POINTNUM-1)%POINTNUM];
		}
		dir.Normalize();//方向
		rotang = acos(dir.x);
		if(dir.y<0) rotang = -rotang;
		mat.SetRotate(rotang,2);//设置为旋转矩阵。
		mat[12] = g_pos[i].x;	//设置平移部分。
		mat[13] = g_pos[i].y;
		mat[14] = g_pos[i].z;
		for(int j=0;j<CIRCLENUM;j++)
		{
			int index = i*CIRCLENUM+j;
			g_allpos[index] = mat.posMul(g_circle[j]);
		}
	}

	g_ballpos = g_pos[0];
	g_balldir = g_pos[1]-g_pos[0];
	g_balldir.Normalize();
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0, 0, -25);
	glMultMatrixf(g_EyeMat);
	glGetFloatv(GL_MODELVIEW_MATRIX, g_EyeMat);
	glPopMatrix();

}
/*接受按键的函数*/
void myKeyboardFunc(unsigned char key,int x, int y)
{
	bool bChange=false;
	switch(key)
	{
	case 'w':
		//my+=mspeed;
		if (change==1)
		{
			break;
		}
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0,-mspeed,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			mx+=g_IEyeMat[4]*mspeed;
			my+=g_IEyeMat[5]*mspeed;
			mz+=g_IEyeMat[6]*mspeed;
		}
		break;
	case 's':
		//my-=mspeed;
		if (change==1)
		{
			break;
		}
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0,mspeed,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			mx-=g_IEyeMat[4]*mspeed;
			my-=g_IEyeMat[5]*mspeed;
			mz-=g_IEyeMat[6]*mspeed;
		}

		break;
	case 'a':
		//mx-=mspeed;
		if (change==1)
		{
			break;
		}
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(mspeed,0,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			mx-=g_IEyeMat[0]*mspeed;
			my-=g_IEyeMat[1]*mspeed;
			mz-=g_IEyeMat[2]*mspeed;
		}

		break;
	case 'd':
		if (change==1)
		{
			break;
		}
		//mx+=mspeed;
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(-mspeed,0,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			mx+=g_IEyeMat[0]*mspeed;
			my+=g_IEyeMat[1]*mspeed;
			mz+=g_IEyeMat[2]*mspeed;
		}

		break;
	case 'q':
		if (change==1)
		{
			robotspeed+=0.3;
			break;
		}
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0,0,mspeed);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			mx-=g_IEyeMat[8]*mspeed;
			my-=g_IEyeMat[9]*mspeed;
			mz-=g_IEyeMat[10]*mspeed;
		}
		//mz-=mspeed;

		break;
	case 'e':
		if (change==1)
		{
			robotspeed-=0.3;
			break;
		}
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0,0,-mspeed);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			mx+=g_IEyeMat[8]*mspeed;
			my+=g_IEyeMat[9]*mspeed;
			mz+=g_IEyeMat[10]*mspeed;
		}
		//mz+=mspeed;

		break;
	case 'i':
		if (change==1)
		{
			break;
		}
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glRotatef(-rspeed,1,0,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			rx+=rspeed;
			bChange = true;
		}
		break;
	case 'k':
		if (change==1)
		{
			break;
		}
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glRotatef(rspeed,1,0,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			rx-=rspeed;
			bChange = true;
		}

		break;
	case 'j':
		if (change==1)
		{
			break;
		}
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glRotatef(-rspeed,0,1,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			ry+=rspeed;
			bChange = true;
		}

		break;
	case 'l':
		if (change==1)
		{
			break;
		}
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glRotatef(rspeed,0,1,0);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			ry-=rspeed;
			bChange = true;
		}

		break;
	case 'u':
		if (change==1)
		{
			break;
		}
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glRotatef(rspeed,0,0,1);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			rz+=rspeed;
			bChange = true;
		}

		break;
	case 'o':
		if (change==1)
		{
			break;
		}
		if(mode==0)
		{
			glPushMatrix();
			glLoadIdentity();
			glRotatef(-rspeed,0,0,1);
			glMultMatrixf(g_EyeMat);
			glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
			glPopMatrix();
		}
		else
		{
			rz-=rspeed;
			bChange = true;
		}

		break;
	case '1':
		change=1-change;
		break;
	case '2':
		pers2=1-pers2;
		break;
	case '3':
		mode=1;
		printf("mode:%d\n",mode);
		break;
	case '4':
		mode=0;
		glPushMatrix();
		glLoadIdentity();
		glRotatef(-rz,0,0,1);
		glRotatef(-rx,1,0,0);
		glRotatef(-ry,0,1,0);
		glTranslatef(-mx,-my,-mz);
		glGetFloatv(GL_MODELVIEW_MATRIX,g_EyeMat);
		glPopMatrix();
		printf("mode:%d\n",mode);
		break;
	case ']':
		mspeed*=1.1;
		printf("mspeed:%.1f\n",mspeed);
		break;
	case '[':
		mspeed*=0.9;
		printf("mspeed:%.1f\n",mspeed);
		break;
	case '{':
		rspeed*=1.1;
		printf("rspeed:%.1f\n",rspeed);
		break;
	case '}':
		rspeed*=0.9;
		printf("rspeed:%.1f\n",rspeed);
		break;
	case ' ':
		g_mode=1-g_mode;
		break;
	case '-':
	case '_':
		g_ballspeed-=0.01;
		break;
	case '+':
	case '=':
		g_ballspeed+=0.01;
		break;
	}
	if(bChange)//计算视点矩阵的逆矩阵
	{
		glPushMatrix();
		glLoadIdentity();
		glRotatef(ry,0,1,0);
		glRotatef(rx,1,0,0);
		glRotatef(rz,0,0,1);
		glGetFloatv(GL_MODELVIEW_MATRIX,g_IEyeMat);
		glPopMatrix();
	}
}

/*显示每个点*/
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	SetView();
	RenderWorld();
	glPopMatrix();
	glutSwapBuffers();
}


/*刷新显示窗口的函数*/
void myReshape(int w,int h)
{
	GLfloat nRange = 100.0f;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,GLfloat(w)/h,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*主函数*/
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE| GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("第一个OpenGL程序");
	glutDisplayFunc(&myDisplay);
	glutTimerFunc(1,myTimerFunc,0);
	glutReshapeFunc(&myReshape);
	glutKeyboardFunc(&myKeyboardFunc);
	SetRC();
	glutMainLoop();
	return 0;
}
