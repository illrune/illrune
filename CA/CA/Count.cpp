#include "Count.h"

Count::Count()
: Object(OBJ_ITEM_COUNT, true)
{
}
Count::~Count()
{
}
void Count::Input(DWORD)
{
}
void Count::Update(DWORD)
{
}
void Count::Draw(HDC)
{
}

bool Count::IsCollide(Object* obj)
{
	// TODO
	return false;
}

void Count::DoBreak()
{
	SetNeedToClean();
}