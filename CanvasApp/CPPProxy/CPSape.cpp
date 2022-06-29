#include "CPShape.h"

CPShape::CPShape()
{
	Mesh = gcnew List<CPSurfaceUnit^>();
	Pts = gcnew List<Point3D>();
	OutLines = gcnew List<CPLine^>();
	CCube cube;
	Width = cube.Width, Length = cube.Length, Height = cube.Height;
	for (int i = 0; i < cube.OtmopLine.size(); i++)
	{
		CP2 pt1 = cube.OtmopLine[i].StartPt;
		CP2 pt2 = cube.OtmopLine[i].EndPt;
		OutLines->Add(gcnew CPLine(pt1.X, pt1.Y, pt2.X, pt2.Y));
	}

	for (int i = 0; i < cube.P.size(); i++)
	{
		Pts->Add(Point3D(cube.P[i].X, cube.P[i].Y, cube.P[i].Z));
	}

	for (int i = 0; i < cube.Mesh.size(); i++)
	{
		Mesh->Add(gcnew CPSurfaceUnit(cube.Mesh[i]));
	}
}


CPShape::~CPShape()
{

}

void CPShape::CreateCube(Point position, double length, double width, double height)
{
	Mesh = gcnew List<CPSurfaceUnit^>();
	Pts = gcnew List<Point3D>();
	Position = position;
	CP3 pt = CP3(position.X, position.Y, 0);
	CCube cube = CCube(pt, length, width, height);
	Width = cube.Width, Length = cube.Length, Height = cube.Height;
	OutLines = gcnew List<CPLine^>();
	for (int i = 0; i < cube.OtmopLine.size(); i++)
	{
		CP2 pt1 = cube.OtmopLine[i].StartPt;
		CP2 pt2 = cube.OtmopLine[i].EndPt;
		OutLines->Add(gcnew CPLine(pt1.X, pt1.Y, pt2.X, pt2.Y));
	}

	for (int i = 0; i < cube.P.size(); i++)
	{
		Pts->Add(Point3D(cube.P[i].X, cube.P[i].Y, cube.P[i].Z));
	}

	for (int i = 0; i < cube.Mesh.size(); i++)
	{
		Mesh->Add(gcnew CPSurfaceUnit(cube.Mesh[i]));
	}
}

void CPShape::CreateCylind(Point3D pos, double radius, double height, double precision)
{
	Mesh = gcnew List<CPSurfaceUnit^>();
	Pts = gcnew List<Point3D>();

	CCylind pyramid = CCylind(CP3(pos.X, pos.Y, pos.Z), radius, height, precision);
	OutLines = gcnew List<CPLine^>();
	for (int i = 0; i < pyramid.OtmopLine.size(); i++)
	{
		CP2 pt1 = pyramid.OtmopLine[i].StartPt;
		CP2 pt2 = pyramid.OtmopLine[i].EndPt;
		OutLines->Add(gcnew CPLine(pt1.X, pt1.Y, pt2.X, pt2.Y));
	}

	for (int i = 0; i < pyramid.P.size(); i++)
	{
		Pts->Add(Point3D(pyramid.P[i].X, pyramid.P[i].Y, pyramid.P[i].Z));
	}

	for (int i = 0; i < pyramid.Mesh.size(); i++)
	{
		Mesh->Add(gcnew CPSurfaceUnit(pyramid.Mesh[i]));
	}
}

void CPShape::CreatePyramid(double width, double height)
{
	Mesh = gcnew List<CPSurfaceUnit^>();
	Pts = gcnew List<Point3D>();

	CPyramid pyramid = CPyramid(width, height);
	Width = pyramid.Width, Height = pyramid.Height;
	OutLines = gcnew List<CPLine^>();
	for (int i = 0; i < pyramid.OtmopLine.size(); i++)
	{
		CP2 pt1 = pyramid.OtmopLine[i].StartPt;
		CP2 pt2 = pyramid.OtmopLine[i].EndPt;
		OutLines->Add(gcnew CPLine(pt1.X, pt1.Y, pt2.X, pt2.Y));
	}

	for (int i = 0; i < pyramid.P.size(); i++)
	{
		Pts->Add(Point3D(pyramid.P[i].X, pyramid.P[i].Y, pyramid.P[i].Z));
	}

	for (int i = 0; i < pyramid.Mesh.size(); i++)
	{
		Mesh->Add(gcnew CPSurfaceUnit(pyramid.Mesh[i]));
	}
}

