#include "StdAfx.h"
#include "MyOpenGl.h"


static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
bool robotspeed=false;
float seta = 0;

CMyOpenGL::CMyOpenGL(void)
{
	g_mode = 0;
	g_angle = 0 ;
	g_ballspeed=0.1;//球速度
	g_iCurFrame=0;
	g_old_ballspeed=0;
	g_ballindex=0;
	look=0;
	look2=0;
	mode=1;
	ACBD=0;
	SL=false;//机器人转身时的控制量
	EYElen=0;
	bx=0;
	rerobot=0;
	for (int i=0;i<25;i++)
	{
		mykey[i]=false;
	}
	g_updir.Set(0,0,0);
	g_rightdir.Set(0,0,0);
}


CMyOpenGL::~CMyOpenGL(void)
{
}

bool CMyOpenGL::wenli()
{
	FILE *File=NULL;
	resource_path[0] = "image.bmp";
	resource_path[1] = "image2.bmp";
	AUX_RGBImageRec* TextureImage[2];
	//装载图像文件资源   
	for (int i=0;i<2;i++)
	{
		if ((TextureImage[i]=auxDIBImageLoad(resource_path[i]))!=NULL)
		{
			if (i==0)
			{
				glGenTextures(1, &texture[0]);					// Create The Texture
				glBindTexture(GL_TEXTURE_2D, texture[0]);
			}
			else
			{
				glGenTextures(1, &Texture[0]);					// Create The Texture
				glBindTexture(GL_TEXTURE_2D, Texture[0]);
			}
			// Generate The Texture
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[i]->sizeX, TextureImage[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[i]->data);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering

			if (TextureImage[i]->data)					// If Texture Image Exists
				free(TextureImage[i]->data);				// Free The Texture Image Memory
			free(TextureImage[i]);						// Free The Image Structure
		}					// Free The Image Structure
	}
	return true;
}

int CMyOpenGL::robotpos(CVector068 pos)
{
	CVector068 poslong;
	float longmin=1000000;
	int posmin=0;
	for(int i=0;i<129;i++)
	{
		poslong=pos-g_pos[i];
		if (longmin>poslong.len())
		{
			longmin=poslong.len();
			posmin=i;
		}
	}
	return posmin;
}

