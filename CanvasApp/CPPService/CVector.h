#pragma once
#include "CP3.h"
#include <math.h>

class CVector
{
public:
	CVector();
	CVector(double X, double Y, double Z);
	CVector(CP3 pt1, CP3 pt2);
	CVector(CP3 pt1);
	~CVector();
	double Modulus(); //向量的模
	CVector Normalize();//归一化
	friend CVector operator +(const CVector v0, const CVector v1);
	friend CVector operator -(const CVector v0, const CVector v1);
	friend CVector operator *(const CVector v0, double scalar);
	friend CVector operator *(double scalar, const CVector v1);
	friend CVector operator /(const CVector v1, double scalar);
	double DotProduct(CVector v0, CVector v1);//点积
	double DotProduct(CVector v0);//点积
	CVector CrossProduct(CVector v0, CVector v1);//叉积
	CVector CrossProduct(CVector v0);//叉积
public:
	double X, Y, Z;
};

