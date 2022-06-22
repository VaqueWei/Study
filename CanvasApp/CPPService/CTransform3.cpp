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
}

CTransform3::CTransform3()
{
	Identity();
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
		result.push_back(screenPoint);
	}
	return result;
}

vector<CP2> CTransform3::ObliqueBinary()
{
	//vector<CP3> pts;
	//for (int i = 0; i < Mesh.size(); i++)
	//{
	//	CVector viewV(CP3(0, 100, 900), Mesh[i].Pts[0]);
	//	viewV.Normalize();
	//	if (viewV.DotProduct(viewV, Mesh[i].Normal()) >= 0)
	//	{
	//		pts.push_back(Mesh[i].Pts[0]);
	//		pts.push_back(Mesh[i].Pts[1]);
	//		pts.push_back(Mesh[i].Pts[2]);
	//	}

	//}
	//eyePoint(0,0,1200)
	vector<CP2> result;
	for (int i = 0; i < Pts.size(); i++)
	{
		CP2 screenPoint;
		screenPoint.X = Pts[i].X + 0.3536 * Pts[i].Z;
		screenPoint.Y = Pts[i].Y + 0.3536 * Pts[i].Z;
		result.push_back(screenPoint);
	}

	vector<CP2> temp;
	for (int i = 0; i < result.size(); i += 3)
	{
		double x1 = result[i].X, y1 = result[i].Y, x2 = result[i + 1].X, y2 = result[i + 1].Y, x3 = result[i + 2].X, y3 = result[i + 2].Y;
		if ((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1) < 0)
		{
			temp.push_back(result[i]);
			temp.push_back(result[i + 1]);
			temp.push_back(result[i + 2]);
		}
	}
	return temp;
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

void CTransform3::ResetMesh()
{
	Mesh.clear();
	for (int i = 0; i < Pts.size(); i += 3)
	{
		Mesh.push_back(SurfaceUnit(Pts[i], Pts[i + 1], Pts[i + 2]));
	}
}
