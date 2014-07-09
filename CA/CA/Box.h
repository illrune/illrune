#pragma once

#include "GameDev.h"
#include "Object.h"
#include "Collision.h"

#include "Count.h"
#include "Power.h"
#include "Speed.h"

class Box : public Object
{
public :
	Box();
	virtual ~Box();

public :
   virtual void Input(DWORD);
   virtual void Update(DWORD);
   virtual void Draw(HDC);

   virtual bool IsCollide(Object* );

   virtual void DoBreak();
};