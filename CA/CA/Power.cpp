#include "Power.h"

Power::Power()
: Object(OBJ_ITEM_COUNT, true)
{
}
Power::~Power()
{
}
void Power::Input(DWORD)
{
}
void Power::Update(DWORD)
{
}
void Power::Draw(HDC)
{
}

bool Power::IsCollide(Object* obj)
{
	// TODO
	return false;
}

void Power::DoBreak()
{
	SetNeedToClean();
}
