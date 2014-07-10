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
void Block::Draw(HDC hdc)
{
	HBRUSH hBrush = ::CreateSolidBrush(RGB(210,220,255));
	HBRUSH hOldBrush = ::Select(hdc,hBrush);

	::Rectangle(hdc, pos().x - 20, pos().y - 20,
		pos().x + 20, pos().y + 20);

	::Select(hdc,hOldBrush);
	::DeleteObject(hBrush);
}

bool Block::IsCollide(Object* obj)
{
	// TODO
	return false;
}