void CMyOpenGL::update()//场景更新。
{
	float speed;
	int UP_KEY=0;
	bool OK=false;
	CVector068 g_x;
	if(g_ballspeed>=0)
		speed=g_ballspeed;
	else
		speed=-g_ballspeed;
	if (mykey[0])
	{
		if(robotspeed)
		{
			robotspeed=false;
			g_oldballdir=g_balldir;
			g_balldir.x=0-g_balldir.x;
			g_balldir.y=0-g_balldir.y;
			g_balldir.z=0-g_balldir.z;
		}
		g_ballpos=g_ballpos+g_balldir*speed;
		glPushMatrix();
		glLoadIdentity();		
		glRotatef(-g_balldir.ToEuler().b,0,0,1);	
		glRotatef(-g_balldir.ToEuler().p,1,0,0);
		glRotatef(-g_balldir.ToEuler().h,0,1,0);
		glTranslatef(-g_ballpos.x,-g_ballpos.y,-g_ballpos.z);
		glGetFloatv(GL_MODELVIEW_MATRIX,f_pos);
		glPopMatrix();
		return ;
	}
	if(bx>=1&&g_ballindex==rerobot)
	{
		g_ballspeed=0;
		return ;
	}
	while(!UP_KEY)
	{
		if(g_ballspeed>=0)
		{
			if(g_ballindex<128)
			{
				float leftlen = (g_pos[g_ballindex+1] - g_ballpos).len();
				g_oldballdir=g_balldir;
				//g_oldballdir.Normalize();
				g_balldir = g_pos[g_ballindex+1]-g_ballpos;
				g_balldir.Normalize();
				g_x=g_balldir-g_oldballdir;
				if(g_x.len()>0.05)
					OK=true;
				if(OK)
				{
					UP_KEY=1;
				}
				if(leftlen>=speed)
				{
					g_oldballpos=g_ballpos;
					g_ballpos = g_ballpos + g_balldir * speed;
					break;
				}
				else
				{		
					g_ballindex++;
					if(g_ballindex>=128)
					{
						g_oldballpos=g_ballpos;
						g_ballpos =g_ballpos + g_balldir * leftlen;
						g_oldballdir=g_balldir;
						//g_oldballdir.Normalize();
						g_balldir = g_pos[0]-g_pos[g_ballindex-1];
						g_balldir.Normalize();
						g_x=g_balldir-g_oldballdir;
						if(g_x.len()>0.05)
							OK=true;
						if(OK)
						{
							UP_KEY=1;
						}
						g_ballindex=-1;
					}
					else
					{
						g_oldballpos=g_ballpos;
						g_ballpos = g_ballpos + g_balldir * leftlen;
						g_oldballdir=g_balldir;
						//g_oldballdir.Normalize();
						g_balldir = g_pos[g_ballindex+1]-g_pos[g_ballindex];
						g_balldir.Normalize();
						g_x=g_balldir-g_oldballdir;
						if(g_x.len()>0.05)
							OK=true;
						if(OK)
						{
							UP_KEY=1;
						}
					}	
					speed-=leftlen;
				}
			}
			else
			{
				g_oldballdir=g_balldir;
				//g_oldballdir.Normalize();
				g_balldir = g_pos[0]-g_pos[g_ballindex];
				g_balldir.Normalize();
				g_x=g_balldir-g_oldballdir;
				if(g_x.len()>0.05)
					OK=true;
				if(OK)
				{
					UP_KEY=1;
				}
				g_ballindex=-1;
			}
		}
		else
		{
			if(g_ballindex>0)
			{
				float leftlen = (g_pos[g_ballindex-1] - g_ballpos).len();
				g_oldballdir=g_balldir;
				//g_oldballdir.Normalize();
				g_balldir = g_pos[g_ballindex-1]-g_ballpos;
				g_balldir.Normalize();
				g_x=g_balldir-g_oldballdir;
				if(g_x.len()>0.05)
					OK=true;
				if(OK)
				{
					UP_KEY=1;
				}
				if(leftlen>=speed)
				{
					g_oldballpos=g_ballpos;
					g_ballpos = g_ballpos + g_balldir * speed;
					break;
				}
				else
				{		
					g_ballindex--;
					if(g_ballindex<0)
					{
						g_oldballpos=g_ballpos;
						g_ballpos = g_ballpos + g_balldir * leftlen;
						g_oldballdir=g_balldir;
						//g_oldballdir.Normalize();
						g_balldir = g_pos[128]-g_pos[g_ballindex+1];
						g_balldir.Normalize();
						g_x=g_balldir-g_oldballdir;
						if(g_x.len()>0.05)
							OK=true;
						if(OK)
						{
							UP_KEY=1;
						}
						g_ballindex=-1;
					}
					else if(g_ballindex==0)
					{
						g_oldballpos=g_ballpos;
						g_ballpos = g_ballpos + g_balldir * leftlen;
						if(g_balldir.len()!=0)
							g_oldballdir=g_balldir;
						//g_oldballdir.Normalize();
						g_balldir = g_pos[128]-g_pos[g_ballindex];
						g_balldir.Normalize();
						g_x=g_balldir-g_oldballdir;
						if(g_x.len()>0.05)
							OK=true;
						if(OK)
						{
							UP_KEY=1;
						}
						g_ballindex=-1;
					}
					else
					{
						g_oldballpos=g_ballpos;
						g_ballpos = g_ballpos + g_balldir * leftlen;
						if(g_balldir.len()!=0)
							g_oldballdir=g_balldir;
						//g_oldballdir.Normalize();
						g_balldir = g_pos[g_ballindex-1]-g_pos[g_ballindex];
						g_balldir.Normalize();
						g_x=g_balldir-g_oldballdir;
						if(g_x.len()>0.05)
							OK=true;
						if(OK)
						{
							UP_KEY=1;
						}
					}	
					speed-=leftlen;
				}
			}
			else
			{
				if(g_balldir.len()!=0)
					g_oldballdir=g_balldir;
				//g_oldballdir.Normalize();
				g_balldir = g_pos[128]-g_pos[g_ballindex];
				g_balldir.Normalize();
				g_x=g_balldir-g_oldballdir;
				if(g_x.len()>0.05)
					OK=true;
				if(OK)
				{
					UP_KEY=1;
				}
				g_ballindex=129;
			}
		}
	}
}

