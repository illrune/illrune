#pragma once

#include "GameDev.h"
#include "Object.h"
#include "Water.h"

class Waterbomb : public Object
{
public :
	Waterbomb();
	virtual ~Waterbomb();

public :
   virtual void Input(DWORD);
   virtual void Update(DWORD);
   virtual void Draw(HDC);

   virtual bool IsCollide(Object* );

   virtual void DoBreak();

private :
	int rolling;
	bool roll;
	int rollcount;

	int roll_dt;
	int roll_delay;
};