#include "stdafx.h"

using namespace std;

vector<float> nums;
ifstream fin("test.txt");
ofstream out("Myout.txt");

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

void outCEu(CEuler&ceu)
{
	out<<setiosflags(ios::fixed)<<setprecision(2)<<ceu.h<<","
		<<ceu.p<<","
		<<ceu.b<<"\n";
}

void outCMa(CMatrix068& cma)
{
	for (int i=0;i<16;i++)
	{
		if (i==15)
		{
			out<<setiosflags(ios::fixed)<<setprecision(2)<<cma[i]<<"\n";
		}
		else
		{
			out<<setiosflags(ios::fixed)<<setprecision(2)<<cma[i]<<",";

		}

	}
}

void outCQu(CQuaternion&cqu)
{
	out<<setiosflags(ios::fixed)<<setprecision(2)<<cqu.x<<","
		<<cqu.y<<","
		<<cqu.z<<","
		<<cqu.w<<"\n";
}


int main()
{
	CEuler ceu;
	CMatrix068 cma;
	CVector068 cve;
	CVector068 updir;
	CQuaternion cqu,cqu1;
	float ary[16];
	float sum;

	string s1="欧拉角转换向量",
				 s2="向量转换欧拉角",
				 s3="欧拉角转换四元数",
				 s4="四元数转换欧拉角",
				 s5="欧拉角转换矩阵",
				 s6="矩阵转换欧拉角",
				 s7="矩阵转换四元数",
				 s8="四元数转换矩阵",
				 s9="欧拉角标准化",
				 s10="四元数单位化",
				 s11="四元数相乘",
				 s12="四元数求差",
				 s13="四元数点乘",
				 s14="四元数求逆",
				 s15="四元数求角度和旋转轴",
				 s16="四元数插值";

	string s;
	string data;
	while(getline(fin,s))
	{
		if (s == s1)
		{
			out << s1 <<"\n";
			getline(fin,data);
			out <<data;
			prostr(data);
			ceu.Set(nums[0],nums[1],nums[2]);
			nums.clear();
			cve=ceu.ToVector068(&updir);
			out <<"    ";
			out<<setiosflags(ios::fixed)<<setprecision(2)<<cve.x<<","
														 <<cve.y<<","
														 <<cve.z<<"    ";
			out<<setiosflags(ios::fixed)<<setprecision(2)<<updir.x<<","
														 <<updir.y<<","
														 <<updir.z<<"\n";
		}
		
		 if (s == s2)
		 {
			 out << s2 <<"\n";
			 getline(fin,data);
			 out <<data;
			 prostr(data);
			 cve.Set(nums[0],nums[1],nums[2]);
			 nums.clear();
			 out <<"	";
			 ceu=cve.ToEuler();
			 out<<setiosflags(ios::fixed)<<setprecision(2)<<ceu.h<<","
														  <<ceu.p<<","
														  <<ceu.b<<"\n";
		 }
		 if (s == s3)
		 {
			 out << s3 <<"\n";
			 getline(fin,data);
			 out <<data;
			 prostr(data);
			 ceu.Set(nums[0],nums[1],nums[2]);
			 nums.clear();
			 out <<"	";
			 cqu=ceu.ToQuaternion();
			 out<<setiosflags(ios::fixed)<<setprecision(2)<<cqu.x<<","
				<<cqu.y<<","
				<<cqu.z<<","
				<<cqu.w<<"\n";
		 }
		
		 if (s == s4)
		 {
		 	out << s4 <<"\n";
		 	getline(fin,data);
		 	out << data;
		 	prostr(data);
		 	cqu.Set(nums[0],nums[1],nums[2],nums[3]);
		 	nums.clear();
		 	ceu=cqu.ToEuler();
		 	out <<"	";
			out<<setiosflags(ios::fixed)<<setprecision(2)<<ceu.h<<","
				<<ceu.p<<","
				<<ceu.b<<"\n";
		 }
		
		 if (s == s5)
		 {
			 out << s5 <<"\n";
			 getline(fin,data);
			 out << data;
			 prostr(data);
			 ceu.Set(nums[0],nums[1],nums[2]);
			 nums.clear();
			 cma=ceu.ToMatrix068();
			 out <<"	";
			 for (int i=0;i<16;i++)
			 {
				 if (i==15)
				 {
					 out<<setiosflags(ios::fixed)<<setprecision(2)<<cma[i]<<"\n";
				 }
				 else
				 {
					 out<<setiosflags(ios::fixed)<<setprecision(2)<<cma[i]<<",";

				 }

			 }

		 }
		
		 if (s == s6)
		 {
			 out << s6 <<"\n";
			 getline(fin,data);
			 out << data;
			 prostr(data);
			 for (int i=0;i<16;i++)
			 {
				 ary[i]=nums[i];
			 }
			 cma.Set(ary);
			 nums.clear();
			 ceu=cma.ToEuler();
			 out <<"	";
			 out<<setiosflags(ios::fixed)<<setprecision(2)<<ceu.h<<","
				 <<ceu.p<<","
				 <<ceu.b<<"\n";
		 }

		  if (s == s7)
		  {
			  out << s7 <<"\n";
			  getline(fin,data);
			  out << data;
			  prostr(data);
			  for (int i=0;i<16;i++)
			  {
				  ary[i]=nums[i];
			  }
			  cma.Set(ary);
			  nums.clear();
			  cqu=cma.ToQuaternion();
			  out <<"	";
			  out<<setiosflags(ios::fixed)<<setprecision(2)<<cqu.x<<","
				  <<cqu.y<<","
				  <<cqu.z<<","
				  <<cqu.w<<"\n";
		  }

		  if (s == s8)
		  {
			  out << s8 <<"\n";
			  getline(fin,data);
			  out << data;
			  prostr(data);
			  cqu.Set(nums[0],nums[1],nums[2],nums[3]);
			  nums.clear();
			  cma=cqu.ToMatrix();
			  out <<"	";
			  for (int i=0;i<16;i++)
			  {
				  if (i==15)
				  {
					  out<<setiosflags(ios::fixed)<<setprecision(2)<<cma[i]<<"\n";
				  }
				  else
				  {
					  out<<setiosflags(ios::fixed)<<setprecision(2)<<cma[i]<<",";

				  }

			  }
		  }

		  if (s == s9)
		  {
			  out << s9 <<"\n";
			  getline(fin,data);
			  out << data;
			  prostr(data);
			  ceu.Set(nums[0],nums[1],nums[2]);
			  nums.clear();
			  ceu.Normal();
			  out <<"	";
			  out<<setiosflags(ios::fixed)<<setprecision(2)<<ceu.h<<","
				  <<ceu.p<<","
				  <<ceu.b<<"\n";
		  }

		  if (s == s10)
		  {
			  out << s10 <<"\n";
			  getline(fin,data);
			  out << data;
			  prostr(data);
			  cqu.Set(nums[0],nums[1],nums[2],nums[3]);
			  nums.clear();
			  cqu.Normalize();
			  out <<"	";
			  out<<setiosflags(ios::fixed)<<setprecision(2)<<cqu.x<<","
				  <<cqu.y<<","
				  <<cqu.z<<","
				  <<cqu.w<<"\n";
		  }

		  if (s == s11)
		  {
			  out << s11 <<"\n";
			  getline(fin,data);
			  out << data;
			  prostr(data);
			  cqu.Set(nums[0],nums[1],nums[2],nums[3]);
			  cqu1.Set(nums[4],nums[5],nums[6],nums[7]);
			  nums.clear();
			  cqu=cqu*cqu1;
			  out <<"	";
			  outCQu(cqu);
		  }

		  if (s == s12)
		  {
			  out << s12 <<"\n";
			  getline(fin,data);
			  out << data;
			  prostr(data);
			  cqu.Set(nums[0],nums[1],nums[2],nums[3]);
			  cqu1.Set(nums[4],nums[5],nums[6],nums[7]);
			  nums.clear();
			  cqu=cqu.Div(cqu1);
			  out <<"	";
			  outCQu(cqu);
		  }

		  if (s == s13)
		  {
			  out << s13 <<"\n";
			  getline(fin,data);
			  out << data;
			  prostr(data);
			  cqu.Set(nums[0],nums[1],nums[2],nums[3]);
			  cqu1.Set(nums[4],nums[5],nums[6],nums[7]);
			  nums.clear();
			  sum=cqu.dotMul(cqu1);
			  out <<"	"<<sum<<endl;
		  }

		  if (s == s14)
		  {
			  out << s14 <<"\n";
			  getline(fin,data);
			  out << data;
			  prostr(data);
			  cqu.Set(nums[0],nums[1],nums[2],nums[3]);
			  nums.clear();
			  cqu1=cqu.GetInverse();
			  outCQu(cqu1);
		  }

		  if (s == s15)
		  {
			  out << s15 <<"\n";
			  getline(fin,data);
			  out << data;
			  prostr(data);
			  cqu.Set(nums[0],nums[1],nums[2],nums[3]);
			  nums.clear();
			  cqu.GetAngle(sum,cve);
			  out<<"	";
			  out<<setiosflags(ios::fixed)<<setprecision(2)<<sum<<"	"<<cve.x<<","
				  <<cve.y<<","
				  <<cve.z<<"\n";
		  }

		  if (s == s16)
		  {
			  out << s16 <<"\n";
			  getline(fin,data);
			  out << data;
			  prostr(data);
			  cqu.Set(nums[0],nums[1],nums[2],nums[3]);
			  cqu1.Set(nums[4],nums[5],nums[6],nums[7]);
			  sum = nums[8];
			  nums.clear();
			  cqu=cqu.Slerp(cqu1,sum);
			  out<<"	";
			  outCQu(cqu);
		  }

	}
	fin.close();
	out.close();
	return 0;
}
