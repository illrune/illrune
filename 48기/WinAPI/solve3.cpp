//���� ����
//������������������������������������������������������������������������������
// �٦��� 03-03-21, ������� ������ seth. ������
//������������������������������������������������������������������������������
#include <windows.h>			//������ ��������� ��ũ���


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
	char				szBuf[128] = "";
	static int			nNumber = 0;

	static const int	nAsciiValue = 0x20;

	switch(iMessage)
	{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
		break;
		case WM_LBUTTONDOWN:
			::InvalidateRect(g_hWnd, NULL, true);
			break;
		case WM_CHAR:
			if (nNumber >= 127)
				break;

			hdc = ::GetDC(g_hWnd);

			nNumber++;

			szBuf[nNumber] = wParam;

			if(szBuf[nNumber] >= 'A' && szBuf[nNumber] <= 'Z')
				szBuf[nNumber] = szBuf[nNumber] + nAsciiValue;
			else if(szBuf[nNumber] >= 'a' && szBuf[nNumber] <= 'z')
				szBuf[nNumber] = szBuf[nNumber] - nAsciiValue;				
			
			if (nNumber <= 64)
				::TextOut(hdc, 100 + nNumber*10, 100, &szBuf[nNumber], 1);
			else
				::TextOut(hdc, 100 + nNumber*10 - 64*10, 100 + 30, &szBuf[nNumber], 1);

			::InvalidateRect(g_hWnd, NULL, false);
			::ReleaseDC(g_hWnd,hdc);
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}


//������������������������������������������������������������������������������
// �٦��� 03-03-21, ������׵� seth. ������
//������������������������������������������������������������������������������