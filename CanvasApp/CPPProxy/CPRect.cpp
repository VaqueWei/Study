#include "CPRect.h"

CPRect::CPRect(Point^ pos, double width, double length)
{
	CRect rect = CRect(CP2(pos->X, pos->Y), width, length);
	OutLines = gcnew List<CPLine^>();
	OutLinePts = gcnew List<Point>();
	for (int i = 0; i < rect.OtmopLine.size(); i++)
	{
		CP2 pt1 = rect.OtmopLine[i].StartPt;
		CP2 pt2 = rect.OtmopLine[i].EndPt;
		OutLines->Add(gcnew CPLine(pt1.X, pt1.Y, pt2.X, pt2.Y));
		OutLinePts->Add(Point(pt1.X, pt1.Y));
	}
}
 
CPRect::~CPRect()
{

}
