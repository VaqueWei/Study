#pragma once
#include "CTransform2.h"
#include "CPLine.h"
#include <vector>
#include "TopCpLineShape.h"

using namespace System::Collections::Generic;
using namespace System::Windows;

public ref class CPTransform2
{
public:
	CPTransform2(TopCpLineShape^ shape);
	~CPTransform2();

	void Translate(double tx, double ty);
	void Scale(double sx, double sy);
	void Rotate(double angle, double tx, double ty);
	void SetMatrix(
		double m11, double m12, double m13,
		double m21, double m22, double m23,
		double m31, double m32, double m33
	);
public:
	List<Point>^ Pts;
	double Angle;
	double Tx, Ty;
	double Sx, Sy;
	List<double>^ Matrix;
	List<CPLine^>^ OutLines;

private:
	vector<CP2> List2Pointer(List<Point>^ pts);
	List<Point>^ Pointer2List(vector<CP2> pts);
	List<CPLine^>^ Pts2CPLine(List<Point>^ pts);
};

