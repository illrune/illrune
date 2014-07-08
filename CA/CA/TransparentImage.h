#pragma once

#include "Image.h"

class TransparentImage : public Image
{
public :
	TransparentImage();
	virtual ~TransparentImage();

	virtual void Draw(HDC hdc);

	void SetColor(const COLORREF& clr);
private :
	COLORREF color;
};