#pragma once
#include <math.h>
#include "CP2.h"
class CLine
{
public:
	CLine();
	CLine(CP2 startPt, CP2 endPt);
	~CLine();
public:
	double Length;
	CP2 StartPt;
	CP2 EndPt;
};

