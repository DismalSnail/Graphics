// glCamera.cpp: implementation of the Camera068 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Camera068.h"
#include "gl\glut.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Camera068::Camera068()
{
	Init();
}

void Camera068::Init()
{
	m_type=0;
	m_pos=CVector068(0,0,0);	
	m_eyedir=CVector068(0,0,-1);
	m_updir=CVector068(0,1,0);
	m_hpr = CVector068(0,0,0);
	int i;
	for(i=0;i<16;i++)
	{
		if(i==0||i==5||i==10||i==15)
		{
			m_viewMatrix[i]=1;
			m_viewMatrixSave[i]=1;
		}
		else
		{
			m_viewMatrixSave[i]=0;
			m_viewMatrix[i]=0;
		}
	}
}

Camera068::~Camera068()
{

}

void Camera068::Move(int dir, double len)//dir=0表示左右移，dir=1表示上下移，dir=2表示前后移
{
	if(m_type==0)
	{
		CVector068 mov;
		if(dir==0)
		{
			mov.Set(&m_viewMatrixInverse[0]);
		}
		else if(dir==1)
		{
			mov.Set(&m_viewMatrixInverse[4]);
		}
		else if(dir==2)
		{
			mov.Set(&m_viewMatrixInverse[8]);
		}
		m_pos+=mov*len;
	}
	else if(m_type==1)
	{
		glPushMatrix();
		glLoadIdentity();
		if(dir==0)
			glTranslatef(-len,0,0);
		else if(dir==1)
			glTranslatef(0,-len,0);
		else
			glTranslatef(0,0,-len);
		glMultMatrixd(m_viewMatrix);
		glGetDoublev(GL_MODELVIEW_MATRIX,m_viewMatrix);
		CglMath::InverseMatrix(m_viewMatrix,m_viewMatrixInverse);
		glPopMatrix();
		m_pos = &m_viewMatrixInverse[12];
	}
}

void Camera068::Rotate(int dir, double len)//dir=0表示左右转，dir=1表示上下转，dir=2表示滚动转
{
	if(m_type==0)
	{
		m_hpr[dir]+=len;
	}
	else if(m_type==1)
	{
		glPushMatrix();
		glLoadIdentity();
		if(dir==0)		
			glRotated(-len,0,1,0);	//h
		else if(dir==1)
			glRotated(-len,1,0,0);	//p
		else
			glRotated(-len,0,0,1);	//r
		glMultMatrixd(m_viewMatrix);
		glGetDoublev(GL_MODELVIEW_MATRIX,m_viewMatrix);
		CglMath::InverseMatrix(m_viewMatrix,m_viewMatrixInverse);
		glPopMatrix();

		m_eyedir = m_viewMatrixInverse*CVector068(0,0,-1);
		m_eyedir -= m_pos;

		m_updir = m_viewMatrixInverse*CVector068(0,1,0);
		m_updir -= m_pos;
	}
}

void Camera068::ShowView()
{
	if(m_type==0)
	{
		glRotated(-m_hpr[2],0,0,1);	//r
		glRotated(-m_hpr[1],1,0,0);	//p
		glRotated(-m_hpr[0],0,1,0);	//h
		glTranslatef(-m_pos[0],-m_pos[1],-m_pos[2]);
	}
	else if(m_type==1)
	{
		gluLookAt(	m_pos.x,m_pos.y,m_pos.z,
			m_pos.x+m_eyedir.x,m_pos.y+m_eyedir.y,m_pos.z+m_eyedir.z,
			m_updir.x,m_updir.y,m_updir.z
			);
	}
	glGetDoublev(GL_MODELVIEW_MATRIX,m_viewMatrix);
	CglMath::InverseMatrix(m_viewMatrix,m_viewMatrixInverse);
}

void Camera068::SetCamera(const CVector068 &pos, const CVector068 &obj_dir, bool bObj,int type)
{		
	m_pos = pos;
	if(bObj)	//如果第二个参数是观察的对象位置
	{
		m_type = 1;
		m_eyedir = obj_dir - pos;
	}
	else if(m_type==0)	//第二个参数是观察的方向,水平漫游hpr
	{
		m_type = 0;
		m_hpr = obj_dir;
	}
	else if(m_type==1)	//第二个参数是观察的方向
	{
		m_type = 1;
		m_eyedir = obj_dir;
	}
	glPushMatrix();
	glLoadIdentity();
	ShowView();
	glPopMatrix();
	if(type>=0) m_type=type;
	CglMath::Dir2HPR(m_eyedir,m_updir,m_hpr);
}


void Camera068::SaveCamera()
{
	int i;
	for(i=0;i<16;i++)
	{
		m_viewMatrixSave[i]=m_viewMatrix[i];
	}
}

void Camera068::LoadCamera()
{
	int i;
	for(i=0;i<16;i++)
	{
		m_viewMatrix[i]=m_viewMatrixSave[i];
	}
	CglMath::InverseMatrix(m_viewMatrix,m_viewMatrixInverse);
	m_pos = m_viewMatrixInverse*CVector068(0,0,0);
	m_eyedir = m_viewMatrixInverse*CVector068(0,0,-1)-m_pos;
	m_updir = m_viewMatrixInverse*CVector068(0,1,0)-m_pos;
	CglMath::Dir2HPR(m_eyedir,m_updir,m_hpr);
}

void Camera068::SetType(int type)
{
	m_type=type;
	m_eyedir = m_viewMatrixInverse*CVector068(0,0,-1)-m_pos;
	m_updir = m_viewMatrixInverse*CVector068(0,1,0)-m_pos;
	CglMath::Dir2HPR(m_eyedir,m_updir,m_hpr);
}
