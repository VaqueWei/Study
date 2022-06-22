#include "CP3.h"

CP3::CP3()
{
	X = 0, Y = 0, Z = 0, W = 1;
}

CP3::CP3(double x, double y, double z, double w)
{
	X = x, Y = y, Z = z;
	W = w;
}

CP3::~CP3()
{
}
