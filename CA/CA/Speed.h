#pragma once

#include "GameDev.h"
#include "Object.h"

class Speed : public Object
{
public :
   Speed();
   virtual ~Speed();

public :
   virtual void Input(DWORD);
   virtual void Update(DWORD);
   virtual void Draw(HDC);

   virtual bool IsCollide(Object* );

   virtual void DoBreak();
};