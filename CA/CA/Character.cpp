#include "Character.h"

Character::Character()
: lock_dt(0), lock_delay(2000)
, st(0), dt(0)
, color(RGB(255,255,255)), colorvalue(0), size(20), locked(false), moveable(true)
, bomb_dt(0), bomb_delay(200)
, key_allocate(VK_SPACE), key_item_use(VK_LCONTROL)
, key_up(VK_UP), key_down(VK_DOWN), key_left(VK_LEFT), key_right(VK_RIGHT)
, Object(OBJ_CHARACTER, true)
, direction(0.f,0.f)
, speed(2.f), count(30), power(2), nowcount(0)
{
	st = ::GetTickCount();
}
Character::~Character()
{
}

void Character::Input(DWORD tick)
{

	// item_use
	if ((::GetAsyncKeyState(key_item_use) & 0x8000) == 0x8000)
	{
		color = RGB(255,255,255);
		colorvalue = 0;
		lock_dt = 0;
		locked = false;
	}
	if (!locked) // °¤Èù »óÅÂ°¡ ¾Æ´Ò¶§¸¸ Á¶ÀÛ°¡´É
	{
		// allocate
		if ((::GetAsyncKeyState(key_allocate) & 0x8000) == 0x8000)
		{
			if(nowcount <= count)
			{
				if (bomb_dt >= bomb_delay)
				{
					Waterbomb* pWaterbomb= new Waterbomb;

					pWaterbomb->SetObjectPosition(pos());
					pWaterbomb->SetPower(power);

					ObjectDepot.push(pWaterbomb);
					nowcount++;

					bomb_dt = 0;
				}

				bomb_dt += tick;
			}
		}

		// Move

		if ((::GetAsyncKeyState(key_up) & 0x8000) == 0x8000)
		{
			if (pos().y > clientrc.top + size)
			{
				direction = Vector(0.f,-speed);
				pos() = pos() + direction;
			}
		}
		else if ((::GetAsyncKeyState(key_down) & 0x8000) == 0x8000)
		{
			if (pos().y < clientrc.bottom - size)
			{
				direction = Vector(0.f,speed);
				pos() = pos() + direction;
			}
		}
		else if ((::GetAsyncKeyState(key_left) & 0x8000) == 0x8000)
		{
			if (pos().x > clientrc.left + size)
			{
				direction = Vector(-speed,0.f);
				pos() = pos() + direction;
			}
		}
		else if ((::GetAsyncKeyState(key_right) & 0x8000) == 0x8000)
		{
			if (pos().x < clientrc.right - size)
			{
				direction = Vector(speed,0.f);
				pos() = pos() + direction;
			}
		}
	}

	//::GetKeyState();
	//::GetKeyboardState();
}
void Character::Update(DWORD tick)
{
	if(locked)
	{
		color = RGB(255-colorvalue, 255-colorvalue, 255-colorvalue);

		if (lock_dt >= lock_delay)
		{
			colorvalue++;

			if(colorvalue >= 255)
				SetNeedToClean();
		}

		lock_dt += tick;
	}
}
void Character::Draw(HDC hdc)
{
	HBRUSH hBrush = ::CreateSolidBrush(color);
	HBRUSH hOldBrush = ::Select(hdc,hBrush);

	::Ellipse(hdc, pos().x - size, pos().y - size,
		pos().x + size, pos().y + size);

	::Select(hdc,hOldBrush);
	::DeleteObject(hBrush);
}

bool Character::IsCollide(Object* obj)
{
	// ¹°¿¡ ¸ÂÀ½
   if (obj->type() == OBJ_WATER)
   {		
	   Point pt = obj->GetPosition();
	   
	   return Collision(pos(), size, pt);
   }
	//¾ÆÀÌÅÛ(°¹¼ö)À» È¹µæÇÔ
   else if (obj->type() == OBJ_ITEM_COUNT)
   {
	   obj->IsCollide(this);
   }
	//¾ÆÀÌÅÛ(ÆÄ¿ö)À» È¹µæÇÔ
   else if (obj->type() == OBJ_ITEM_POWER)
   {
	   obj->IsCollide(this);
   }
	//¾ÆÀÌÅÛ(½ºÇÇµå)À» È¹µæÇÔ
   else if (obj->type() == OBJ_ITEM_SPEED)
   {
	   obj->IsCollide(this);
   }

   return false;
}
void Character::DoBreak()
{
	if (!locked)
		locked = true;
}
void Character::SetClientRect(Rect& rc)
{
	clientrc = rc;
}
void Character::SetKeyMapping(const int& item_use,
							  const int& allocate,
							  const int& up,
							  const int& down,
							  const int& left,
							  const int& right)
{
	key_item_use = item_use;
	key_allocate = allocate;
	key_up = up;
	key_down = down;
	key_left = left;
	key_right = right;
}
void Character::SpeedUp()
{
	speed += 1.f;
}
void Character::CountUp()
{
	count++;
}
void Character::PowerUp()
{
	power++;
}