void CMyOpenGL::SetRC()
{
	//定义了一个圆的路径。
	for(int i=0; i<20; i++)
	{
		float angle = i*2*3.14/(19);
		g_circle[i].x = 0;
		g_circle[i].y = 0.8*cos(angle);
		g_circle[i].z = 0.8*sin(angle);
	}
	//初始化位置向量
	int i=0;
	//四
	//定义了一个圆的路径。
	for(int i=0; i<129; i++)
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
		if(i!=128)
		{
			dir = g_pos[(i+1)%129]-g_pos[i];				
		}
		else
		{
			dir = g_pos[i] - g_pos[(i+129-1)%129];				
		}
		dir.Normalize();//方向
		rotang = acos(dir.x);
		if(dir.y<0) rotang = -rotang;
		if(dir.y==0||i==37||i==66||i==78||i==85||i==105||i==108||i==111||i==52)
			mat.SetRotate(rotang,1);//设置为旋转矩阵。
		else
			mat.SetRotate(rotang,2);
		mat[12] = g_pos[i].x;	//设置平移部分。
		mat[13] = g_pos[i].y;
		mat[14] = g_pos[i].z;
		for(int j=0;j<20;j++)
		{
			int index = i*20+j;
			g_allpos[index] = mat.posMul(g_circle[j]);
		}
	}
	g_oldballpos=g_ballpos;
	g_ballpos = g_pos[0];
	g_balldir = g_pos[1]-g_pos[0];
	g_balldir.Normalize();
	glEnable(GL_DEPTH_TEST);
	wenli();
	/*glClearColor(1,1,1,1);
	glShadeModel(GL_FLAT);
	glFrontFace(GL_CCW);*/

	//glEnable(GL_DEPTH_TEST);
	float amb[4]={0.3,0.0,0.0,1};					//红色环境光
	//	float amb[4]={0.0,0.0,0.0,1};
	float dif[4]={1.0,1.0,1.0,1};					//白色漫射光和反射光
	//	float dif[4]={0.0,0.0,0.0,1};					//白色漫射光和反射光
	float spe[4]={1.0,1.0,1.0,1};
	glLightfv(GL_LIGHT0,GL_AMBIENT,amb);			
	glLightfv(GL_LIGHT0,GL_DIFFUSE,dif);
	glLightfv(GL_LIGHT0,GL_SPECULAR,spe);
	float aamb[4]={0.3,0.0,0.0,1};
	//	float amb[4]={0.0,0.0,0.0,1};
	float ddif[4]={0.0,1.0,0.0,1};					//白色漫射光和反射光
	//	float dif[4]={0.0,0.0,0.0,1};					//白色漫射光和反射光
	float sspe[4]={1.0,1.0,1.0,1};
	//glLightfv(GL_LIGHT1,GL_AMBIENT,aamb);			
	glLightfv(GL_LIGHT1,GL_DIFFUSE,ddif);
	glLightfv(GL_LIGHT1,GL_SPECULAR,sspe);
	glEnable( GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
}

