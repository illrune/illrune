#pragma once

#include <windows.h>
#include <tchar.h>
#include "BaseType.h"
#include "Utility.hpp"

class Image
{
public :
	Image();
	virtual ~Image();

	bool Load(LPCTSTR szFileName);
	bool Load(LPCTSTR szFileName, const Rect& rc);

	virtual void Draw(HDC hdc);

	void SetRect(const Rect& rc);
private :
	bool _load_detail(LPCTSTR szFileName);
protected :
	HBITMAP hBitmap;

	Rect rcSrc;
	Rect rcDest;
};