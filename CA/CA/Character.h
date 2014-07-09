#pragma once

#include <windows.h>
#include "GameDev.h"
#include "Object.h"
#include "Waterbomb.h"
#include "Collision.h"

class Character : public Object
{
public :
	Character();
	virtual ~Character();

public :
	virtual void Input(DWORD);
	virtual void Update(DWORD);
	virtual void Draw(HDC);

	virtual bool IsCollide(Object* );

	virtual void DoBreak();
	void SetClientRect(Rect& rc);

	void SetKeyMapping(const int& item_use,
					   const int& allocate,
					   const int& up,
					   const int& down,
					   const int& left,
					   const int& right);
	void SpeedUp();
	void CountUp();
	void PowerUp();

private :
	DWORD st;
	DWORD dt;
	int lock_dt;
	int lock_delay;

	COLORREF color;
	int colorvalue;
	int size;
	bool locked;

	Rect clientrc;
	int bomb_dt;
	int bomb_delay;

	int key_item_use;
	int key_allocate;
	int key_up;
	int key_down;
	int key_left;
	int key_right;

	Vector direction;

	float speed;
	int count;
	int power;
};