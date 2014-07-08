#include "Water.h"

Water::Water()
: Object(OBJ_WATER, true), power(1)
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

	for (int i = 0; i < power; i++)
	{
		// UP
		::Rectangle(hdc, pos().x - 18, pos().y - 18 - 40*(i+1), pos().x + 18, pos().y + 18 - 40*(i+1));
		// DOWN
		::Rectangle(hdc, pos().x - 18, pos().y - 18 + 40*(i+1), pos().x + 18, pos().y + 18 + 40*(i+1));
		// LEFT
		::Rectangle(hdc, pos().x - 18 - 40*(i+1), pos().y - 18, pos().x + 18 - 40*(i+1), pos().y + 18);
		// RIGHT
		::Rectangle(hdc, pos().x - 18 + 40*(i+1), pos().y - 18, pos().x + 18 + 40*(i+1), pos().y + 18);
	}

	::Select(hdc,hOldBrush);
	::DeleteObject(hBrush);
}

bool Water::IsCollide(Object* obj)
{
	// TODO
	return false;
}

void Water::DoBreak()
{
	SetNeedToClean();
}