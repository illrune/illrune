#pragma once

#include "GameDev.h"
#include "Object.h"

class Block : public Object
{
public :
	Block();
	virtual ~Block();

public :
   virtual void Input(DWORD);
   virtual void Update(DWORD);
   virtual void Draw(HDC);

   virtual bool IsCollide(Object* );
};