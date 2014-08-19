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
	char				szBuf[128] = "��������";
	static int			number = 0;

	switch(iMessage)
	{
		case WM_PAINT:
			if(number > 4)
			{
				number = 0;
			}
			hdc = BeginPaint(hWnd, &ps);
			::TextOut(hdc, 100, 100, szBuf, number*2);
			EndPaint(hWnd, &ps);
		break;
		case WM_LBUTTONDOWN:
			number++;
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
			PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}


//������������������������������������������������������������������������������
// �٦��� 03-03-21, ������׵� seth. ������
//������������������������������������������������������������������������������