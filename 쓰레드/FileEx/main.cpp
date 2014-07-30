#include "FileEx.h"

#include <conio.h>

#include <sstream>
#include <locale>

int main(void)
{
	::setlocale(LC_ALL, "korean");
	
	FileEx fe(_T("D:"));

	bool need_to_draw = true;
	while(true)
	{
		if (_kbhit())
		{
			int key = _getch();

			if (key == SPECIAL)
			{
				key = _getch();

				if (key == UP)
				{
					fe.up();
				}
				else if (key == DOWN)
				{
					fe.down();
				}
			}
			else if (key == ENTER)
			{
				fe.enter();
			}

			need_to_draw = true;
		}

		if (need_to_draw)
		{
			::system("cls");
			std::wcout << fe;
			need_to_draw = false;
		}

	}

	_getch();
	return 0;
}