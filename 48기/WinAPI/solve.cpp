//버젼 정보
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 03-03-21, 헤더파일 써주자 seth. ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
#include <windows.h>			//윈도우 헤더파일을 인크루드
#include <list>
#include "LineOrRect.h"


//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 03-03-21, 전역변수 써주는 곳 seth. ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
HINSTANCE	g_hInst;						//전역 인스턴스의 핸들선언
HWND		g_hWnd;							//윈도우의 핸들


//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 03-03-21, 함수의 프로토 타입 써주는 곳 seth. ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);


//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 03-03-21, 윈도우 메인 함수 seth. ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam, int nCmdShow)
{
	MSG			Message;					//메세지 구조체 선언
	WNDCLASS	WndClass;					//윈도우 클래스 선언
	char  		szClassName[128] = "Seth";	//클래스 이름
	char  		szWinName[128] = "Seth";	//윈도우 이름



	g_hInst =	hInstance;		//인스턴스를 얻는다

	WndClass.cbClsExtra		= 0;									//여분메모리	
	WndClass.cbWndExtra		= 0;									//여분메모리
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	//배경색상 지정
	WndClass.hCursor		= LoadCursor(NULL,IDC_ARROW);			//커서를 읽는다
	WndClass.hIcon			= LoadIcon(NULL,IDI_APPLICATION);		//아이콘을 읽는다
	WndClass.hInstance		= hInstance;							//윈도우 클래스의 인스턴스
	WndClass.lpfnWndProc	= (WNDPROC)WndProc;						//윈도우 프로시저의 이름
	WndClass.lpszClassName	= szClassName;							//윈도우 클래스의 이름
	WndClass.lpszMenuName	= NULL;									//메뉴의 이름
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;				//윈도우의 스타일
	RegisterClass(&WndClass);										//클래스를 등록한다

	//윈도우를 만든다
	g_hWnd = CreateWindow(szClassName, szWinName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(g_hWnd, nCmdShow);
	
	/*
	while(true)
	{
        /// 메시지큐에 메시지가 있으면 메시지 처리
		if( PeekMessage( &Message, NULL, 0U, 0U, PM_REMOVE ) )
		{
			if(Message.message == WM_QUIT) break;
			TranslateMessage( &Message );
			DispatchMessage( &Message );
		}
		else
		{
			test();

		}
		/// 처리할 메시지가 없으면 Render()함수 호출
		//	Render();
	}*/

	//메세지 루프
	while(GetMessage(&Message,0,0,0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}


//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 03-03-21, 윈도우 프로시저 seth. ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT			ps;
	HDC					hdc;

	static std::list<LineOrRect*> depot;

	static RECT			rc;

	static POINT		ptMouse = {0,0};
	static POINT		pt1 = {0,0};
	static POINT		pt2 = {0,0};

	static COLORREF		clr[8];
	static int			nClrSelect = 7;

	static bool			bLeftClick = false;
	static bool			bRightClick = false;

	static const int	nRcSize = 80;
	::GetClientRect(g_hWnd,&rc);

	COLORREF clrtmp = RGB(0,0,0);
	for (int i = 0; i < 8; i++)
	{
		if (i >= 5)
		{
			if (i == 5)
				clrtmp -= 0xFF00;
			else if (i == 6)
			{
				clrtmp -= 0xFF;
			}
			else
				clrtmp = 0;
		}
		else if (i%2 == 0)
			clrtmp += 0xFF;
		else
			clrtmp = clrtmp << 8;

		clr[i] = clrtmp;
	}

	switch(iMessage)
	{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);

			// 색 지정 영역 그리기
			{
				RECT rcclr = {rc.right - nRcSize, rc.top + nRcSize/2, rc.right, rcclr.top + nRcSize};				
				for (int i = 0; i < 8; i++)
				{
					HBRUSH hBrush = ::CreateSolidBrush(clr[i]);
					HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdc,hBrush);

					::Rectangle(hdc, rcclr.left, rcclr.top, rcclr.right, rcclr.bottom);

					::SelectObject(hdc,hOldBrush);
					::DeleteObject(hBrush);

					rcclr.top = rcclr.top + nRcSize;
					rcclr.bottom = rcclr.top + nRcSize;
				}
			}

			// 리스트 안에 저장된 선과 사각형
			{
				std::list<LineOrRect*>::iterator it;
				for (it = depot.begin(); it != depot.end(); it++)
				{
					(*it)->Draw(hdc);
				}
			}

			{
				// 선택한 색으로 지정
				HBRUSH hBrush = ::CreateSolidBrush(clr[nClrSelect]);
				HPEN hPen = ::CreatePen(PS_SOLID, 1, clr[nClrSelect]);
				// 전의 색상을 저장
				HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);
				HPEN hOldPen = (HPEN)::SelectObject(hdc, hPen);

				// 현재 그리는 중인 선
				if (bLeftClick)
				{
					::MoveToEx(hdc, pt1.x, pt1.y, NULL);
					::LineTo(hdc, ptMouse.x, ptMouse.y);
				}
				// 현재 그리는 중인 사각형
				else if (bRightClick)
				{
					int left, top, right, bottom;

					left = min(pt1.x, ptMouse.x);
					top = min(pt1.y, ptMouse.y);
					right = max(pt1.x, ptMouse.x);
					bottom = max(pt1.y, ptMouse.y);

					::Rectangle(hdc, left, top, right, bottom);
				}

				// 브러시 메모리 해제
				::SelectObject(hdc,hOldBrush);
				::SelectObject(hdc,hOldPen);
				::DeleteObject(hBrush);
				::DeleteObject(hPen);
			}

			EndPaint(hWnd, &ps);
		break;
		case WM_LBUTTONDOWN:	// 왼쪽클릭(선)
			// 선 그리기
			if (ptMouse.x < rc.right - nRcSize)
			{
				bLeftClick = true;
				pt1 = ptMouse;
			}
			// 색 영역 선택
			else
			{	
				if (ptMouse.y >= nRcSize/2 && ptMouse.y <= nRcSize*8 + nRcSize/2)
					nClrSelect = (ptMouse.y - nRcSize/2)/nRcSize;
			}
		break;
		case WM_LBUTTONUP:
			// 색 선택 영역에서 클릭을 떼면 취소
			if (ptMouse.x >= rc.right - nRcSize)
			{
				bLeftClick = false;
				::InvalidateRect(g_hWnd, NULL, true);
				break;
			}

			// 선 추가
			pt2 = ptMouse;
			{
				LineOrRect* pline = new LineOrRect(pt1, pt2);
				pline->SetType(Line);
				pline->SetColor(clr[nClrSelect]);

				depot.push_back(pline);
			}
			bLeftClick = false;
			::InvalidateRect(g_hWnd, NULL, true);
		break;
		case WM_RBUTTONDOWN:	// 오른쪽클릭(사각형)
			// 색 선택 영역이 아닐때만
			if (ptMouse.x < rc.right - nRcSize)
			{
				bRightClick = true;
				pt1 = ptMouse;
			}
		break;
		case WM_RBUTTONUP:
			// 색 선택 영역에서 클릭을 떼면 취소
			if (ptMouse.x >= rc.right - nRcSize)
			{
				bRightClick = false;
				::InvalidateRect(g_hWnd, NULL, true);
				break;
			}

			// 사각형 추가
			pt2 = ptMouse;

			POINT lefttop, rightbottom;

			lefttop.x = min(pt1.x, pt2.x);
			lefttop.y = min(pt1.y, pt2.y);
			rightbottom.x = max(pt1.x, pt2.x);
			rightbottom.y = max(pt1.y, pt2.y);

			{
				LineOrRect* pRect = new LineOrRect(lefttop, rightbottom);
				pRect->SetType(Rect);
				pRect->SetColor(clr[nClrSelect]);

				depot.push_back(pRect);
			}

			bRightClick = false;
			::InvalidateRect(g_hWnd, NULL, true);
		break;
		case WM_MOUSEMOVE:
			::GetCursorPos(&ptMouse);
			::ScreenToClient(g_hWnd, &ptMouse);

			::InvalidateRect(g_hWnd, NULL, true);
		break;
		case WM_KEYDOWN:
			switch(wParam)
			{
				case VK_ESCAPE:
					PostMessage( hWnd, WM_DESTROY, 0, 0L );
				break;
			}
		break;
		case WM_DESTROY:
			{
				std::list<LineOrRect*>::iterator it;
				for (it = depot.begin(); it != depot.end(); )
				{
					delete *it;
					it = depot.erase(it);
				}
			}
			PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}


//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 03-03-21, 참고사항들 seth. ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━