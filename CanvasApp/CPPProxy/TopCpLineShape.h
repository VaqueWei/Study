#pragma once
#include "CPLine.h"
#include "NCollection_Haft.h"
#include "SurfaceUnit.h"
#include "CPSurfaceUnit.h"

using namespace System::Collections::Generic;
using namespace System::Windows;
using namespace System::Windows::Media::Media3D;

public ref class TopCpLineShape
{
public:
	List<CPLine^>^ OutLines;
	List<Point3D>^ Pts;
	List<CPSurfaceUnit^>^ Mesh;
};