void CPShape::CreateSphere(Point3D pos, double radius, double precision)
{
	Mesh = gcnew List<CPSurfaceUnit^>();
	Pts = gcnew List<Point3D>();

	CSphere sphere = CSphere(CP3(pos.X, pos.Y, pos.Z), radius, precision);
	OutLines = gcnew List<CPLine^>();
	for (int i = 0; i < sphere.OtmopLine.size(); i++)
	{
		CP2 pt1 = sphere.OtmopLine[i].StartPt;
		CP2 pt2 = sphere.OtmopLine[i].EndPt;
		OutLines->Add(gcnew CPLine(pt1.X, pt1.Y, pt2.X, pt2.Y));
	}

	for (int i = 0; i < sphere.P.size(); i++)
	{
		Pts->Add(Point3D(sphere.P[i].X, sphere.P[i].Y, sphere.P[i].Z));
	}

	for (int i = 0; i < sphere.Mesh.size(); i++)
	{
		Mesh->Add(gcnew CPSurfaceUnit(sphere.Mesh[i]));
	}
}

void CPShape::Translate(double tx, double ty, double tz)
{
	TopLineShape shape;
	vector<SurfaceUnit> temp;
	for each (CPSurfaceUnit^ surface in Mesh)
	{
		temp.push_back(SurfaceUnit(CP3(surface->Pts[0].X, surface->Pts[0].Y, surface->Pts[0].Z),
			CP3(surface->Pts[1].X, surface->Pts[1].Y, surface->Pts[1].Z),
			CP3(surface->Pts[2].X, surface->Pts[2].Y, surface->Pts[2].Z)));
	}
	shape.Mesh = temp;
	shape.Translate(tx, ty, tz);
	OutLines = gcnew List<CPLine^>();
	for (int i = 0; i < shape.OtmopLine.size(); i++)
	{
		CP2 pt1 = shape.OtmopLine[i].StartPt;
		CP2 pt2 = shape.OtmopLine[i].EndPt;
		OutLines->Add(gcnew CPLine(pt1.X, pt1.Y, pt2.X, pt2.Y));
	}

	Mesh = gcnew List<CPSurfaceUnit^>();
	for (int i = 0; i < shape.Mesh.size(); i++)
	{
		Mesh->Add(gcnew CPSurfaceUnit(shape.Mesh[i]));
	}
}

void CPShape::Scale(double sx, double sy, double sz)
{
	TopLineShape shape;
	vector<SurfaceUnit> temp;
	for each (CPSurfaceUnit ^ surface in Mesh)
	{
		temp.push_back(SurfaceUnit(CP3(surface->Pts[0].X, surface->Pts[0].Y, surface->Pts[0].Z),
			CP3(surface->Pts[1].X, surface->Pts[1].Y, surface->Pts[1].Z),
			CP3(surface->Pts[2].X, surface->Pts[2].Y, surface->Pts[2].Z)));
	}
	shape.Mesh = temp;
	shape.Scale(sx, sy, sz);
	OutLines = gcnew List<CPLine^>();
	for (int i = 0; i < shape.OtmopLine.size(); i++)
	{
		CP2 pt1 = shape.OtmopLine[i].StartPt;
		CP2 pt2 = shape.OtmopLine[i].EndPt;
		OutLines->Add(gcnew CPLine(pt1.X, pt1.Y, pt2.X, pt2.Y));
	}

	Mesh = gcnew List<CPSurfaceUnit^>();
	for (int i = 0; i < shape.Mesh.size(); i++)
	{
		Mesh->Add(gcnew CPSurfaceUnit(shape.Mesh[i]));
	}
}

void CPShape::RotateX(double angle)
{
	TopLineShape shape;
	vector<SurfaceUnit> temp;
	for each (CPSurfaceUnit ^ surface in Mesh)
	{
		temp.push_back(SurfaceUnit(CP3(surface->Pts[0].X, surface->Pts[0].Y, surface->Pts[0].Z),
			CP3(surface->Pts[1].X, surface->Pts[1].Y, surface->Pts[1].Z),
			CP3(surface->Pts[2].X, surface->Pts[2].Y, surface->Pts[2].Z)));
	}
	shape.Mesh = temp;
	shape.RotateX(angle);
	OutLines = gcnew List<CPLine^>();
	for (int i = 0; i < shape.OtmopLine.size(); i++)
	{
		CP2 pt1 = shape.OtmopLine[i].StartPt;
		CP2 pt2 = shape.OtmopLine[i].EndPt;
		OutLines->Add(gcnew CPLine(pt1.X, pt1.Y, pt2.X, pt2.Y));
	}

	Mesh = gcnew List<CPSurfaceUnit^>();
	for (int i = 0; i < shape.Mesh.size(); i++)
	{
		Mesh->Add(gcnew CPSurfaceUnit(shape.Mesh[i]));
	}
}

