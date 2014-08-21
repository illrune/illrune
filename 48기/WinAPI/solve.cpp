//���� ����
//������������������������������������������������������������������������������
// �٦��� 03-03-21, ������� ������ seth. ������
//������������������������������������������������������������������������������
#include <windows.h>			//������ ��������� ��ũ���
#include <list>
#include "LineOrRect.h"
#include "ColorArea.h"


//������������������������������������������������������������������������������
// �٦��� 03-03-21, �������� ���ִ� �� seth. ������
//������������������������������������������������������������������������������
HINSTANCE	g_hInst;						//���� �ν��Ͻ��� �ڵ鼱��
HWND		g_hWnd;							//�������� �ڵ�


//������������������������������������������������������������������������������
// �٦��� 03-03-21, �Լ��� ������ Ÿ�� ���ִ� �� seth. ������
//������������������������������������������������������������������������������
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);


//������������������������������������������������������������������������������
// �٦��� 03-03-21, ������ ���� �Լ� seth. ������
//������������������������������������������������������������������������������
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam, int nCmdShow)
{
	MSG			Message;					//�޼��� ����ü ����
	WNDCLASS	WndClass;					//������ Ŭ���� ����
	char  		szClassName[128] = "Seth";	//Ŭ���� �̸�
	char  		szWinName[128] = "Seth";	//������ �̸�



	g_hInst =	hInstance;		//�ν��Ͻ��� ��´�

	WndClass.cbClsExtra		= 0;									//���и޸�	
	WndClass.cbWndExtra		= 0;									//���и޸�
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	//������ ����
	WndClass.hCursor		= LoadCursor(NULL,IDC_ARROW);			//Ŀ���� �д´�
	WndClass.hIcon			= LoadIcon(NULL,IDI_APPLICATION);		//�������� �д´�
	WndClass.hInstance		= hInstance;							//������ Ŭ������ �ν��Ͻ�
	WndClass.lpfnWndProc	= (WNDPROC)WndProc;						//������ ���ν����� �̸�
	WndClass.lpszClassName	= szClassName;							//������ Ŭ������ �̸�
	WndClass.lpszMenuName	= NULL;									//�޴��� �̸�
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;				//�������� ��Ÿ��
	RegisterClass(&WndClass);										//Ŭ������ ����Ѵ�

	//�����츦 �����
	g_hWnd = CreateWindow(szClassName, szWinName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(g_hWnd, nCmdShow);
	
	/*
	while(true)
	{
        /// �޽���ť�� �޽����� ������ �޽��� ó��
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
		/// ó���� �޽����� ������ Render()�Լ� ȣ��
		//	Render();
	}*/

	//�޼��� ����
	while(GetMessage(&Message,0,0,0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}


//������������������������������������������������������������������������������
// �٦��� 03-03-21, ������ ���ν��� seth. ������
//������������������������������������������������������������������������������
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT			ps;
	HDC					hdc;

	static std::list<LineOrRect*> depot;

	static POINT		ptMouse = {0,0};
	static POINT		pt1 = {0,0};
	static POINT		pt2 = {0,0};

	static ColorArea	ColorDepot;
	static int			nClrSelect = 0;

	static bool			bLeftClick = false;
	static bool			bRightClick = false;

	static const int	nRcSize = 80;

	// �� ���ÿ��� �ʱ⼳��
	RECT rc;
	::GetClientRect(g_hWnd,&rc);
	ColorDepot.SetClientRect(rc);
	ColorDepot.SetSize(nRcSize);

	switch(iMessage)
	{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);

			// �� ���ÿ��� �׸���
			ColorDepot.Draw(hdc);

			// ����Ʈ �ȿ� ����� ���� �簢��
			{
				std::list<LineOrRect*>::iterator it;
				for (it = depot.begin(); it != depot.end(); it++)
				{
					(*it)->Draw(hdc);
				}
			}

			{
				// ������ ������ ����
				HBRUSH hBrush = ::CreateSolidBrush(ColorDepot.GetColor(nClrSelect));
				HPEN hPen = ::CreatePen(PS_SOLID, 1, ColorDepot.GetColor(nClrSelect));
				// ���� ������ ����
				HBRUSH hOldBrush = (HBRUSH)::SelectObject(hdc, hBrush);
				HPEN hOldPen = (HPEN)::SelectObject(hdc, hPen);

				// ���� �׸��� ���� ��
				if (bLeftClick)
				{
					::MoveToEx(hdc, pt1.x, pt1.y, NULL);
					::LineTo(hdc, ptMouse.x, ptMouse.y);
				}
				// ���� �׸��� ���� �簢��
				else if (bRightClick)
				{
					int left, top, right, bottom;

					left = min(pt1.x, ptMouse.x);
					top = min(pt1.y, ptMouse.y);
					right = max(pt1.x, ptMouse.x);
					bottom = max(pt1.y, ptMouse.y);

					::Rectangle(hdc, left, top, right, bottom);
				}

				// �귯�� �޸� ����
				::SelectObject(hdc,hOldBrush);
				::SelectObject(hdc,hOldPen);
				::DeleteObject(hBrush);
				::DeleteObject(hPen);
			}

			EndPaint(hWnd, &ps);
		break;
		case WM_LBUTTONDOWN:	// ����Ŭ��(��)
			// �� �׸���
			if (ptMouse.x < rc.right - nRcSize)
			{
				bLeftClick = true;
				pt1 = ptMouse;
			}
			// �� ���� ����
			else
			{	
				if (ptMouse.y >= nRcSize/2 && ptMouse.y <= nRcSize*8 + nRcSize/2)
					nClrSelect = ColorDepot.GetColorNumber(ptMouse.y);
			}
		break;
		case WM_LBUTTONUP:
			// �� ���� �������� Ŭ���� ���� ���
			if (ptMouse.x >= rc.right - nRcSize)
			{
				bLeftClick = false;
				::InvalidateRect(g_hWnd, NULL, true);
				break;
			}

			// �� �߰�
			pt2 = ptMouse;
			{
				LineOrRect* pline = new LineOrRect(pt1, pt2);
				pline->SetType(Line);
				pline->SetColor(ColorDepot.GetColor(nClrSelect));

				depot.push_back(pline);
			}
			bLeftClick = false;
			::InvalidateRect(g_hWnd, NULL, true);
		break;
		case WM_RBUTTONDOWN:	// ������Ŭ��(�簢��)
			// �� ���� ������ �ƴҶ���
			if (ptMouse.x < rc.right - nRcSize)
			{
				bRightClick = true;
				pt1 = ptMouse;
			}
		break;
		case WM_RBUTTONUP:
			// �� ���� �������� Ŭ���� ���� ���
			if (ptMouse.x >= rc.right - nRcSize)
			{
				bRightClick = false;
				::InvalidateRect(g_hWnd, NULL, true);
				break;
			}

			// �簢�� �߰�
			pt2 = ptMouse;

			POINT lefttop, rightbottom;

			lefttop.x = min(pt1.x, pt2.x);
			lefttop.y = min(pt1.y, pt2.y);
			rightbottom.x = max(pt1.x, pt2.x);
			rightbottom.y = max(pt1.y, pt2.y);

			{
				LineOrRect* pRect = new LineOrRect(lefttop, rightbottom);
				pRect->SetType(Rect);
				pRect->SetColor(ColorDepot.GetColor(nClrSelect));

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


//������������������������������������������������������������������������������
// �٦��� 03-03-21, ������׵� seth. ������
//������������������������������������������������������������������������������