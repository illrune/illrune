#include "Power.h"

Power::Power()
: Object(OBJ_ITEM_COUNT, true)
{
}
Power::~Power()
{
}
void Power::Input(DWORD)
{
}
void Power::Update(DWORD)
{
}
void Power::Draw(HDC hdc)
{
	HBRUSH hBrush = ::CreateSolidBrush(RGB(0,200,255));
	HBRUSH hOldBrush = ::Select(hdc,hBrush);

	::Ellipse(hdc, pos().x - 10, pos().y - 15,
		pos().x + 10, pos().y + 15);

	::Select(hdc,hOldBrush);
	::DeleteObject(hBrush);
}

bool Power::IsCollide(Object* obj)
{
	// TODO
	//if (obj->type() == OBJ_WATER)
	//{
	//	Point pt = obj->GetPosition();

	//	return Collision(pos(), 20, pt);
	//}
	if (obj->type() == OBJ_CHARACTER)
	{
		Point pt = obj->GetPosition();

		if (Collision(pos(), 20, pt))
		{
		  obj->PowerUp();
		  return true;
		}
	}

	return false;
}

void Power::DoBreak()
{
	SetNeedToClean();
}
