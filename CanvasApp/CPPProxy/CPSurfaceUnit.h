#pragma once
#include "SurfaceUnit.h"

using namespace System::Collections::Generic;
using namespace System::Windows;
using namespace System::Windows::Media::Media3D;

ref class CPSurfaceUnit
{
public:
	CPSurfaceUnit(Point3D pt1,Point3D pt2,Point3D pt3);
	CPSurfaceUnit(SurfaceUnit surface);
public:
	List<Point3D>^ Pts;
	Point3D V1;
	Point3D V2;
	Point3D V3;
};

