#include "ColorArea.h"

ColorArea::ColorArea()
: size(0)
{
	color[BLACK] = 0x00000000;
	color[RED] = 0x000000FF;
	color[GREEN] = 0x0000FF00;
	color[BLUE] = 0x00FF0000;
	color[YELLOW] = 0x0000FFFF;
	color[MAGENTA] = 0x00FF00FF;
	color[CYAN] = 0x00FFFF00;
	color[WHITE] = 0x00FFFFFF;

	rect.left = 0;
	rect.top = 0;
	rect.right = 0;
	rect.bottom = 0;
}
ColorArea::~ColorArea()
{
}

void ColorArea::SetSize(const int& s)
{
	size = s;
}
void ColorArea::SetClientRect(RECT& rc)
{
	rect = rc;
}
void ColorArea::Draw(HDC hdc)
{
	// 색 지정 영역 그리기
	RECT rcclr = {rect.right - size, rect.top + size/2, rect.right, rcclr.top + size};				
	for (int i = 0; i < 8; i++)
	{
		HBRUSH hBrush = ::CreateSolidBrush(color[i]);
		HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);

		::Rectangle(hdc, rcclr.left, rcclr.top, rcclr.right, rcclr.bottom);

		::SelectObject(hdc,hOldBrush);
		::DeleteObject(hBrush);

		rcclr.top = rcclr.top + size;
		rcclr.bottom = rcclr.top + size;
	}
}

COLORREF ColorArea::GetColor(const int& nColorNumber)
{
	return color[nColorNumber];
}
int ColorArea::GetColorNumber(const int& n)
{
	return (n - size/2)/size;
}