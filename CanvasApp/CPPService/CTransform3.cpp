#include "CTransform3.h"

CTransform3::CTransform3(vector<SurfaceUnit> mesh)
{
	for (int i = 0; i < mesh.size(); i++)
	{
		Pts.push_back(mesh[i].Pts[0]);
		Pts.push_back(mesh[i].Pts[1]);
		Pts.push_back(mesh[i].Pts[2]);
	}
	Mesh = mesh;
	PtNum = Pts.size();
	Identity();
	CameraMatiax();
}

CTransform3::CTransform3(vector<CP3> pts)
{
	Pts = pts;
	PtNum = Pts.size();
	Identity();
	CameraMatiax();
}
CTransform3::CTransform3()
{
	Identity();
	CameraMatiax();
}

CTransform3::~CTransform3()
{
}

void CTransform3::Identity()
{
	T[0][0] = 1, T[0][1] = 0, T[0][2] = 0, T[0][3] = 0;
	T[1][0] = 0, T[1][1] = 1, T[1][2] = 0, T[1][3] = 0;
	T[2][0] = 0, T[2][1] = 0, T[2][2] = 1, T[2][3] = 0;
	T[3][0] = 0, T[3][1] = 0, T[3][2] = 0, T[3][3] = 1;
}

void CTransform3::Translate(double tx, double ty, double tz)
{
	Identity();
	T[0][3] = tx;
	T[1][3] = ty;
	T[2][3] = tz;
	MulMatrix();
}

void CTransform3::Scale(double sx, double sy, double sz)
{
	Identity();
	T[0][0] = sx;
	T[1][1] = sy;
	T[2][2] = sz;
	MulMatrix();
}

void CTransform3::RotateX(double angle)
{
	Identity();
	T[1][1] = cos(angle);
	T[1][2] = -sin(angle);
	T[2][1] = sin(angle);
	T[2][2] = cos(angle);
	MulMatrix();
}

void CTransform3::RotateY(double angle)
{
	Identity();
	T[0][0] = cos(angle);
	T[0][2] = sin(angle);
	T[2][0] = -sin(angle);
	T[2][2] = cos(angle);
	MulMatrix();
}

void CTransform3::RotateZ(double angle)
{
	Identity();
	T[0][0] = cos(angle);
	T[0][1] = -sin(angle);
	T[1][0] = sin(angle);
	T[1][1] = cos(angle);
	MulMatrix();
}

//相机矩阵
void CTransform3::CameraMatiax()
{
	//内参矩阵
	I[0][0] = 4.1378, I[0][1] = 0,		I[0][2] = 2.128, I[0][3] = 0;
	I[1][0] = 0,	  I[1][1] = 4.1473, I[1][2] = 1.416, I[1][3] = 0;
	I[2][0] = 0,	  I[2][1] = 0,		I[2][2] = 0,	 I[2][3] = 0;

	//外参矩阵
	R[0][0] = 1, R[0][1] = 0, R[0][2] = 0, R[0][3] = 0;
	R[1][0] = 0, R[1][1] = 1, R[1][2] = 0, R[1][3] = 0;
	R[2][0] = 0, R[2][1] = 0, R[2][2] = 1, R[2][3] = 0;
	R[3][0] = 0, R[3][1] = 0, R[3][2] = 0, R[3][3] = 1;
}

void CTransform3::SetCameraMatiax(double r11, double r12, double r13, double tx, double r21, double r22, double r23, double ty, double r31, double r32, double r33, double tz)
{
	CameraMatiax();
	R[0][0] = r11, R[0][1] = r12, R[0][2] = r13, R[0][3] = tx;
	R[1][0] = r21, R[1][1] = r22, R[1][2] = r23, R[1][3] = ty;
	R[2][0] = r31, R[2][1] = r32, R[2][2] = r33, R[2][3] = tz;
}


/// <summary>
/// 透视投影
/// </summary>
/// <param 视点 name="v"></param>
/// <param 视径 name="r"></param>
/// <param 视距 name="d"></param>
vector<CP2> CTransform3::Perspective(double v, double r, double d)
{
	vector<CP2> result;
	CP3 viewPoint;
	for (int i = 0; i < Pts.size(); i++)
	{
		viewPoint.X = Pts[i].X;
		viewPoint.Y = Pts[i].Y;
		viewPoint.Z = r - Pts[i].Z;
		CP2 screenPoint;
		screenPoint.X = d * viewPoint.X / viewPoint.Z;
		screenPoint.Y = d * viewPoint.Y / viewPoint.Z;
		result.emplace_back(screenPoint);
	}
	return result;
}

