#include "Speed.h"

Speed::Speed()
: Object(OBJ_ITEM_SPEED, true)
{
}
Speed::~Speed()
{
}
void Speed::Input(DWORD)
{
}
void Speed::Update(DWORD)
{
}
void Speed::Draw(HDC)
{
}

bool Speed::IsCollide(Object* obj)
{
	// TODO
	return false;
}

void Speed::DoBreak()
{
	SetNeedToClean();
}