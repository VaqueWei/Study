#include "CPSurfaceUnit.h"

CPSurfaceUnit::CPSurfaceUnit(Point3D pt1, Point3D pt2, Point3D pt3)
{
	Pts = gcnew List<Point3D>();
	SurfaceUnit surface = SurfaceUnit(CP3(pt1.X, pt1.Y, pt1.Z), CP3(pt2.X, pt2.Y, pt2.Z), CP3(pt3.X, pt3.Y, pt3.Z));
	for (int i = 0; i < surface.Pts.size(); i++)
	{
		Pts->Add(Point3D(surface.Pts[i].X, surface.Pts[i].Y, surface.Pts[i].Z));
	}
	V1 = Point3D(surface.V1.X, surface.V1.Y, surface.V1.Z);
	V2 = Point3D(surface.V2.X, surface.V2.Y, surface.V2.Z);
	V3 = Point3D(surface.V3.X, surface.V3.Y, surface.V3.Z);
}

CPSurfaceUnit::CPSurfaceUnit(SurfaceUnit surface)
{
	Pts = gcnew List<Point3D>();
	for (int i = 0; i < surface.Pts.size(); i++)
	{
		Pts->Add(Point3D(surface.Pts[i].X, surface.Pts[i].Y, surface.Pts[i].Z));
	}
	V1 = Point3D(surface.V1.X, surface.V1.Y, surface.V1.Z);
	V2 = Point3D(surface.V2.X, surface.V2.Y, surface.V2.Z);
	V3 = Point3D(surface.V3.X, surface.V3.Y, surface.V3.Z);
}
