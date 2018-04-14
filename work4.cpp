#include "stdafx.h"

using namespace std;

int main()
{
	CEuler CEulerA;
	CVector068 dir;
	float angle;
	CVector068 CVEA;
	CQuaternion CQU1,CQU2,CQU3;
	CMatrix068 CMA;
	//float Array[16]={0.99,0.08,-0.14,0,-0.03,0.94,0.35,0,0.16,-0.34,0.93,0,0,0,0,1};
	//CVEA.Set(10,20,5);
	//CMA.Set(Array);
	//CEulerA.Set(650,-400,500);
	//CEulerA.Normal();
	CQU1.Set(4,6,6,4);
	//CQU2.Set(5,4,3,1);
	//CQU3=CQU1+CQU2;
	//num=CQU1.dotMul(CQU2);
	CQU1.GetAngle(angle,dir);
	//CEulerA=CQU.ToEuler();
	/*for (int i=0;i<16;i++)
	{
		cout<<CMA[i]<<" ";
	}*/
	cout<<angle<<" "<<dir.x<<" "<<dir.y<<" "<<dir.z<<endl;
	//CEulerA=CVEA.ToEuler();
	//cout<<CVEA.x<<" "<<CVEA.y<<" "<<CVEA.z<<endl;
	//cout<<dir.x<<" "<<dir.y<<" "<<dir.z<<endl;
	//cout<<CEulerA.h<<" "<<CEulerA.p<<" "<<CEulerA.b<<endl;
	//cout<<CQU3.x<<" "<<CQU3.y<<" "<<CQU3.z<<" "<<CQU3.w<<endl;
	system("PAUSE");
	return 0;
};