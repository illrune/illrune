#include "Speed.h"

Speed::Speed()
: Object(OBJ_ITEM_SPEED, true)
{
}
Speed::~Speed()
{
}
void Speed::Input(DWORD)
{
}
void Speed::Update(DWORD)
{
}
void Speed::Draw(HDC hdc)
{
	HBRUSH hBrush = ::CreateSolidBrush(RGB(255,0,0));
	HBRUSH hOldBrush = ::Select(hdc,hBrush);

	::Ellipse(hdc, pos().x - 15, pos().y - 15,
		pos().x + 15, pos().y + 15);

	::Select(hdc,hOldBrush);
	::DeleteObject(hBrush);
}

bool Speed::IsCollide(Object* obj)
{
	// TODO
	if (obj->type() == OBJ_WATER)
	{
		Point pt = obj->GetPosition();

		return Collision(pos(), 20, pt);
	}
	else if (obj->type() == OBJ_CHARACTER)
	{
		Point pt = obj->GetPosition();

		if (Collision(pos(), 20, pt))
		{
		  obj->SpeedUp();
		  return true;
		}
	}
	return false;
}

void Speed::DoBreak()
{
	SetNeedToClean();
}