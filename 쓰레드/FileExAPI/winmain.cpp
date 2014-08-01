#include "windefine.h"
#include "resource.h"

INT WINAPI _tWinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPTSTR lpCmdLine,
					 INT nCmdShow)
{
	LPCTSTR szClassName = _T("MyMainWindowClass");

	WNDCLASSEX wcex;

	::memset(&wcex, 0, sizeof(wcex));

    wcex.cbSize = sizeof(wcex);
    wcex.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc = &WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
	wcex.hIcon = ::LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szClassName;
	wcex.hIconSm = wcex.hIcon;

	if (!::RegisterClassEx(&wcex))
	{
		return 1;
	}

	//int width = 1000;
	//int height = 600;

	//int cx = ::GetSystemMetrics(SM_CXSCREEN);
	//int cy = ::GetSystemMetrics(SM_CYSCREEN);

	//int x = (cx - width)/2;
	//int y = (cy - height)/2;

	//DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	//dwStyle &= ~WS_MAXIMIZEBOX;
	//dwStyle &= ~WS_THICKFRAME;
	//dwStyle = dwStyle & ~WS_MINIMIZEBOX;
	//dwStyle &= ~WS_SYSMENU;
	//dwStyle &= ~WS_CAPTION;

	HWND hWnd = ::CreateWindowEx(0, szClassName, _T("Win32 FileEx"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	if (hWnd == NULL)
	{
		return 2;
	}

	::ShowWindow(hWnd, SW_NORMAL);
	::UpdateWindow(hWnd);

	MSG msg;

	while (true)
	{
		// if (::GetMessage(&msg, NULL, 0, 0))
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT)
			break;
	}

	return msg.wParam;
}

