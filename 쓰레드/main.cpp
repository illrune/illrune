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
	std::wostringstream wos, wos2;
	wos2 << "D:";
	wos << _T("" << wos2.str().c_str() << "\\*");

	int index = 0;

	HANDLE hFile = ::FindFirstFile(wos.str().c_str(), &fd);

	while(true)
	{
		int current = 0;	

		do {
			if (index == current)
				std::wcout << ">> ";
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

		hFile = ::FindFirstFile(wos.str().c_str(), &fd);

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
					for(int i = 0; i < index; i++)
						::FindNextFile(hFile,&fd);

					if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
					{
						wos2 << "\\" << fd.cFileName;

						std::wostringstream wostmp;
						wostmp << _T("" << wos2.str().c_str() << "\\*");

						wos.clear();
						wos.str(_T(""));

						wos << wostmp.str().c_str();
						hFile = ::FindFirstFile(wos.str().c_str(), &fd);
						index = 0;
					}
					else
						hFile = ::FindFirstFile(wos.str().c_str(), &fd);
				}
			}

			system("cls");
		}

	_getch();
	return 0;
}