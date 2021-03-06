#include "Count.h"

Count::Count()
: Object(OBJ_ITEM_COUNT, true)
{
}
Count::~Count()
{
}
void Count::Input(DWORD)
{
}
void Count::Update(DWORD)
{
}
void Count::Draw(HDC hdc)
{
	HBRUSH hBrush = ::CreateSolidBrush(RGB(0,0,200));
	HBRUSH hOldBrush = ::Select(hdc,hBrush);

	::Ellipse(hdc, pos().x - 15, pos().y - 15,
		pos().x + 15, pos().y + 15);

	::Select(hdc,hOldBrush);
	::DeleteObject(hBrush);
}

bool Count::IsCollide(Object* obj)
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
		  obj->CountUp();
		  return true;
		}
	}

	return false;
}

void Count::DoBreak()
{
	SetNeedToClean();
}