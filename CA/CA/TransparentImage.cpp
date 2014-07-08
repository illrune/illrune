#include "TransparentImage.h"

TransparentImage::TransparentImage()
: color(RGB(0,0,0))
{
}
TransparentImage::~TransparentImage()
{
}

void TransparentImage::Draw(HDC hdc)
{
	HDC hBitmapDC = ::CreateCompatibleDC(hdc);
	HBITMAP hOld = ::Select(hBitmapDC, hBitmap);

	::GdiTransparentBlt(hdc, rcDest.left, rcDest.top,
		rcDest.width(), rcDest.height(),
		hBitmapDC, rcSrc.left, rcSrc.top,
		rcSrc.width(), rcSrc.height(), color);

	::Select(hBitmapDC, hOld);
	::DeleteDC(hBitmapDC);
}

void TransparentImage::SetColor(const COLORREF& clr)
{
	color = clr;
}
