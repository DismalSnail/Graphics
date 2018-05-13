// glCamera.h: interface for the Camera068 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLCAMERA_H__090064F1_F0BF_4146_A666_5CC6841483C2__INCLUDED_)
#define AFX_GLCAMERA_H__090064F1_F0BF_4146_A666_5CC6841483C2__INCLUDED_
#include "Vector068.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Camera068  
{
public:
	void SetType(int type);
	void LoadCamera();
	void SaveCamera();
	void Init();
	void SetCamera(const CVector068& pos, const CVector068& obj_dir,bool bObj=true,int type=0);
	void ShowView();
	void Rotate(int dir,double len);
	void Move(int dir,double len);
	Camera068();
	virtual ~Camera068();
	CVector068 m_pos;	//�ӵ㵱ǰλ��
	CVector068 m_hpr;	//�ӵ㷽��ǣ�xΪh,yΪp,zΪr
	CVector068 m_eyedir;//���߷���
	CVector068 m_updir;	//�Ϸ�����
	double m_viewMatrix[16];	//��ͼ����
	double m_viewMatrixInverse[16];	//��ͼ����������
	double m_viewMatrixSave[16];	//�������ͼ����
	int m_type;//	������͡�0��ʾ��������(hpr�ۻ�)��1��ʾ�������Σ�2��ʾ��������
};

#endif // !defined(AFX_GLCAMERA_H__090064F1_F0BF_4146_A666_5CC6841483C2__INCLUDED_)
