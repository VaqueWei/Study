#pragma once
#include "CP3.h"
#include "CP2.h"
#include <math.h>
#include <vector>
#include "SurfaceUnit.h"

using namespace std;

class CTransform3
{
public:
	CTransform3(vector<SurfaceUnit> mesh);
	CTransform3();
	~CTransform3();
	void Identity();
	void Translate(double tx, double ty, double tz);
	void Scale(double sx, double sy, double sz);
	void RotateX(double angle);
	void RotateY(double angle);
	void RotateZ(double angle);
	/// <summary>
/// 透视投影
/// </summary>
/// <param 视点 name="v"></param>
/// <param 视径 name="r"></param>
/// <param 视距 name="d"></param>
	vector<CP2> Perspective(double v, double r, double d);
	/// <summary>
	/// 斜二测投影
	/// </summary>
	/// <returns></returns>
	vector<CP2> ObliqueBinary();
private:
	void MulMatrix();
	void ResetMesh();
public:
	vector<SurfaceUnit> Mesh;
	vector<CP3> Pts;
private:
	double T[4][4];
	double PtNum;
};

