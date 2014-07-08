#pragma once

#include "GameDev.h"
#include "Object.h"

class Power : public Object
{
public :
   Power();
   virtual ~Power();

public :
   virtual void Input(DWORD);
   virtual void Update(DWORD);
   virtual void Draw(HDC);

   virtual bool IsCollide(Object* );

   virtual void DoBreak();
};