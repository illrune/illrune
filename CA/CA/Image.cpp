#include "Image.h"

Image::Image()
: hBitmap(NULL)
{
}
Image::~Image()
{
	if (hBitmap)
	{
		::DeleteObject(hBitmap);
		hBitmap = NULL;
	}
}

bool Image::Load(LPCTSTR szFileName)
{
	if (!_load_detail(szFileName))
		return false;

	BITMAP bm;
	::GetObject(hBitmap, sizeof(BITMAP), &bm);

	rcSrc = Rect(0,0,bm.bmWidth,bm.bmHeight);
	rcDest = rcSrc;

	return true;
}
bool Image::Load(LPCTSTR szFileName, const Rect& rc)
{
	if (!_load_detail(szFileName))
		return false;

	rcSrc = rc;
	rcDest = rcSrc;

	return true;
}
void Image::Draw(HDC hdc)
{
	HDC hBitmapDC = ::CreateCompatibleDC(hdc);
	HBITMAP hOld = ::Select(hBitmapDC, hBitmap);

	::StretchBlt(hdc, rcDest.left, rcDest.top,
		rcDest.width(), rcDest.height(),
		hBitmapDC, rcSrc.left, rcSrc.top,
		rcSrc.width(), rcSrc.height(), SRCCOPY);

	::Select(hBitmapDC, hOld);
	::DeleteDC(hBitmapDC);
}
void Image::SetRect(const Rect& rc)
{
	rcDest = rc;
}
bool Image::_load_detail(LPCTSTR szFileName)
{
	hBitmap = (HBITMAP)::LoadImage(NULL, szFileName,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_SHARED);
	if (hBitmap == NULL)
		return false;

	return true;
}