vector<CP2> CTransform3::ObliqueBinary()
{
	vector<CP2> result;
	for (int i = 0; i < Pts.size(); i++)
	{
		CP2 screenPoint;
		screenPoint.X = Pts[i].X - 0.3536 * Pts[i].Z;
		screenPoint.Y = Pts[i].Y - 0.3536 * Pts[i].Z;
		result.push_back(screenPoint);
	}

	vector<CP2> temp;
	for (int i = 0; i < result.size(); i += 3)
	{
		double x1 = result[i].X, y1 = result[i].Y, x2 = result[i + 1].X, y2 = result[i + 1].Y, x3 = result[i + 2].X, y3 = result[i + 2].Y;
		if ((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1) > 0)
		{
			temp.push_back(result[i]);
			temp.push_back(result[i + 1]);
			temp.push_back(result[i + 2]);
		}
	}
	return temp;
}

vector<CP2> CTransform3::ScreenSpace()
{
	vector<CP2> result;
	for (int i = 0; i < Pts.size(); i++)
	{
		result.push_back(MulCameraMatrix(Pts[i]));
	}

	vector<CP2> temp;
	for (int i = 0; i < result.size(); i += 3)
	{
		double x1 = result[i].X, y1 = result[i].Y, x2 = result[i + 1].X, y2 = result[i + 1].Y, x3 = result[i + 2].X, y3 = result[i + 2].Y;
		if ((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1) > 0)
		{
			temp.push_back(result[i]);
			temp.push_back(result[i + 1]);
			temp.push_back(result[i + 2]);
		}
	}
	return temp;
}

vector<CP2> CTransform3::ScreenSpaceAll()
{
	vector<CP2> result;
	for (int i = 0; i < Pts.size(); i++)
	{
		result.push_back(MulCameraMatrix(Pts[i]));
	}
	return result;
}

void CTransform3::MulMatrix()
{
	for (int i = 0; i < PtNum; i++)
	{
		CP3 pt = CP3(Pts[i].X, Pts[i].Y, Pts[i].Z);
		Pts[i].X = T[0][0] * pt.X + T[0][1] * pt.Y + T[0][2] * pt.Z + T[0][3] * pt.W;
		Pts[i].Y = T[1][0] * pt.X + T[1][1] * pt.Y + T[1][2] * pt.Z + T[1][3] * pt.W;
		Pts[i].Z = T[2][0] * pt.X + T[2][1] * pt.Y + T[2][2] * pt.Z + T[2][3] * pt.W;
		Pts[i].W = T[3][0] * pt.X + T[3][1] * pt.Y + T[3][2] * pt.Z + T[3][3] * pt.W;
	}
	ResetMesh();
}


CP2 CTransform3::MulCameraMatrix(CP3 pt)
{
	double x, y, z, w;
	x = R[0][0] * pt.X + R[0][1] * pt.Y + R[0][2] * pt.Z + R[0][3] * pt.W;
	y = R[1][0] * pt.X + R[1][1] * pt.Y + R[1][2] * pt.Z + R[1][3] * pt.W;
	z = R[2][0] * pt.X + R[2][1] * pt.Y + R[2][2] * pt.Z + R[2][3] * pt.W;
	w = R[3][0] * pt.X + R[3][1] * pt.Y + R[3][2] * pt.Z + R[3][3] * pt.W;
	
	double x0, y0, w0;
	x0 = I[0][0] * x + I[0][1] * y + I[0][2] * z + I[0][3] * w;
	y0 = I[1][0] * x + I[1][1] * y + I[1][2] * z + I[1][3] * w;
	w0 = I[2][0] * x + I[2][1] * y + I[2][2] * z + I[2][3] * w;
	return CP2(x0, y0);
}

void CTransform3::ResetMesh()
{
	Mesh.clear();
	for (int i = 0; i < Pts.size(); i += 3)
	{
		Mesh.push_back(SurfaceUnit(Pts[i], Pts[i + 1], Pts[i + 2]));
	}
}
