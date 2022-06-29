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
	CTransform3(vector<CP3> pts);
	CTransform3();
	~CTransform3();
	void Identity();
	void Translate(double tx, double ty, double tz);
	void Scale(double sx, double sy, double sz);
	void RotateX(double angle);
	void RotateY(double angle);
	void RotateZ(double angle);
	void CameraMatiax();
	void SetCameraMatiax(
		double r11, double r12, double r13, double tx,
		double r21, double r22, double r23, double ty,
		double r31, double r32, double r33, double tz);
	// 透视投影
	vector<CP2> Perspective(double v, double r, double d);
	// 斜二测投影
	vector<CP2> ObliqueBinary();

	vector<CP2> ScreenSpace();
	vector<CP2> ScreenSpaceAll();
private:
	void MulMatrix();
	CP2 MulCameraMatrix(CP3 pt);
	void ResetMesh();
public:
	vector<SurfaceUnit> Mesh;
	vector<CP3> Pts;
private:
	double T[4][4]; //三维坐标变换矩阵
	double I[3][4]; //相机内参矩阵
	double R[4][4]; //相机外参矩阵
	double PtNum;
};

