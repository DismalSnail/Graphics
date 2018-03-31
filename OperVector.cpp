#include "stdafx.h"
#include "targetver.h"
#include "Vector068.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

vector<float> nums;

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
	CVector068 CVector068_A;
	CVector068 CVector068_B;
	CVector068 CVector068_C;
	
	string vector_dotMul="向量点乘";
	string vector_crossMul="向量叉乘";
	string vector_normalize="向量标准化";
	string vector_dotlen="向量求模";
	string vector_project="向量投影";
	string vector_add="向量相加";

	float result;

	ifstream fin("test.txt");
	ofstream out("Myout.txt");
	string s;
	string data;
	while(getline(fin,s))
	{
		if (s == vector_add)
		{
			out << vector_add <<"\n";
			getline(fin,data);
			out << data;
			prostr(data);
			CVector068_A.Set(nums[0],nums[1],nums[2]);
			CVector068_B.Set(nums[3],nums[4],nums[5]);
			nums.clear();
			CVector068_C = CVector068_A + CVector068_B;
			out <<"	";
			out<<setiosflags(ios::fixed)<<setprecision(2)<<CVector068_C.x<<",";
			out<<setiosflags(ios::fixed)<<setprecision(2)<<CVector068_C.y<<",";
			out<<setiosflags(ios::fixed)<<setprecision(2)<<CVector068_C.z<<"\n";
		}

		if (s == vector_dotMul)
		{
			out << vector_dotMul <<"\n";
			getline(fin,data);
			out << data;
			prostr(data);
			CVector068_A.Set(nums[0],nums[1],nums[2]);
			CVector068_B.Set(nums[3],nums[4],nums[5]);
			nums.clear();
			result = CVector068_A.dotMul(CVector068_B);
			out <<"	";
			out<<setiosflags(ios::fixed)<<setprecision(2)<<result<<"\n";
		}

		if (s == vector_dotlen)
		{
			out << vector_dotlen <<"\n";
			getline(fin,data);
			out << data;
			prostr(data);
			CVector068_A.Set(nums[0],nums[1],nums[2]);
			nums.clear();
			result = CVector068_A.len();
			out <<"	";
			out<<setiosflags(ios::fixed)<<setprecision(2)<<result<<"\n";
		}

		if (s == vector_normalize)
		{
			out << vector_normalize <<"\n";
			getline(fin,data);
			out << data;
			prostr(data);
			CVector068_A.Set(nums[0],nums[1],nums[2]);
			nums.clear();
			CVector068_A.Normalize();
			out <<"	";
			out<<setiosflags(ios::fixed)<<setprecision(2)<<CVector068_A.x<<",";
			out<<setiosflags(ios::fixed)<<setprecision(2)<<CVector068_A.y<<",";
			out<<setiosflags(ios::fixed)<<setprecision(2)<<CVector068_A.z<<"\n";
		}

		if (s == vector_crossMul)
		{
			out << vector_crossMul <<"\n";
			getline(fin,data);
			out << data;
			prostr(data);
			CVector068_A.Set(nums[0],nums[1],nums[2]);
			CVector068_B.Set(nums[3],nums[4],nums[5]);
			nums.clear();
			CVector068_C = CVector068_A.crossMul(CVector068_B);
			out <<"	";
			out<<setiosflags(ios::fixed)<<setprecision(2)<<CVector068_C.x<<",";
			out<<setiosflags(ios::fixed)<<setprecision(2)<<CVector068_C.y<<",";
			out<<setiosflags(ios::fixed)<<setprecision(2)<<CVector068_C.z<<"\n";
		}

		if (s == vector_project)
		{
			out << vector_add <<"\n";
			getline(fin,data);
			out << data;
			prostr(data);
			CVector068_A.Set(nums[0],nums[1],nums[2]);
			CVector068_B.Set(nums[3],nums[4],nums[5]);
			nums.clear();
			CVector068_C = CVector068_A.project(CVector068_B);
			out <<"	";
			out<<setiosflags(ios::fixed)<<setprecision(2)<<CVector068_C.x<<",";
			out<<setiosflags(ios::fixed)<<setprecision(2)<<CVector068_C.y<<",";
			out<<setiosflags(ios::fixed)<<setprecision(2)<<CVector068_C.z<<"\n";
		}

	}
	fin.close();
	out.close();
	return 0;
}