#pragma once

#include "GameDev.h"
#include "Object.h"
#include "Character.h"
#include "Water.h"

class Count : public Object
{
public :
   Count();
   virtual ~Count();

public :
   virtual void Input(DWORD);
   virtual void Update(DWORD);
   virtual void Draw(HDC);

   virtual bool IsCollide(Object* );

   virtual void DoBreak();
};