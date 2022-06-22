#pragma once
#include "CPLine.h"
#include "CRect.h"
#include "CPTransform2.h"
#include "TopCpLineShape.h"

public ref class CPRect:public TopCpLineShape
{
public:
	CPRect(Point^ pos, double width,double length);
	~CPRect();
public:
	List<Point>^ OutLinePts;
};

