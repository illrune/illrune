#include "Water.h"

Water::Water()
: Object(OBJ_WATER, true)
, water_dt(0), water_stay(500)
{
}
Water::~Water()
{
}
void Water::Input(DWORD)
{
}
void Water::Update(DWORD tick)
{
	water_dt += tick;

	if (water_dt > water_stay)
	{
		DoBreak();
	}
}
void Water::Draw(HDC hdc)
{
	HBRUSH hBrush = ::CreateSolidBrush(RGB(0,200,240));
	HBRUSH hOldBrush = ::Select(hdc,hBrush);

	::Rectangle(hdc, pos().x - 18, pos().y - 18, pos().x + 18, pos().y + 18);

	::Select(hdc,hOldBrush);
	::DeleteObject(hBrush);
}

bool Water::IsCollide(Object* obj)
{
	// TODO
	if (obj->type() == OBJ_CHARACTER)
	{		
	   Point pt = obj->GetPosition();
	   
	   return Collision(pos(), 20, pt);
	}
	else if (obj->type() == OBJ_BOX)
	{
		Point pt = obj->GetPosition();

		return Collision(pos(), 20, pt);
	}
	else if (obj->type() == OBJ_WATERBOMB)
	{
		Point pt = obj->GetPosition();

		return Collision(pos(), 20, pt);
	}

	return false;
}

void Water::DoBreak()
{
	SetNeedToClean();
}