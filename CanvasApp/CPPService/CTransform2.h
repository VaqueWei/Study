#pragma once
#include "CP2.h"
#include <math.h>
#include <vector>

using namespace std;

class CTransform2
{
public:
	CTransform2(vector<CP2> pts);
	CTransform2();
	~CTransform2();
	void SetMatrix(
		double m11,double m12,double m13,
		double m21,double m22,double m23,
		double m31,double m32,double m33
	);
	void Identity();
	void Translate(double tx, double ty);
	void Scale(double sx,double sy);
	void Rotate(double angle, double tx, double ty);
private:
	void MulMatrix();

public:

	vector<CP2> Pts;
private:
	double T[3][3];
	double PtNum;
};

