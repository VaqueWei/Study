#include "CTransform2.h"

CTransform2::CTransform2(vector<CP2> pts)
{
	Pts = pts;
	PtNum = pts.size();
	Identity();
}

CTransform2::CTransform2()
{
	Identity();
}

CTransform2::~CTransform2()
{
}

void CTransform2::SetMatrix(double m11, double m12, double m13, double m21, double m22, double m23, double m31, double m32, double m33)
{
	T[0][0] = m11, T[0][1] = m12, T[0][2] = m13;
	T[1][0] = m21, T[1][1] = m22, T[1][2] = m23;
	T[2][0] = m31, T[2][1] = m32, T[2][2] = m33;
	MulMatrix();
}

void CTransform2::Identity()
{
	T[0][0] = 1, T[0][1] = 0, T[0][2] = 0;
	T[1][0] = 0, T[1][1] = 1, T[1][2] = 0;
	T[2][0] = 0, T[2][1] = 0, T[2][2] = 1;
}

void CTransform2::Translate(double tx, double ty)
{
	Identity();
	T[0][2] = tx;
	T[1][2] = ty;
	MulMatrix();
}

void CTransform2::Scale(double sx, double sy)
{
	Identity();
	T[0][0] = sx;
	T[1][1] = sy;
	MulMatrix();
}

void CTransform2::Rotate(double angle, double tx, double ty)
{
	double matrix[9] = {
		cos(angle),-sin(angle),tx * (1 - cos(angle)) + ty * sin(angle),
		sin(angle),cos(angle),ty * (1 - cos(angle)) - tx * sin(angle),
		0,0,1 };
	T[0][0] = cos(angle);
	T[0][1] = -sin(angle);
	T[0][2] = tx * (1 - cos(angle)) + ty * sin(angle);
	T[1][0] = sin(angle);
	T[1][1] = cos(angle);
	T[1][2] = ty * (1 - cos(angle)) - tx * sin(angle);
	MulMatrix();
}

void CTransform2::MulMatrix()
{
	for (int i = 0; i < PtNum; i++)
	{
		CP2 pt = CP2(Pts[i].X, Pts[i].Y);
		Pts[i].X = T[0][0] * pt.X + T[0][1] * pt.Y + T[0][2] * pt.W;
		Pts[i].Y = T[1][0] * pt.X + T[1][1] * pt.Y + T[1][2] * pt.W;
		Pts[i].W = T[2][0] * pt.X + T[2][1] * pt.Y + T[2][2] * pt.W;
	}

}
