#pragma once
#include "CCube.h"
#include "CPLine.h"
#include "TopCpLineShape.h"
#include "NCollection_Haft.h"
#include "CPSurfaceUnit.h"

public ref class CPCube:public TopCpLineShape
{
public:
	CPCube();
	CPCube(Point position, double length, double width, double height);
	~CPCube();
	void Translate(double tx, double ty, double tz);
	void Scale(double sx, double sy, double sz);
	void RotateX(double angle);
	void RotateY(double angle);
	void RotateZ(double angle);
public:
	double Width, Length, Height;
	Point Position;

};

