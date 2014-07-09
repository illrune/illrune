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
	HBRUSH hBrush = ::CreateSolidBrush(RGB(255,200,0));
	HBRUSH hOldBrush = ::Select(hdc,hBrush);

	::Ellipse(hdc, pos().x - 15, pos().y - 15,
		pos().x + 15, pos().y + 15);

	::Select(hdc,hOldBrush);
	::DeleteObject(hBrush);
}

bool Speed::IsCollide(Object* obj)
{
	// TODO
	return false;
}

void Speed::DoBreak()
{
	SetNeedToClean();
}