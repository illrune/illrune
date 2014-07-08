#include "Block.h"

Block::Block()
: Object(OBJ_BLOCK, false)
{
}
Block::~Block()
{
}

void Block::Input(DWORD)
{
}
void Block::Update(DWORD)
{
}
void Block::Draw(HDC)
{
}

bool Block::IsCollide(Object* obj)
{
	// TODO
	return false;
}