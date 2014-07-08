#include "Water.h"

Water::Water()
: Object(OBJ_WATER, true), power(1)
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
	if(tick >= 500)
	{
		DoBreak();
	}
}
void Water::Draw(HDC hdc)
{
	HBRUSH hBrush = ::CreateSolidBrush(RGB(50,50,200));
	HBRUSH hOldBrush = ::Select(hdc,hBrush);

	::Rectangle(hdc, pos().x - 18, pos().y - 18, pos().x + 18, pos().y - 18);

	for (int i = 0; i < power; i++)
	{
		// UP
		::Rectangle(hdc, pos().x - 18, pos().y - 18 - 20*i, pos().x + 18, pos().y - 18 - 20*i);
		// DOWN
		::Rectangle(hdc, pos().x - 18, pos().y - 18 + 20*i, pos().x + 18, pos().y - 18 + 20*i);
		// LEFT
		::Rectangle(hdc, pos().x - 18 - 20*i, pos().y - 18, pos().x + 18 - 20*i, pos().y - 18);
		// RIGHT
		::Rectangle(hdc, pos().x - 18 + 20*i, pos().y - 18, pos().x + 18 + 20*i, pos().y - 18);
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