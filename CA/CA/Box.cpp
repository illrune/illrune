#include "Box.h"

Box::Box()
: Object(OBJ_BOX, true)
{
}
Box::~Box()
{
}
void Box::Input(DWORD)
{
}
void Box::Update(DWORD)
{
}
void Box::Draw(HDC)
{
}

bool Box::IsCollide(Object* obj)
{
	// TODO
	return false;
}

void Box::DoBreak()
{
	SetNeedToClean();
}