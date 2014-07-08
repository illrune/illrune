#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DWORD st = 0;
	static DWORD dt = 0;
	static DWORD update_dt = 0;
	static DWORD update_delay = 10;

	if (uMsg == WM_CREATE)
	{
		backbuffer.Attach(hWnd);
		ObjectDepot.Attach(hWnd);

		Rect rc;
		::GetClientRect(hWnd,&rc);

		// Character Input ////////

		Character* pCharacter = new Character;
		pCharacter->SetPosition(Point(rc.width()/4, rc.center().y));
		pCharacter->SetKeyMapping(VK_LCONTROL, VK_LSHIFT, 'W','S','A','D');
		pCharacter->SetClientRect(rc);

		ObjectDepot.push(pCharacter);

		////////////////////////////

		pCharacter = new Character;
		pCharacter->SetPosition(Point(rc.width()*3/4, rc.center().y));
		pCharacter->SetKeyMapping(VK_RCONTROL, VK_RSHIFT, VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT);
		pCharacter->SetClientRect(rc);

		ObjectDepot.push(pCharacter);
		
		/////////////////////////////

		st = ::GetTickCount();
		::SetTimer(hWnd, 0, 10, NULL);
		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		// TODO
		ObjectDepot.clear();

		::KillTimer(hWnd, 0);
		backbuffer.Detach();
		::PostQuitMessage(0);
		return 0;
	}
	else if (uMsg == WM_PAINT)
	{
		Rect rc;
		::GetClientRect(hWnd, &rc);

		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(hWnd, &ps);

		backbuffer << RGB(100,100,255);

		// TODO
		ObjectDepot.Draw(backbuffer);

		backbuffer.Draw();
		::EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_ERASEBKGND)
	{
		return 1;
	}
	else if (uMsg == WM_MOUSEMOVE)
	{
		return 0;
	}
	else if (uMsg == WM_TIMER)
	{
		// TODO
		ObjectDepot.Input(dt);
		ObjectDepot.Update(dt);

		dt = ::GetTickCount() - st;
		st = ::GetTickCount();

		Rect rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);
		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}
