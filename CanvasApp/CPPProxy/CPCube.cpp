#include "CPCube.h"

CPCube::CPCube()
{
	Mesh = gcnew List<CPSurfaceUnit^>();
	Pts = gcnew List<Point3D>();
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

CPCube::CPCube(Point position, double length, double width, double height)
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

CPCube::~CPCube()
{

}

void CPCube::Translate(double tx, double ty, double tz)
{
	CCube cube;
	vector<SurfaceUnit> temp;
	for each (CPSurfaceUnit^ surface in Mesh)
	{
		temp.push_back(SurfaceUnit(CP3(surface->Pts[0].X, surface->Pts[0].Y, surface->Pts[0].Z),
			CP3(surface->Pts[1].X, surface->Pts[1].Y, surface->Pts[1].Z),
			CP3(surface->Pts[2].X, surface->Pts[2].Y, surface->Pts[2].Z)));
	}
	cube.Mesh = temp;
	cube.Translate(tx, ty, tz);
	OutLines = gcnew List<CPLine^>();
	for (int i = 0; i < cube.OtmopLine.size(); i++)
	{
		CP2 pt1 = cube.OtmopLine[i].StartPt;
		CP2 pt2 = cube.OtmopLine[i].EndPt;
		OutLines->Add(gcnew CPLine(pt1.X, pt1.Y, pt2.X, pt2.Y));
	}

	Mesh = gcnew List<CPSurfaceUnit^>();
	for (int i = 0; i < cube.Mesh.size(); i++)
	{
		Mesh->Add(gcnew CPSurfaceUnit(cube.Mesh[i]));
	}
}

void CPCube::Scale(double sx, double sy, double sz)
{
	CCube cube;
	vector<SurfaceUnit> temp;
	for each (CPSurfaceUnit ^ surface in Mesh)
	{
		temp.push_back(SurfaceUnit(CP3(surface->Pts[0].X, surface->Pts[0].Y, surface->Pts[0].Z),
			CP3(surface->Pts[1].X, surface->Pts[1].Y, surface->Pts[1].Z),
			CP3(surface->Pts[2].X, surface->Pts[2].Y, surface->Pts[2].Z)));
	}
	cube.Mesh = temp;
	cube.Scale(sx, sy, sz);
	OutLines = gcnew List<CPLine^>();
	for (int i = 0; i < cube.OtmopLine.size(); i++)
	{
		CP2 pt1 = cube.OtmopLine[i].StartPt;
		CP2 pt2 = cube.OtmopLine[i].EndPt;
		OutLines->Add(gcnew CPLine(pt1.X, pt1.Y, pt2.X, pt2.Y));
	}

	Mesh = gcnew List<CPSurfaceUnit^>();
	for (int i = 0; i < cube.Mesh.size(); i++)
	{
		Mesh->Add(gcnew CPSurfaceUnit(cube.Mesh[i]));
	}
}

void CPCube::RotateX(double angle)
{
	CCube cube;
	vector<SurfaceUnit> temp;
	for each (CPSurfaceUnit ^ surface in Mesh)
	{
		temp.push_back(SurfaceUnit(CP3(surface->Pts[0].X, surface->Pts[0].Y, surface->Pts[0].Z),
			CP3(surface->Pts[1].X, surface->Pts[1].Y, surface->Pts[1].Z),
			CP3(surface->Pts[2].X, surface->Pts[2].Y, surface->Pts[2].Z)));
	}
	cube.Mesh = temp;
	cube.RotateX(angle);
	OutLines = gcnew List<CPLine^>();
	for (int i = 0; i < cube.OtmopLine.size(); i++)
	{
		CP2 pt1 = cube.OtmopLine[i].StartPt;
		CP2 pt2 = cube.OtmopLine[i].EndPt;
		OutLines->Add(gcnew CPLine(pt1.X, pt1.Y, pt2.X, pt2.Y));
	}

	Mesh = gcnew List<CPSurfaceUnit^>();
	for (int i = 0; i < cube.Mesh.size(); i++)
	{
		Mesh->Add(gcnew CPSurfaceUnit(cube.Mesh[i]));
	}
}

void CPCube::RotateY(double angle)
{
	CCube cube;
	vector<SurfaceUnit> temp;
	for each (CPSurfaceUnit ^ surface in Mesh)
	{
		temp.push_back(SurfaceUnit(CP3(surface->Pts[0].X, surface->Pts[0].Y, surface->Pts[0].Z),
			CP3(surface->Pts[1].X, surface->Pts[1].Y, surface->Pts[1].Z),
			CP3(surface->Pts[2].X, surface->Pts[2].Y, surface->Pts[2].Z)));
	}
	cube.Mesh = temp;
	cube.RotateY(angle);
	OutLines = gcnew List<CPLine^>();
	for (int i = 0; i < cube.OtmopLine.size(); i++)
	{
		CP2 pt1 = cube.OtmopLine[i].StartPt;
		CP2 pt2 = cube.OtmopLine[i].EndPt;
		OutLines->Add(gcnew CPLine(pt1.X, pt1.Y, pt2.X, pt2.Y));
	}

	Mesh = gcnew List<CPSurfaceUnit^>();
	for (int i = 0; i < cube.Mesh.size(); i++)
	{
		Mesh->Add(gcnew CPSurfaceUnit(cube.Mesh[i]));
	}
}

void CPCube::RotateZ(double angle)
{
	CCube cube;
	vector<SurfaceUnit> temp;
	for each (CPSurfaceUnit ^ surface in Mesh)
	{
		temp.push_back(SurfaceUnit(CP3(surface->Pts[0].X, surface->Pts[0].Y, surface->Pts[0].Z),
			CP3(surface->Pts[1].X, surface->Pts[1].Y, surface->Pts[1].Z),
			CP3(surface->Pts[2].X, surface->Pts[2].Y, surface->Pts[2].Z)));
	}
	cube.Mesh = temp;
	cube.RotateZ(angle);
	OutLines = gcnew List<CPLine^>();
	for (int i = 0; i < cube.OtmopLine.size(); i++)
	{
		CP2 pt1 = cube.OtmopLine[i].StartPt;
		CP2 pt2 = cube.OtmopLine[i].EndPt;
		OutLines->Add(gcnew CPLine(pt1.X, pt1.Y, pt2.X, pt2.Y));
	}

	Mesh = gcnew List<CPSurfaceUnit^>();
	for (int i = 0; i < cube.Mesh.size(); i++)
	{
		Mesh->Add(gcnew CPSurfaceUnit(cube.Mesh[i]));
	}
}