void CMyOpenGL::DrawRobot(int type)
{
	GLfloat lightPos[] = {0.0f, 0.0f, 0.0f, 1.0f},lightdir[3]= {0.0f, 0.0f, 1.0f};
	if(type==1||type==0)
	{
		float size=0.4;
		//头
		
		glPushMatrix();
		glColor3f(1,1,0);
		glTranslatef(0,0,0.4);
		glLightfv(GL_LIGHT1,GL_POSITION,lightPos);
		glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,45.0);
		glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,lightdir);
		//glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,2.0);
		glScalef(1,1,1);
		glutSolidCube(size*0.7);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glColor3f(1,1,1);
		glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(-1.0f, -1.0f); glVertex3f(-0.14f, -0.14f,  0.18f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, -1.0f); glVertex3f(0.14f, -0.14f,  0.18f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0.14f, 0.14f,  0.18f);	// Top Right Of The Texture and Quad
		glTexCoord2f(-1.0f, 1.0f); glVertex3f(-0.14f, 0.14f,  0.18f);	// Top Left Of The Texture and Quad
		glEnd();
		glDisable(GL_TEXTURE_2D);
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
	else if(type==4)
	{
		float size=0.4;
		//头
		glPushMatrix();
		glColor3f(1,1,0);
		glTranslatef(0,0,0.4*(1-bx));
		glTranslatef(0,-0.4*bx,0);
		glScalef(1,1,1);
		glLightfv(GL_LIGHT1,GL_POSITION,lightPos);
		glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,45.0);
		glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,lightdir);
		//glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,2.0);
		glutSolidCube(size*0.7*(1-bx));
		glPopMatrix();

		//机头
		glPushMatrix();
		glColor3f(10,1,0);
		glTranslatef(0,0,0.4*bx);
		glTranslatef(0,-size,0);
		glScalef(1,1,1);
		glutSolidCone(0.2*bx,0.3,30,30);
		glPopMatrix();

		//机舱
		glPushMatrix();
		glColor3f(10,10,0);
		glTranslatef(0,0.2*bx,0);
		glTranslatef(0,-size,0);
		glScalef(1,1,2);
		glutSolidSphere(0.2*bx,30,30);
		glPopMatrix();

		//身子
		glColor3f(1,0,0);
		glPushMatrix();
		glTranslatef(0,-size,0);
		glScalef(1,0.5+0.5*bx,2);
		glutSolidCube(size);
		glPopMatrix();

		//胳膊
		glColor3f(0,1,1);
		glPushMatrix();
		glTranslatef(-size*0.7,-size*0.9,0.4);
		glTranslatef(0,-size*0.5*(1-bx),0);
		glScalef(0.2,1,0.2);
		glutSolidCube(size-0.4*bx);
		glPopMatrix();

		//胳膊
		glColor3f(0,1,0);
		glPushMatrix();
		glTranslatef(size*0.7,-size*0.9,0.4);
		glTranslatef(0,-size*0.5*(1-bx),0);
		glScalef(0.2,1,0.2);
		glutSolidCube(size-0.4*bx);
		glPopMatrix();

		//胳膊
		glColor3f(0,1,0);
		glPushMatrix();
		glTranslatef(size*0.7,-size*0.9,-0.4);
		glTranslatef(0,-size*0.5*(1-bx),0);
		glScalef(0.2,1,0.2);
		glutSolidCube(size-0.4*bx);
		glPopMatrix();

		//胳膊
		glColor3f(0,1,1);
		glPushMatrix();
		glTranslatef(-size*0.7,-size*0.9,-0.4);
		glTranslatef(0,-size*0.5*(1-bx),0);
		glScalef(0.2,1,0.2);
		glutSolidCube(size-0.4*bx);
		glPopMatrix();

		//机翼
		glColor3f(10,5,10);
		glPushMatrix();
		glTranslatef(0,-size,0);
		glScalef(0.5+3.5*bx,0.3,1);
		glutSolidCube(size*bx);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, Texture[0]);
		glColor3f(1,1,1);
		glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-(size*bx/8)*(0.5+3.5*bx), 0.23,  -(size*bx/2));	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f((size*bx/8)*(0.5+3.5*bx), 0.23,  -(size*bx/2));	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f((size*bx/8)*(0.5+3.5*bx), 0.23,  (size*bx/2));	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-(size*bx/8)*(0.5+3.5*bx), 0.23,  (size*bx/2));	// Top Left Of The Texture and Quad
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		//喷火器
		glColor3f(0,1,1);
		glPushMatrix();
		glTranslatef(-size*0.2,0,-0.4-bx*0.1);
		glTranslatef(0,-size,0);
		glutSolidCube(0.1*bx);
		glPopMatrix();

		glColor3f(10,1,0);
		glPushMatrix();
		glTranslatef(size*0.2,0,-0.4-bx*0.1);
		glTranslatef(0,-size,0);
		glutSolidCube(0.1*bx);
		glPopMatrix();
	}
}

