#include "CLine.h"

CLine::CLine()
{
	StartPt = CP2(0,0), EndPt = CP2(0,0);
	Length = 0;
}
CLine::CLine(CP2 startPt, CP2 endPt)
{
	StartPt = startPt, EndPt = endPt;
	double A = StartPt.X - EndPt.X;
	double B = StartPt.Y - EndPt.Y;
	Length = sqrt(A * A + B * B);
}

CLine::~CLine()
{

}