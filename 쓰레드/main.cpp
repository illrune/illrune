#include <iostream>
#include <conio.h>

#include <locale> // ÇÑ±Û

#include <windows.h>
#include <tchar.h>
#include <sstream>

enum keycode_id
{
	SPECIAL = 0xE0,
	UP		= 0x48,
	DOWN	= 0x50,
	ENTER	= 0x0D,
};

int main(void)
{
	::setlocale(LC_ALL, "korean");

	WIN32_FIND_DATA fd;

	int index = 1;

	HANDLE hFile = ::FindFirstFile(_T("D:\\*"), &fd);

	while(true)
	{
		int current = 0;
		std::ostringstream oss;		

		do {
			if (index == current)
			{
				std::wcout << ">> ";
				oss << "D:\\" << fd.cFileName << "\\*";
			}
			else
				std::wcout << "   ";

			if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
			std::wcout << _T("[");

			std::wcout << fd.cFileName;

			if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
				std::wcout << _T("]");

			std::wcout << std::endl;

			current++;

		} while (::FindNextFile(hFile,&fd));

		hFile = ::FindFirstFile(_T("D:\\*"), &fd);

			if (_kbhit())
			{
				int key = _getch();

				if (key == SPECIAL)
				{
					key = _getch();

					if (key == UP)
					{
						if (index > 0)
							index--;
					}
					else if (key == DOWN)
					{
						if (index < current-1)
							index++;
					}
				}
				else if (key == ENTER)
				{
					// todo
				}
			}

			system("cls");
		}

	_getch();
	return 0;
}