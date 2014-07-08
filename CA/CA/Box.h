#pragma once

#include "GameDev.h"
#include "Object.h"

class Box : public Object
{
protected :
	Box();
	virtual ~Box();

public :
   virtual void Input(DWORD);
   virtual void Update(DWORD);
   virtual void Draw(HDC);

   virtual bool IsCollide(Object* );

   virtual void DoBreak();
};