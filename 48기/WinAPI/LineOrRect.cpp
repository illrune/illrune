#include "LineOrRect.h"

LineOrRect::LineOrRect(const POINT ptStart, const POINT ptEnd)
: start(ptStart), end(ptEnd), color(0x00000000), type(Line)
{
}
LineOrRect::~LineOrRect()
{
}
void LineOrRect::SetColor(COLORREF clr)
{
	color = clr;
}
void LineOrRect::SetType(const unsigned int t)
{
	type = t;
}

void LineOrRect::Draw(HDC hdc)
{
	HBRUSH hBrush = ::CreateSolidBrush(color);
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);

	HPEN hPen = ::CreatePen(PS_SOLID, 1, color);
	HPEN hOldPen = (HPEN)::SelectObject(hdc, hPen);

	if (type == Line)
	{
		MoveToEx(hdc, start.x, start.y, NULL);
		LineTo(hdc, end.x, end.y);
	}
	else
	{
		::Rectangle(hdc, start.x, start.y, end.x, end.y);
	}

	::SelectObject(hdc, hOldBrush);
	::DeleteObject(hBrush);

	::SelectObject(hdc, hOldPen);
	::DeleteObject(hPen);
}