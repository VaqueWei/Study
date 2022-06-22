#pragma once
#include "CLine.h"

using namespace System::Windows::Controls;
using namespace System::Windows::Shapes;
using namespace System::Windows::Media;
using namespace System::Windows;
using namespace System::Collections::Generic;
using namespace System;

public ref class CPLine
{
public:
	CPLine(double x1, double y1, double x2, double y2);
	~CPLine();
public:
	double Length;
	double X1, X2, Y1, Y2;
	Line^ Shape;
};



