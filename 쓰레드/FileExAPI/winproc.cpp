#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static FileEx fe(_T("D:"));
	static Point ptMouse;

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
	else if (uMsg == WM_MOUSEMOVE)
	{
		::GetCursorPos(&ptMouse);
		ptMouse = ptMouse.ToClient(hWnd);

		RECT rc;
		::GetClientRect(hWnd,&rc);

		if (ptMouse.x <= 500 && ptMouse.y < (fe.GetSize() * 25))
		{
			fe.mouse(ptMouse.y);
		}

		::InvalidateRect(hWnd,&rc,TRUE);

		return 0;
	}
	else if (uMsg == WM_LBUTTONDOWN)
	{
		RECT rc;
		::GetClientRect(hWnd,&rc);

		if (ptMouse.x <= 500 && ptMouse.y < (fe.GetSize() * 25))
		{
			fe.mouse(ptMouse.y);
			fe.enter();
		}

		::InvalidateRect(hWnd,&rc,TRUE);

		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}