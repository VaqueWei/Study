#pragma once
#include "CCube.h"
#include "CPLine.h"
#include "TopCpLineShape.h"
#include "NCollection_Haft.h"
#include "CPSurfaceUnit.h"
#include "CPyramid.h"
#include "CCylind.h"
#include "CSphere.h"

public ref class CPShape:public TopCpLineShape
{
public:
	CPShape();
	~CPShape();
	void CreateCube(Point position, double length, double width, double height);
	void CreateCylind(Point3D pos, double radius, double height, double precision);
	void CreatePyramid(double width, double length);
	void CreateSphere(Point3D pos, double radius, double precision);
	void Translate(double tx, double ty, double tz);
	void Scale(double sx, double sy, double sz);
	void RotateX(double angle);
	void RotateY(double angle);
	void RotateZ(double angle);
	void SetCameraMatiax(
		double r11, double r12, double r13, double tx,
		double r21, double r22, double r23, double ty,
		double r31, double r32, double r33, double tz);
public:
	double Width, Length, Height;
	Point Position;

};

