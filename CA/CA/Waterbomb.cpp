#include "Waterbomb.h"

Waterbomb::Waterbomb()
: Object(OBJ_WATERBOMB, true), power(1)
, rolling(20), roll(true), rollcount(0)
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
void Waterbomb::SetPower(int WPower)
{
	power = WPower;
}
bool Waterbomb::IsCollide(Object* obj)
{
	//TODO
	if (obj->type() == OBJ_WATER)
	{
		Point pt = obj->GetPosition();

		return Collision(pos(), 20, pt);
	}

	return false;
}

void Waterbomb::DoBreak()
{
	if (!IsNeedToClean())
	{
		Water* pWater= new Water;

		pWater->SetObjectPosition(pos());

		ObjectDepot.push(pWater);

		for (int i = 0; i < power; i++)
		{
			// UP
			pWater = new Water;
			pWater->SetObjectPosition(pos() + Point(0,-(40*(i+1))));
			ObjectDepot.push(pWater);
			// DOWN
			pWater = new Water;
			pWater->SetObjectPosition(pos() + Point(0,40*(i+1)));
			ObjectDepot.push(pWater);
			// LEFT
			pWater = new Water;
			pWater->SetObjectPosition(pos() + Point(-(40*(i+1)),0));
			ObjectDepot.push(pWater);
			// RIGHT
			pWater = new Water;
			pWater->SetObjectPosition(pos() + Point(40*(i+1),0));
			ObjectDepot.push(pWater);
		}

		SetNeedToClean();
	}
}