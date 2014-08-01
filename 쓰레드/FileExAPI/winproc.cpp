#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static FileEx fe(_T("D:"));

	if (uMsg == WM_DESTROY)
	{
		::PostQuitMessage(0);
		return 0;
	}
	else if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(hWnd, &ps);

		hdc << fe;

		::EndPaint(hWnd,&ps);

		return 0;
	}
	else if (uMsg == WM_KEYDOWN)
	{
		RECT rc;
		::GetClientRect(hWnd,&rc);

		if (wParam == VK_UP)
		{
			fe.up();
		}
		else if (wParam == VK_DOWN)
		{
			fe.down();
		}
		else if (wParam == VK_RETURN)
		{
			fe.enter();
		}

		::InvalidateRect(hWnd,&rc,TRUE);

		return 0;
	}
	else if (uMsg == WM_LBUTTONDOWN)
	{
		POINT ptMouse;
		::GetCursorPos(&ptMouse);
		::ScreenToClient(hWnd, &ptMouse);

		fe.setpos(ptMouse);

		RECT rc;
		::GetClientRect(hWnd,&rc);
		::InvalidateRect(hWnd,&rc,TRUE);

		return 0;
	}
	else if (uMsg == WM_LBUTTONDBLCLK)
	{
		POINT ptMouse;
		::GetCursorPos(&ptMouse);
		::ScreenToClient(hWnd, &ptMouse);

		if (fe.setpos(ptMouse))
			fe.enter();
	
		RECT rc;
		::GetClientRect(hWnd,&rc);
		::InvalidateRect(hWnd,&rc,TRUE);

		return 0;
	}
	else if (uMsg == WM_RBUTTONDOWN)
	{
		LOGFONT lFont;

		CHOOSEFONT chFont;
		chFont.lStructSize = sizeof(CHOOSEFONT);
		chFont.Flags = CF_EFFECTS;
		chFont.hwndOwner = hWnd;
		chFont.lpLogFont = &lFont;

		if (::ChooseFont(&chFont))
		{
			fe.SetFontInfo(lFont, chFont.rgbColors);

			RECT rc;
			::GetClientRect(hWnd,&rc);
			::InvalidateRect(hWnd,&rc,TRUE);
		}

		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}