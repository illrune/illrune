#pragma once

#include <windows.h>

enum color_id
{
	BLACK,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	MAGENTA,
	CYAN,
	WHITE,
};

class ColorArea
{
public :
	ColorArea();
	~ColorArea();

public :
	void SetSize(const int& s);
	void SetClientRect(RECT& rc);
	void Draw(HDC hdc);
	
	COLORREF GetColor(const int& nColorNumber);
	int GetColorNumber(const int& n);

private :
	COLORREF color[8];
	int size;
	RECT rect;
};