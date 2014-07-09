#include "Box.h"

Box::Box()
: Object(OBJ_BOX, true)
{
}
Box::~Box()
{
}
void Box::Input(DWORD)
{
}
void Box::Update(DWORD)
{
}
void Box::Draw(HDC hdc)
{
	HBRUSH hBrush = ::CreateSolidBrush(RGB(220,180,80));
	HBRUSH hOldBrush = ::Select(hdc,hBrush);

	::Rectangle(hdc, pos().x - 20, pos().y - 20, pos().x + 20, pos().y + 20);

	::Select(hdc,hOldBrush);
	::DeleteObject(hBrush);
}

bool Box::IsCollide(Object* obj)
{
	// TODO
	if (obj->type() == OBJ_WATER)
	{
		Point pt = obj->GetPosition();

		return Collision(pos(), 10, pt);
	}
	return false;
}

void Box::DoBreak()
{
	// 상자가 부서진 후 5분의 1 확률로 아이템이 생성

	// 갯수 아이템 생성
	if (rand()%5 == 0)
	{
		Count* pCount= new Count;

		pCount->SetObjectPosition(pos());

		ObjectDepot.push(pCount);
	}
	// 파워 아이템 생성
	else if (rand()%5 == 1)
	{
		Power* pPower= new Power;

		pPower->SetObjectPosition(pos());

		ObjectDepot.push(pPower);
	}
	// 스피드 아이템 생성
	else if (rand()%5 == 2)
	{
		Speed* pSpeed= new Speed;

		pSpeed->SetObjectPosition(pos());

		ObjectDepot.push(pSpeed);
	}

	// 그 외에는 빈 상자

	SetNeedToClean();
}