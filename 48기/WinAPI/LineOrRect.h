#pragma once

#include <windows.h>

enum type_id
{
	Line,
	Rect,
};

class LineOrRect
{
typedef unsigned int Type;

public :
	LineOrRect(const POINT ptStart, const POINT ptEnd);
	~LineOrRect();

public :
	void SetHDC(HDC dc);
	void DelHDC();
	void SetColor(const COLORREF clr);
	void SetType(const unsigned int t);

	void Draw(HDC hdc);

private :
	POINT start;
	POINT end;

	COLORREF color;
	Type type;
};