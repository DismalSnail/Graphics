// 001.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Vector068.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include <GL/glut.h>
#include <iostream>
using namespace std;
void myDisplay(void);
int g_iCurFrame=0;
int g_mode = 0;
float g_angle = 0 ;
#define POINTNUM 129

CVector068 g_pos[POINTNUM];
CVector068 g_ballpos,g_balldir;//球的位置和方向

float g_ballspeed = 0.06;//球的速度
float g_ballspeed1 = 0;
int g_ballindex;//当前球所在的曲线节点位置

void update()
{	

	g_ballspeed1 = abs(g_ballspeed);
	if(g_ballspeed < 0)//速度为负
		{
			if(g_ballindex>0)
			{
				float leftlen = (g_pos[g_ballindex-1] - g_ballpos).len();
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
	cout << g_ballpos.x<<" "<< g_ballpos.y <<" "<<g_ballpos.z << endl;
	cout << g_ballspeed1 <<endl;
}

/*刷新函数*/
void myTimerFunc(int val)
{
	g_angle+=0.01;
	update();
	myDisplay();
	glutTimerFunc(1,myTimerFunc,1);
}

/*构建名字轨迹的函数*/
void SetRC()
{
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

	g_ballpos = g_pos[0];
	g_balldir = g_pos[1]-g_pos[0];
	g_balldir.Normalize();
	glEnable(GL_DEPTH_TEST);
}
/*接受按键的函数*/
void myKeyboardFunc(unsigned char key,int x, int y)
{
	switch(key)
	{
	case '+':
		g_ballspeed+=0.03;
		break;
	case '-':
		g_ballspeed -= 0.03;
		break;
	case '1':
		g_ballpos = g_pos[0];
		g_balldir = g_pos[1]-g_pos[0];
		g_balldir.Normalize();
		g_ballindex=0;
		break;
	}
}

/*填充轨迹上每个点的函数*/
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(0,0,-20);
	glRotatef(g_angle,0,1,0);
	glColor3f(0.8,0,0);

	glPushMatrix();
	glTranslatef(g_ballpos.x,g_ballpos.y,g_ballpos.z);
	glutSolidSphere(0.5,36,36);
	glPopMatrix();
	glColor3f(0.5,0.4,0.1);
	for(int i=0;i<POINTNUM;i++)
	{
		glPushMatrix();
		glTranslatef(g_pos[i].x,g_pos[i].y,g_pos[i].z);
		glutWireSphere(1,4,2);
		glPopMatrix();
	}
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
    glutInitWindowSize(400, 400);
    glutCreateWindow("第一个OpenGL程序");
    glutDisplayFunc(&myDisplay);
	glutTimerFunc(1,myTimerFunc,2);
	glutReshapeFunc(&myReshape);
	glutKeyboardFunc(&myKeyboardFunc);
	SetRC();
    glutMainLoop();
    return 0;
}
