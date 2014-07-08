#include "Waterbomb.h"

Waterbomb::Waterbomb()
: Object(OBJ_WATERBOMB, true), rolling(20), roll(true), rollcount(0)
, roll_dt(0), roll_delay(30)
{
}
Waterbomb::~Waterbomb()
{
}
void Waterbomb::Input(DWORD)
{
}
void Waterbomb::Update(DWORD tick)
{
	if (roll_dt >= roll_delay)
	{
		if(roll)
			rolling -= 1;
		else
			rolling += 1;

		if(rolling <= 15)
		{
			roll = false;
			rollcount++;
		}
		if(rolling >= 20)
			roll = true;

		roll_dt = 0;
	}

	roll_dt += tick;
	
	if (rollcount >= 10)
		DoBreak();
}
void Waterbomb::Draw(HDC hdc)
{
	HBRUSH hBrush = ::CreateSolidBrush(RGB(0,200,255));
	HBRUSH hOldBrush = ::Select(hdc,hBrush);

	::Ellipse(hdc, pos().x - rolling, pos().y - rolling,
		pos().x + rolling, pos().y + rolling);

	::Select(hdc,hOldBrush);
	::DeleteObject(hBrush);
}

bool Waterbomb::IsCollide(Object* obj)
{
	// TODO
	return false;
}

void Waterbomb::DoBreak()
{
	Water* pWater= new Water;

	pWater->SetObjectPosition(pos());

	ObjectDepot.push(pWater);

	SetNeedToClean();
}