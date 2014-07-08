#include "Character.h"

Character::Character()
: size(20)
, bomb_dt(0), bomb_delay(200)
, key_allocate(VK_SPACE), key_item_use(VK_LCONTROL)
, key_up(VK_UP), key_down(VK_DOWN), key_left(VK_LEFT), key_right(VK_RIGHT)
, Object(OBJ_CHARACTER, true)
, direction(0.f,0.f)
, speed(2.f), count(1), power(1)
{
}
Character::~Character()
{
}

void Character::Input(DWORD tick)
{
	// allocate, item_use
	if ((::GetAsyncKeyState(key_allocate) & 0x8000) == 0x8000)
	{
		if (bomb_dt >= bomb_delay)
		{
			Waterbomb* pWaterbomb= new Waterbomb;

			pWaterbomb->SetObjectPosition(pos());

			ObjectDepot.push(pWaterbomb);

			bomb_dt = 0;
		}
		bomb_dt += tick;
	}
	if ((::GetAsyncKeyState(key_item_use) & 0x8000) == 0x8000)
	{
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

	//::GetKeyState();
	//::GetKeyboardState();
}
void Character::Update(DWORD)
{
}
void Character::Draw(HDC hdc)
{
	::Ellipse(hdc, pos().x - size, pos().y - size,
		pos().x + size, pos().y + size);
}

bool Character::IsCollide(Object* obj)
{
   if (obj->type() == OBJ_ITEM_SPEED)
   {
      //Bullet* pBullet = dynamic_cast<Bullet*>(obj);
      //Point pt = pBullet->GetPosition();
      //LONG r = pBullet->GetRadius();

      //return Collision(pos(), radius, pt, r);
   }
   //else if (obj->type() == OBJ_BLOCK)
   //{
   //   return obj->IsCollide(this);
   //}

   return false;
}
void Character::DoBreak()
{
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
	speed += 0.5f;
}
void Character::CountUp()
{
	count++;
}
void Character::PowerUp()
{
	power++;
}