void CPShape::RotateY(double angle)
{
	TopLineShape shape;
	vector<SurfaceUnit> temp;
	for each (CPSurfaceUnit ^ surface in Mesh)
	{
		temp.push_back(SurfaceUnit(CP3(surface->Pts[0].X, surface->Pts[0].Y, surface->Pts[0].Z),
			CP3(surface->Pts[1].X, surface->Pts[1].Y, surface->Pts[1].Z),
			CP3(surface->Pts[2].X, surface->Pts[2].Y, surface->Pts[2].Z)));
	}
	shape.Mesh = temp;
	shape.RotateY(angle);
	OutLines = gcnew List<CPLine^>();
	for (int i = 0; i < shape.OtmopLine.size(); i++)
	{
		CP2 pt1 = shape.OtmopLine[i].StartPt;
		CP2 pt2 = shape.OtmopLine[i].EndPt;
		OutLines->Add(gcnew CPLine(pt1.X, pt1.Y, pt2.X, pt2.Y));
	}

	Mesh = gcnew List<CPSurfaceUnit^>();
	for (int i = 0; i < shape.Mesh.size(); i++)
	{
		Mesh->Add(gcnew CPSurfaceUnit(shape.Mesh[i]));
	}
}

void CPShape::RotateZ(double angle)
{
	TopLineShape shape;
	vector<SurfaceUnit> temp;
	for each (CPSurfaceUnit ^ surface in Mesh)
	{
		temp.push_back(SurfaceUnit(CP3(surface->Pts[0].X, surface->Pts[0].Y, surface->Pts[0].Z),
			CP3(surface->Pts[1].X, surface->Pts[1].Y, surface->Pts[1].Z),
			CP3(surface->Pts[2].X, surface->Pts[2].Y, surface->Pts[2].Z)));
	}
	shape.Mesh = temp;
	shape.RotateZ(angle);
	OutLines = gcnew List<CPLine^>();
	for (int i = 0; i < shape.OtmopLine.size(); i++)
	{
		CP2 pt1 = shape.OtmopLine[i].StartPt;
		CP2 pt2 = shape.OtmopLine[i].EndPt;
		OutLines->Add(gcnew CPLine(pt1.X, pt1.Y, pt2.X, pt2.Y));
	}

	Mesh = gcnew List<CPSurfaceUnit^>();
	for (int i = 0; i < shape.Mesh.size(); i++)
	{
		Mesh->Add(gcnew CPSurfaceUnit(shape.Mesh[i]));
	}
}

void CPShape::SetCameraMatiax(double r11, double r12, double r13, double tx, double r21, double r22, double r23, double ty, double r31, double r32, double r33, double tz)
{
	TopLineShape shape;
	vector<SurfaceUnit> temp;
	for each (CPSurfaceUnit ^ surface in Mesh)
	{
		temp.push_back(SurfaceUnit(CP3(surface->Pts[0].X, surface->Pts[0].Y, surface->Pts[0].Z),
			CP3(surface->Pts[1].X, surface->Pts[1].Y, surface->Pts[1].Z),
			CP3(surface->Pts[2].X, surface->Pts[2].Y, surface->Pts[2].Z)));
	}
	shape.Mesh = temp;
	shape.SetCameraMatiax(r11, r12, r13, tx, r21, r22, r23, ty, r31, r32, r33, tz);
	OutLines = gcnew List<CPLine^>();
	for (int i = 0; i < shape.OtmopLine.size(); i++)
	{
		CP2 pt1 = shape.OtmopLine[i].StartPt;
		CP2 pt2 = shape.OtmopLine[i].EndPt;
		OutLines->Add(gcnew CPLine(pt1.X, pt1.Y, pt2.X, pt2.Y));
	}

	Mesh = gcnew List<CPSurfaceUnit^>();
	for (int i = 0; i < shape.Mesh.size(); i++)
	{
		Mesh->Add(gcnew CPSurfaceUnit(shape.Mesh[i]));
	}
}
