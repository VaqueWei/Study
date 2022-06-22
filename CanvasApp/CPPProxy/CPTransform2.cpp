#include "CPTransform2.h"


CPTransform2::CPTransform2(TopCpLineShape^ shape)
{
	OutLines = shape->OutLines;
	Pts = gcnew List<Point>();
	for each (CPLine^ line in OutLines)
	{
		Pts->Add(Point(line->X1, line->Y1));
	}
}
CPTransform2::~CPTransform2()
{

}

void CPTransform2::Translate(double tx, double ty)
{
	Tx = tx, Ty = ty;
	CTransform2 trans(List2Pointer(Pts));
	trans.Translate(tx, ty);
	Pts = Pointer2List(trans.Pts);
	OutLines = Pts2CPLine(Pts);
}

void CPTransform2::Scale(double sx, double sy)
{
	Sx = sx, Sy = sy;
	CTransform2 trans(List2Pointer(Pts));
	trans.Scale(sx, sy);
	Pts = Pointer2List(trans.Pts);
	OutLines = Pts2CPLine(Pts);
}

void CPTransform2::Rotate(double angle,double tx,double ty)
{
	Angle = angle;
	CTransform2 trans(List2Pointer(Pts));
	trans.Rotate(angle,tx,ty);
	Pts = Pointer2List(trans.Pts);
	OutLines = Pts2CPLine(Pts);
}
void CPTransform2::SetMatrix(
	double m11, double m12, double m13,
	double m21, double m22, double m23,
	double m31, double m32, double m33
) 
{
	Matrix = gcnew List<double>();
	double matrix[9] = { m11, m12, m13, m21, m22, m23, m31, m32, m33 };
	for (int i=0;i<9;i++)
	{
		Matrix->Add(matrix[i]);
	}
	CTransform2 trans(List2Pointer(Pts));
	trans.SetMatrix(m11, m12, m13, m21, m22, m23, m31, m32, m33);
	Pts = Pointer2List(trans.Pts);
	OutLines = Pts2CPLine(Pts);
}

vector<CP2> CPTransform2::List2Pointer(List<Point>^ pts)
{
	vector<CP2> result;
	for each (Point pt in pts)
	{
		result.push_back(CP2(pt.X, pt.Y));
	}
	return result;
}

List<Point>^ CPTransform2::Pointer2List(vector<CP2> pts)
{
	List<Point>^ result = gcnew List<Point>();
	for (int i = 0; i < pts.size(); i++)
	{
		result->Add(Point(pts[i].X, pts[i].Y));
	}
	return result;
}

List<CPLine^>^ CPTransform2::Pts2CPLine(List<Point>^ pts)
{
	List<CPLine^>^ result = gcnew List<CPLine^>();
	for (int i = 1; i < pts->Count; i++)
	{
		CPLine^ line = gcnew CPLine(Pts[i - 1].X, pts[i - 1].Y, pts[i].X, pts[i].Y);
		result->Add(line);
	}
	result->Add(gcnew CPLine(Pts[pts->Count - 1].X, pts[pts->Count - 1].Y, pts[0].X, pts[0].Y));
	return result;
}
