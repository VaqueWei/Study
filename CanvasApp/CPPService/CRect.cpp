#include "CRect.h"

CRect::CRect(CP2 pos, double width, double length)
{
	OtmopLine.clear();
	OtmopLine.push_back(CLine(pos, CP2(pos.X + width, pos.Y)));
	OtmopLine.push_back(CLine(CP2(pos.X + width, pos.Y), CP2(pos.X + width, pos.Y+length)));
	OtmopLine.push_back(CLine(CP2(pos.X + width, pos.Y + length), CP2(pos.X, pos.Y+length)));
	OtmopLine.push_back(CLine(CP2(pos.X, pos.Y + length), pos));

	OutLinePts.clear();
	OutLinePts.push_back(pos);
	OutLinePts.push_back(CP2(pos.X + width, pos.Y));
	OutLinePts.push_back(CP2(pos.X + width, pos.Y + length));
	OutLinePts.push_back(CP2(pos.X, pos.Y + length));
	Transform = CTransform2(OutLinePts);
}

CRect::~CRect()
{

}
