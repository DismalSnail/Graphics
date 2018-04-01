#include "stdafx.h"
#include "Vector068.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include <GL/glut.h>
#include "Matrix068.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
  float Array_A[16]={
    1,3,5,0,
    2,4,6,0,
    0,2,8,0,
    4,2,1,1
  };
  float Array_B[16]={
    1,2,3,4,
    5,6,7,8,
    9,10,11,12,
    13,14,15,16
  };
  CVector068 CVector068_A;
  CVector068 CVector068_B;
  CMatrix068 CMatrix068_A;
  CMatrix068 CMatrix068_B;
  CMatrix068 CMatrix068_C;
  //CVector068_A.Set(3,6,9);
  // CMatrix068_B.Set(Array_B);
  CMatrix068_A.Set(Array_A);
  // CVector068_B=CMatrix068_A.posMul(CVector068_A);
  //CMatrix068_A.SetScale(CVector068_A);
  CMatrix068_B=CMatrix068_A.GetInverse();
  //std::cout <<CVector068_B.x<<" "<<CVector068_B.y<<" "<<CVector068_B.z<< '\n';
  //CMatrix068_A = CMatrix068_B;
  // CMatrix068_C=CMatrix068_A*CVector068_A;
  // std::cout << CMatrix068_C.m00<<" "<<CMatrix068_C.m10<<" "<<CMatrix068_C.m20<<" "<<CMatrix068_C.m30 << '\n';
  // std::cout << CMatrix068_B.m00<<" "<<CMatrix068_B.m10<<" "<<CMatrix068_B.m20<<" "<<CMatrix068_B.m30 << '\n';
  std::cout << CMatrix068_A.Inverse() << '\n';
  std::cout << CMatrix068_B.m00<<" "<<CMatrix068_B.m10<<" "<<CMatrix068_B.m20<<" "<<CMatrix068_B.m30 << '\n';
  std::cout << CMatrix068_B.m01<<" "<<CMatrix068_B.m11<<" "<<CMatrix068_B.m21<<" "<<CMatrix068_B.m31 << '\n';
  std::cout << CMatrix068_B.m02<<" "<<CMatrix068_B.m12<<" "<<CMatrix068_B.m22<<" "<<CMatrix068_B.m32 << '\n';
  std::cout << CMatrix068_B.m03<<" "<<CMatrix068_B.m13<<" "<<CMatrix068_B.m23<<" "<<CMatrix068_B.m33 << '\n';
  // //return 0;
  system("PAUSE");
  return 0;
}
