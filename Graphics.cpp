#include "stdafx.h"
#include "Vector068.h"
#include "math.h"
#include "Matrix068.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include "targetver.h"

using namespace std;

vector<float> nums;

/*ï¿½Ö´Êºï¿½ï¿½ï¿½*/
void prostr(string data)
{
	char *s_string = (char *)data.c_str();
	const char * split = "	 ,";
	char *p = strtok(s_string,split);
	float num;
	while (p != NULL)
	{
		sscanf(p,"%f",&num);
		nums.push_back(num);
		p=strtok(NULL,split);
	}
}


int main()
{

	float Array_A[16]={0.0};
	float Array_B[16]={0.0};

	CVector068 CVector068_A;
	CVector068 CVector068_B;
	CMatrix068 CMatrix068_A;
	CMatrix068 CMatrix068_B;
	CMatrix068 CMatrix068_C;



	string matrix_Mul="¾ØÕóÏà³Ë";
	string matrix_vecMul="¾ØÕó³ËÏòÁ¿";
	string matrix_posMul="¾ØÕó³ËÎ»ÖÃ";
	string matrix_SetRotate="¾ØÕóÉèÖÃĞı×ª";
	string matrix_SetTrans="¾ØÕóÉèÖÃÆ½ÒÆ";
	string matrix_SetScale="¾ØÕóÉèÖÃËõ·Å";
	string martix_GetInverse="¾ØÕóÇóÄæ";

	ifstream fin("test.txt");
	ofstream out("Myout.txt");
	string s;
	string data;

	while(getline(fin,s))
	{
		if (s == matrix_Mul)
		{
			out << matrix_Mul <<"\n";
			getline(fin,data);
			//out << data;
			prostr(data);
			for (int i = 0; i < 32; i++) {
				if (i==31 || i==15) {
					out<<setiosflags(ios::fixed)<<setprecision(2)<<nums[i]<<" ";
				} else {
					out<<setiosflags(ios::fixed)<<setprecision(2)<<nums[i]<<",";
				}
			}

			for (int i = 0; i < 16; i++) {
				Array_A[i]=nums[i];
			}
			for (int i = 16; i < 32; i++) {
				Array_B[i-16]=nums[i];
			}
			CMatrix068_A.Set(Array_A);
			CMatrix068_B.Set(Array_B);
			nums.clear();
			CMatrix068_C=CMatrix068_A*CMatrix068_B;
			out << setiosflags(ios::fixed) << setprecision(2)<<CMatrix068_C.m00<<","<<CMatrix068_C.m10<<","<<CMatrix068_C.m20<<","<<CMatrix068_C.m30 << ",";
			out << setiosflags(ios::fixed) << setprecision(2)<<CMatrix068_C.m01<<","<<CMatrix068_C.m11<<","<<CMatrix068_C.m21<<","<<CMatrix068_C.m31 << ",";
			out << setiosflags(ios::fixed) << setprecision(2)<<CMatrix068_C.m02<<","<<CMatrix068_C.m12<<","<<CMatrix068_C.m22<<","<<CMatrix068_C.m32 << ",";
			out << setiosflags(ios::fixed) << setprecision(2)<<CMatrix068_C.m03<<","<<CMatrix068_C.m13<<","<<CMatrix068_C.m23<<","<<CMatrix068_C.m33 << "\n";
		}

		if (s == matrix_vecMul)
		{
			out << matrix_vecMul <<"\n";
			getline(fin,data);
			//out << data;
			prostr(data);
			for (int i = 0; i < 19; i++) {
				if (i==15 || i==18) {
					out<<setiosflags(ios::fixed)<<setprecision(2)<<nums[i]<<" ";
				} else {
					out<<setiosflags(ios::fixed)<<setprecision(2)<<nums[i]<<",";
				}
			}

			for (int i = 0; i < 16; i++) {
				Array_A[i]=nums[i];
			}
			CVector068_A.Set(nums[16],nums[17],nums[18]);
			CMatrix068_A.Set(Array_A);
			nums.clear();
			CVector068_B=CMatrix068_A.vecMul(CVector068_A);
			out << setiosflags(ios::fixed) << setprecision(2)<<CVector068_B.x<<","<<CVector068_B.y<<","<<CVector068_B.z<< "\n";
		}

		if (s == matrix_posMul)
		{
			out << matrix_posMul <<"\n";
			getline(fin,data);
			//out << data;
			prostr(data);
			for (int i = 0; i < 19; i++) {
				if (i==31 || i==18) {
					out<<setiosflags(ios::fixed)<<setprecision(2)<<nums[i]<<" ";
				} else {
					out<<setiosflags(ios::fixed)<<setprecision(2)<<nums[i]<<",";
				}
			}

			for (int i = 0; i < 16; i++) {
				Array_A[i]=nums[i];
			}
			CVector068_A.Set(nums[16],nums[17],nums[18]);
			CMatrix068_A.Set(Array_A);
      CVector068_B=CMatrix068_A.posMul(CVector068_A);
			nums.clear();
			CMatrix068_C=CMatrix068_A*CMatrix068_B;
			out << setiosflags(ios::fixed) << setprecision(2)<<CVector068_B.x<<","<<CVector068_B.y<<","<<CVector068_B.z<< "\n";
		}

		if (s == matrix_SetRotate)
		{
			out << matrix_SetRotate <<"\n";
			getline(fin,data);
			//out << data;
			prostr(data);
			for (int i = 0; i < 4; i++) {
				if (i==0 || i==4) {
					out<<setiosflags(ios::fixed)<<setprecision(2)<<nums[i]<<" ";
				} else {
					out<<setiosflags(ios::fixed)<<setprecision(2)<<nums[i]<<",";
				}
			}
			float seta=nums[0];
			CVector068_A.Set(nums[1],nums[2],nums[3]);
			nums.clear();
			CMatrix068_C.SetRotate(seta,CVector068_A);
			out << setiosflags(ios::fixed) << setprecision(2)<<CMatrix068_C.m00<<","<<CMatrix068_C.m10<<","<<CMatrix068_C.m20<<","<<CMatrix068_C.m30 << ",";
			out << setiosflags(ios::fixed) << setprecision(2)<<CMatrix068_C.m01<<","<<CMatrix068_C.m11<<","<<CMatrix068_C.m21<<","<<CMatrix068_C.m31 << ",";
			out << setiosflags(ios::fixed) << setprecision(2)<<CMatrix068_C.m02<<","<<CMatrix068_C.m12<<","<<CMatrix068_C.m22<<","<<CMatrix068_C.m32 << ",";
			out << setiosflags(ios::fixed) << setprecision(2)<<CMatrix068_C.m03<<","<<CMatrix068_C.m13<<","<<CMatrix068_C.m23<<","<<CMatrix068_C.m33 << "\n";
		}

		if (s == matrix_SetTrans)
		{
			out << matrix_SetTrans <<"\n";
			getline(fin,data);
			prostr(data);
			for (int i = 0; i < 3; i++) {
				if (i==0 || i==2) {
					out<<setiosflags(ios::fixed)<<setprecision(2)<<nums[i]<<" ";
				} else {
					out<<setiosflags(ios::fixed)<<setprecision(2)<<nums[i]<<",";
				}
			}
			CVector068_A.Set(nums[0],nums[1],nums[2]);
			nums.clear();
			CMatrix068_C.SetTrans(CVector068_A);
			for (int i = 0; i < 16; i++) {
				if (i == 15) {
					out<<setiosflags(ios::fixed)<<setprecision(2)<<CMatrix068_C[i]<<"\n";
				}else{
					out<<setiosflags(ios::fixed)<<setprecision(2)<<CMatrix068_C[i]<<",";
				}
			}
		}

		if (s == matrix_SetScale)
		{
			out << matrix_SetScale <<"\n";
			getline(fin,data);
			prostr(data);
			for (int i = 0; i < 3; i++) {
				if (i==0 || i==2) {
					out<<setiosflags(ios::fixed)<<setprecision(2)<<nums[i]<<" ";
				} else {
					out<<setiosflags(ios::fixed)<<setprecision(2)<<nums[i]<<",";
				}
			}
			CVector068_A.Set(nums[0],nums[1],nums[2]);
			nums.clear();
			CMatrix068_C.SetScale(CVector068_A);
			for (int i = 0; i < 16; i++) {
				if (i == 15) {
					out<<setiosflags(ios::fixed)<<setprecision(2)<<CMatrix068_C[i]<<"\n";
				}else{
					out<<setiosflags(ios::fixed)<<setprecision(2)<<CMatrix068_C[i]<<",";
				}
			}
		}
		 if (s == martix_GetInverse)
		 {
		 	out << martix_GetInverse <<"\n";
		 	getline(fin,data);
		 	prostr(data);
		 	for (int i = 0; i < 16; i++) {
		 		if (i==15) {
		 			out<<setiosflags(ios::fixed)<<setprecision(2)<<nums[i]<<" ";
		 		} else {
		 			out<<setiosflags(ios::fixed)<<setprecision(2)<<nums[i]<<",";
		 		}
		 	}
		
		 	for (int i = 0; i < 16; i++) {
		 		Array_A[i]=nums[i];
		 	}
			CMatrix068_A.Set(Array_A);
			CMatrix068_C=CMatrix068_A.GetInverse();
		 	nums.clear();
			for (int i = 0; i < 16; i++) {
				if (i == 15) {
					out<<setiosflags(ios::fixed)<<setprecision(2)<<CMatrix068_C[i]<<" ";
				}else{
					out<<setiosflags(ios::fixed)<<setprecision(2)<<CMatrix068_C[i]<<",";
				}
			}
		 }

	}
	fin.close();
	out.close();
	return 0;
}