void CMyOpenGL::PostInit(void)
{
	CVector068 CVT1,CVT2;
	CVT1.Set(0,0,10);
	CVT2.Set(0,0,0);
	//glClearColor(0,0,0.5,1);
	m_pCamere->SetCamera(CVT1,CVT2,true);
	m_pCamere->SaveCamera();
	m_pControl->SetSpeed(0.1,0.1);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	SetRC();
}

void CMyOpenGL::InDraw(void)
{
	CVector068 SEYE;
	CMatrix068 GEYE;
	CEuler KEYE;
	seta+=1;
	if(look)
	{
		CVector068 pos = g_ballpos + g_balldir*(-EYElen);
		KEYE=g_balldir.ToEuler();
		m_pCamere->m_pos.x=pos.z;
		m_pCamere->m_pos.y=pos.y;
		m_pCamere->m_pos.z=-pos.x;
		m_pCamere->m_hpr=KEYE;
		m_pCamere->m_hpr.h+=90;
		m_pCamere->m_hpr.Normal();
		glPushMatrix();
		glLoadIdentity();		
		glRotatef(-m_pCamere->m_hpr.b,0,0,1);	
		glRotatef(-m_pCamere->m_hpr.p,1,0,0);
		glRotatef(-m_pCamere->m_hpr.h,0,1,0);
		glTranslatef(-m_pCamere->m_pos.x,-m_pCamere->m_pos.y,-m_pCamere->m_pos.z);
		glGetFloatv(GL_MODELVIEW_MATRIX,m_pCamere->g_eye);
		glPopMatrix();
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(0,0,-m_pCamere->QZ);
		glMultMatrixf(m_pCamere->g_eye);
		glGetFloatv(GL_MODELVIEW_MATRIX,m_pCamere->g_eye);
		glPopMatrix();
		GEYE=m_pCamere->g_eye.GetInverse();
		m_pCamere->m_pos.x=GEYE.m03;
		m_pCamere->m_pos.y=GEYE.m13;
		m_pCamere->m_pos.z=GEYE.m23;
	}
	else if(look2&&!SL)
	{
		SEYE=g_ballpos-g_oldballpos;
		m_pCamere->m_pos.x+=SEYE.z;
		m_pCamere->m_pos.y+=SEYE.y;
		m_pCamere->m_pos.z+=SEYE.x;
		glPushMatrix();
		glLoadIdentity();		
		glRotatef(-m_pCamere->m_hpr.b,0,0,1);	
		glRotatef(-m_pCamere->m_hpr.p,1,0,0);
		glRotatef(-m_pCamere->m_hpr.h,0,1,0);
		glTranslatef(-m_pCamere->m_pos.x,-m_pCamere->m_pos.y,-m_pCamere->m_pos.z);
		glGetFloatv(GL_MODELVIEW_MATRIX,m_pCamere->g_eye);
		glPopMatrix();
	}
	static int type=0;
	g_iCurFrame++;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	glRotatef(90,0,1,0);
	
	glColor3f(0.8,0,0);
	glPushMatrix();
	//绘制光源，用一个小红球代替
	glPushMatrix();
	//glRotatef(seta,0,1,0);	//绕(1,1,1)方向旋转变换
	glTranslatef(-20,0,0);	//光源距离球心20米的地方
	glColor3f(1,0,0);		//红色小球
	glutSolidSphere(0.5,20,20);	//绘制小球
	float pos[4]={0,0,0,1},lightdir[]={0,-1,0};
	glLightfv(GL_LIGHT0,GL_POSITION,pos);	//设置光源位置
	//glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,lightdir);
	glPopMatrix();
	glTranslatef(g_ballpos.x,g_ballpos.y,g_ballpos.z);
	//if(g_oldballdir!=g_balldir)
	{
		CVector068 saxi;
		saxi.Set(0,1,0);
		CEuler Gball1;
		if(ACBD>2)
		{
			SL=true;
			ACBD--;
			Gball1=Result[25-ACBD].ToEuler();
			abd=Gball1;
			abd.Normal();
			g_oldballdir=g_balldir;
			g_balldir=Gball1.ToVector068(&saxi);
		}
		else
		{
			if(SL)
			{
				g_oldballdir=g_balldir;
				g_balldir=g_Nballdir;
			}
			SL=false; 
			ACBD=0;
			Gball1=g_balldir.ToEuler();
			abd=Gball1;
		}
	}
	abd.Normal();
	glRotatef(abd.h-180,0,1,0);
	glRotatef(abd.p,-1,0,0);
	glRotatef(abd.b,0,0,-1);
	if(!mykey[0]&&bx<=0)
	{
		if(g_iCurFrame%5==0) type = 1-type;
		DrawRobot(type);
		//glRotatef(90,0,1,0);
	}
	else
	{
		DrawRobot(4);
	}
	
	//glRotatef(90,0,1,0);
	glPopMatrix();
	if(g_mode==0)
	{
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glColor3f(0.5,0.4,0.1);	
		for(int i=0;i<129;i++)
		{
			CVector068 dir;
			dir = g_pos[(i+1)%129]-g_pos[i];		
			dir.Normalize();//方向
			glPushMatrix();
			glTranslatef(g_pos[i].x,g_pos[i].y,g_pos[i].z);
			if(dir.y==2 || i==6 || i==18 || i==25 ||i==32|| i==34 || i==36
				||i==46||i==56||i==66||i==76 || i==85 || i==94 || i==123 || i==124
				||i==100||i==104)
				glRotatef(90,0,1,0);
			else
				glRotatef(90,0,0,1);
			glBegin(GL_LINE_STRIP);		
			for(int j=0;j<20;j++)
				glVertex3fv(g_circle[j]);
			glEnd();
			glPopMatrix();

		}
	}
	else if(g_mode==1)
	{		
		CMatrix068 mat;

		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glBegin(GL_TRIANGLE_STRIP);
		for(int i=0;i<128;i++)
		{
			CVector068 dir;
			dir = g_pos[(i+1)%129]-g_pos[i];	
			if(sqrt((g_pos[i].y-g_pos[i+1].y)*(g_pos[i].y-g_pos[i+1].y)+(g_pos[i].z-g_pos[i+1].z)*(g_pos[i].z-g_pos[i+1].z))>sqrt(2.0))//第一笔画结束，第二笔画开始
			{
				glEnd();
				glColor4f(0.1,0.1,0.1,0.5);
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
	//glutSwapBuffers();
}

bool CMyOpenGL::OnKey(unsigned int nChar, bool bDown)
{
	CMatrix068 robotx;
	if(bDown)
		switch(nChar){
		case ' ':
			g_mode=1-g_mode;
			break;
		case '1':
			m_pControl->m_keyStatus[m_pControl->KS_MODE_1]=true;
			mykey[1]=true;
			if(mykey[2])
				mykey[2]=false;
			if(look==0)
			{
				m_pCamere->QZ=0;
				EYElen=(g_ballpos-m_pCamere->m_pos).len();
				m_pCamere->m_pos.x=0;m_pCamere->m_pos.y=0;m_pCamere->m_pos.z=0;
				m_pCamere->m_hpr.b=0;m_pCamere->m_hpr.h=0;m_pCamere->m_hpr.p=0;
				m_pCamere->g_ieye.Set(m_pCamere->m_viewMatrix);
				m_pCamere->g_eye.Set(m_pCamere->m_viewMatrix);
				look=1;
				if(look2==1)
					look2=0;
			}
			else
			{
				look=0;
				mykey[1]=false;
				m_pControl->m_keyStatus[m_pControl->KS_MODE_1]=false;
			}
			break;
		case '2':
			mykey[2]=true;
			if(mykey[1])
			{
				mykey[1]=false;
				m_pControl->m_keyStatus[m_pControl->KS_MODE_1]=false;
			}
			if(look2==0)
			{
				look2=1;
				if(look==1)
				{
					look=0;
				}
			}
			else
			{
				look2=0;
				mykey[2]=false;
			}
			break;
		case '3':
			if(mode==0)
			{
				CMatrix068 yeye;
				yeye=m_pCamere->g_eye.GetInverse();
				m_pCamere->m_pos.x=yeye.m03;
				m_pCamere->m_pos.y=yeye.m13;
				m_pCamere->m_pos.z=yeye.m23;
				m_pCamere->m_hpr=yeye.ToEuler();
			}
			mode = 1;
			m_pCamere->m_type=0;
			break;
		case '4':
			if(mode==1)
			{
				glPushMatrix();
				glLoadIdentity();		
				glRotatef(-m_pCamere->m_hpr.b,0,0,1);	
				glRotatef(-m_pCamere->m_hpr.p,1,0,0);
				glRotatef(-m_pCamere->m_hpr.h,0,1,0);
				glTranslatef(-m_pCamere->m_pos.x,-m_pCamere->m_pos.y,-m_pCamere->m_pos.z);
				glGetFloatv(GL_MODELVIEW_MATRIX,m_pCamere->g_eye);
				glPopMatrix();
			}
			mode = 0;
			m_pCamere->m_type=1;
			break;
		case '6':
			mykey[0]=false;
			mykey[5]=true;
			rerobot=robotpos(g_ballpos);
			g_ballindex=rerobot-1;
			if(g_ballindex<0)
				g_ballindex=128;
			break;
		case '5':
			mykey[0]=true;
			g_old_ballspeed=g_ballspeed;
			g_ballspeed=0;
			glPushMatrix();
			glLoadIdentity();		
			glRotatef(-g_balldir.ToEuler().b,0,0,1);	
			glRotatef(-g_balldir.ToEuler().p,1,0,0);
			glRotatef(-g_balldir.ToEuler().h,0,1,0);
			glTranslatef(-g_ballpos.x,-g_ballpos.y,-g_ballpos.z);
			glGetFloatv(GL_MODELVIEW_MATRIX,f_pos);
			glPopMatrix();
			if (g_balldir.z>0)
			{
				g_rightdir.Set(1,0,0);
			}
			else if (g_balldir.z<0)
			{
				g_rightdir.Set(-1,0,0);
			}
			else
			{
				if (g_balldir.y>0)
				{
					g_rightdir.Set(-1,0,0);
				} 
				else if (g_balldir.y<0)
				{
					g_rightdir.Set(1,0,0);
				}
				else
					g_rightdir.Set(0,0,0);
			}
			g_updir=g_rightdir.crossMul(g_balldir);
			break;
		case '-':
		case 189:
			if (g_old_ballspeed>0)
			{
				robotspeed=true;
			}
			g_old_ballspeed=g_ballspeed;
			g_ballspeed-=0.1;
			break;
		case '=':
		case 187:
			if (g_old_ballspeed<0)
			{
				robotspeed=true;
			}
			g_old_ballspeed=g_ballspeed;
			g_ballspeed+=0.1;
			break;
		case 38:
			robotx.SetRotate(-1,g_rightdir);
			g_oldballdir=g_balldir;
			g_balldir=robotx.vecMul(g_balldir);
			g_updir=robotx.vecMul(g_updir);
			break;
		case 40:
			robotx.SetRotate(1,g_rightdir);
			g_oldballdir=g_balldir;
			g_balldir=robotx.vecMul(g_balldir);
			g_updir=robotx.vecMul(g_updir);
			break;
		case 37:
			robotx.SetRotate(-1,g_updir);
			g_oldballdir=g_balldir;
			g_balldir=robotx.vecMul(g_balldir);
			break;
		case 39:
			robotx.SetRotate(1,g_updir);
			g_oldballdir=g_balldir;
			g_balldir=robotx.vecMul(g_balldir);
			break;
	}
	return false;
}
