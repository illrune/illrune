#pragma once

#include "GameDev.h"
#include "Object.h"

class Water : public Object
{
public :
	Water();
	virtual ~Water();

public :
   virtual void Input(DWORD);
   virtual void Update(DWORD);
   virtual void Draw(HDC);

   virtual bool IsCollide(Object* );

   virtual void DoBreak();

private :
	int water_dt;
	int water_stay;
};