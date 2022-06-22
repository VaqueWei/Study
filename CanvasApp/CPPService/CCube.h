#pragma once
#include "CP3.h"
#include "CFace.h"
#include "TopLineShape.h"
#include "CTransform3.h"

class CCube :public TopLineShape
{
public:
	CCube();
	CCube(CP3 position, double length,double width,double height);
	~CCube();
	void ReadPoint();
	void ReadMesh();

public:
	double Width, Length, Height;
private:
	vector<CP3> SC;
};

