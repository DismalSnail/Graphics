#include "stdafx.h"

using namespace std;

int main()
{

	float num[10];
	num[0]=0.5;
	float *t=num;
	float n=1;
	CQuaternion CQ[10];
	CQuaternion *list=CQ;
	CQuaternion CQU1,CQU2,CQU3;
	//float Array[16]={0.99,0.08,-0.14,0,-0.03,0.94,0.35,0,0.16,-0.34,0.93,0,0,0,0,1};
	//CVEA.Set(10,20,5);
	//CMA.Set(Array);
	//CEulerA.Set(650,-400,500);
	//CEulerA.Normal();
	CQU1.Set(0.11,0.33,0.55,0.76);
	CQU2.Set(0.2,0.41,0.76,0.46);
	//CQU1=CQU1.Normalize();
	//CQU2=CQU2.Normalize();
	CQU1.Slerp(CQU2,n,t,list);
	//num=CQU1.dotMul(CQU2);
	//CQU1.GetAngle(angle,dir);
	//CEulerA=CQU.ToEuler();
	/*for (int i=0;i<16;i++)
	{
		cout<<CMA[i]<<" ";
	}*/
	//cout<<angle<<" "<<dir.x<<" "<<dir.y<<" "<<dir.z<<endl;
	//CEulerA=CVEA.ToEuler();
	//cout<<CVEA.x<<" "<<CVEA.y<<" "<<CVEA.z<<endl;
	//cout<<dir.x<<" "<<dir.y<<" "<<dir.z<<endl;
	//cout<<CEulerA.h<<" "<<CEulerA.p<<" "<<CEulerA.b<<endl;
	for (int i=0;i<n;i++)
	{
		cout<<list[i].x<<" "<<list[i].y<<" "<<list[i].z<<" "<<list[i].w<<endl;
	}
	//cout<<CQU3.x<<" "<<CQU3.y<<" "<<CQU3.z<<" "<<CQU3.w<<endl;
	system("PAUSE");
	return 0;
};