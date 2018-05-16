#include "StdAfx.h"
#include "MyOpenGL.h"
#include "iostream"
using namespace std;

CMyOpenGL::CMyOpenGL(void)
{
	flag=false;
	g_iCurFrame=0;
	g_mode=0;
	g_angle=0;
	g_n=0;
	g_count=0;
	g_ballindex=0;
	g_isSlerp=false;
	g_ballspeed=0.06;
	g_ballspeed1=0;
	change=0;
	mx=0;my=5;mz=10;rx=0;ry=0;rz=0;
	sx=1;sy=1;sz=1;
	mspeed=1;
	rspeed=1;
	for(int i=0;i<16;i++)
	{
		if(i==0||i==5||i==10||i==15)
		{
			g_IEyeMat[i]=1;
			g_EyeMat[i]=1;
			EyeMat[i]=1;
		}
		else
		{
			g_IEyeMat[i]=0;
			g_EyeMat[i]=0;
			EyeMat[i]=0;
		}
	}
	mode=0;
	pers2=0;
	robotspeed=-10.0;
}


CMyOpenGL::~CMyOpenGL(void)
{
}


void CMyOpenGL::PostInit(void)
{
	SetRC();
}

 
void CMyOpenGL::InDraw(void)
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
}


bool CMyOpenGL::OnKey(unsigned char nChar, bool  bDown)
{
	return false;
}

void CMyOpenGL::SetView()
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

void CMyOpenGL::update()
{
	//glutKeyboardUpFunc(&myKeyboardUpFunc);
	g_ballspeed1 = abs(g_ballspeed);
	if(g_ballspeed < 0)//速度小于0
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
					g_balldir = g_pos[128]-g_pos[g_ballindex+1];
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
			g_balldir = g_pos[128]-g_pos[g_ballindex];
			g_balldir.Normalize();
			g_ballindex=128;
		}
	}
	else
	{
		if(g_ballindex<128)
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
				if(g_ballindex>=128)
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

void CMyOpenGL::DrawRobot( int type )
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

void CMyOpenGL::RenderWorld()
{
	static int type=0;
	float b = 0.0;
	g_iCurFrame++;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//
	glPushMatrix();

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
		for(int i=0;i<129;i++)
		{
			CVector068 dir;
			float rotang = 0;
			dir = g_pos[(i+1)%129]-g_pos[i];
			dir.Normalize();//
			rotang = acos(dir.x)*180/3.14;
			if(dir.y<0) rotang = -rotang;

			glPushMatrix();
			glTranslatef(g_pos[i].x,g_pos[i].y,g_pos[i].z);
			glRotatef(rotang,0,0,1);
			glBegin(GL_LINE_STRIP);
			for(int j=0;j<20;j++)
				glVertex3fv(g_circle[j]);
			glEnd();
			glPopMatrix();
		}
	}
	else if(g_mode==1)
	{
		int midlast = 129/2-1;//
		CMatrix068 mat;
		float lastrotang = 0;

		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glBegin(GL_TRIANGLE_STRIP);

		for(int i=0;i<128;i++)
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
			for(int j=0;j<20;j++)
			{
				int index1 = i*20+j;
				int index2 = index1+20;
				glVertex3fv(g_allpos[index1]);
				glVertex3fv(g_allpos[index2]);
			}
		}
		glEnd();
	}

	glPopMatrix();
}

void CMyOpenGL::SetRC()
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

	//定义了一个圆的路径
	for(int i=0; i<20; i++)
	{
		float angle = i*2*3.14/(19);
		g_circle[i].x = 0;
		g_circle[i].y = 1*cos(angle);
		g_circle[i].z = 1*sin(angle);
	}
	//初始化位置向量
	float R=2,seta=0;
	int midlast = 129/2-1;//第一段的最后一个点
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
	for(int i=0; i<129; i++)
	{
		CVector068 dir;
		float rotang = 0;
		if(i!=128&&i!=midlast)
		{
			dir = g_pos[(i+1)%129]-g_pos[i];
		}
		else
		{
			dir = g_pos[i] - g_pos[(i+128)%129];
		}
		dir.Normalize();//方向
		rotang = acos(dir.x);
		if(dir.y<0) rotang = -rotang;
		mat.SetRotate(rotang,2);//设置为旋转矩阵
		mat[12] = g_pos[i].x;	//设置平移部分
		mat[13] = g_pos[i].y;
		mat[14] = g_pos[i].z;
		for(int j=0;j<20;j++)
		{
			int index = i*20+j;
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

void CMyOpenGL::myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	SetView();
	RenderWorld();
	glPopMatrix();
}
