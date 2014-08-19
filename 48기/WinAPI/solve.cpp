//버젼 정보
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 03-03-21, 헤더파일 써주자 seth. ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
#include <windows.h>			//윈도우 헤더파일을 인크루드


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
	char				szBuf[128] = "가오나시";
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


//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 03-03-21, 참고사항들 seth. ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━