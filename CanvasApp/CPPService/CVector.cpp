#include "CVector.h"

CVector::CVector()
{
	X = 0, Y = 0, Z = 1;
}

CVector::CVector(double x, double y, double z)
{
	X = x, Y = y, Z = z;
}

CVector::CVector(CP3 pt1, CP3 pt2)
{
	X = pt2.X - pt1.X;
	Y = pt2.Y - pt1.Y;
	Z = pt2.Z - pt1.Z;
}

CVector::CVector(CP3 pt1)
{
	X = pt1.X, Y = pt1.Y, Z = pt1.Z;
}

CVector::~CVector()
{
}

double CVector::Modulus()
{
	return sqrt(X * X + Y * Y + Z * Z);
}

CVector CVector::Normalize()
{
	CVector vector;
	double modulus = Modulus();
	if (modulus < 1e-4)
	{
		modulus = 1;
	}
	vector.X = X / modulus;
	vector.Y = Y / modulus;
	vector.Z = Z / modulus;

	return vector;
}

double CVector::DotProduct(CVector v0, CVector v1)
{
	return (v0.X * v1.X + v0.Y * v1.Y + v0.Z * v1.Z);
}

double CVector::DotProduct(CVector v0)
{
	return (v0.X * X + v0.Y * Y + v0.Z * Z);
}

CVector CVector::CrossProduct(CVector v0, CVector v1)
{
	CVector vector;
	vector.X = v0.Y * v1.Z - v0.Z * v1.Y;
	vector.Y = v0.Z * v1.X - v0.X * v1.Z;
	vector.Z = v0.X * v1.Y - v0.Y * v1.X;
	return vector;
}

CVector CVector::CrossProduct(CVector v0)
{
	CVector vector;
	vector.X = v0.Y * Z - v0.Z * Y;
	vector.Y = v0.Z * X - v0.X * Z;
	vector.Z = v0.X * Y - v0.Y * X;
	return vector;
}

CVector operator+(const CVector v0, const CVector v1)
{
	CVector vector;
	vector.X = v0.X + v1.X;
	vector.Y = v0.Y + v1.Y;
	vector.Z = v0.Z + v1.Z;
	return vector;
}

CVector operator-(const CVector v0, const CVector v1)
{
	CVector vector;
	vector.X = v0.X - v1.X;
	vector.Y = v0.Y - v1.Y;
	vector.Z = v0.Z - v1.Z;
	return vector;
}

CVector operator*(const CVector v1, double scalar)
{
	CVector vector;
	vector.X = scalar * v1.X;
	vector.Y = scalar * v1.Y;
	vector.Z = scalar * v1.Z;
	return vector;
}

CVector operator*(double scalar, const CVector v1)
{
	CVector vector;
	vector.X = scalar * v1.X;
	vector.Y = scalar * v1.Y;
	vector.Z = scalar * v1.Z;
	return vector;
}

CVector operator/(const CVector v1, double scalar)
{
	if (fabs(scalar) < 1e-4)
	{
		scalar = 1;
	}
	CVector vector;
	vector.X = v1.X / scalar;
	vector.Y = v1.Y / scalar;
	vector.Z = v1.Z / scalar;
	return vector;
}
