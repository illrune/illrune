#pragma once

#include "GameDev.h"
#include "Object.h"
#include "Character.h"
#include "Water.h"

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