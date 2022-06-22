#include "CPLine.h"


CPLine::CPLine(double x1, double y1, double x2, double y2) {
	x1 = x1 + 740;
	y1 = y1 + 375;
	x2 = x2 + 740;
	y2 = y2 + 375;
	CLine line = CLine(CP2(x1,y1),CP2(x2,y2));
	X1 = line.StartPt.X, X2 = line.EndPt.X, Y1 = line.StartPt.Y, Y2 = line.EndPt.Y;
	Shape = gcnew Line();
	Shape->StrokeThickness = 3;
	Shape->X1 = X1;
	Shape->X2 = X2;
	Shape->Y1 = Y1;
	Shape->Y2 = Y2;
}

CPLine::~CPLine() {

}

