#include "FileEx.h"

FileEx::FileEx()
 : index(0), lineheight(25)
{
}
FileEx::FileEx(const TCHAR* dir)
 : index(0), path(dir), lineheight(25)
{
	listdirectory();
}
FileEx::~FileEx()
{
}

void FileEx::up()
{
	index = max(0,index-1);
}
void FileEx::down()
{
	index = min(filelist.size()-1,index+1);
}
void FileEx::setpos(POINT pt)
{
	if (pt.x <= 500 && pt.y < lineheight * (filelist.size()+1))
	{
		index = max(0, pt.y/lineheight-1);
	}
}
void FileEx::enter()
{
	std::list<FileInfo>::iterator it = filelist.begin();
	std::advance(it,index);

	if (*it == std::wstring(_T(".")))
	{
		// do noting
	}
	else if (*it == std::wstring(_T("..")))
	{
		// 이전 디렉토리
		path = path.substr(0, path.find_last_of(_T('\\')));
	}
	else
	{
		std::wstring check(path);
		check += _T("\\") + std::wstring(*it);

		WIN32_FIND_DATA fd;
		HANDLE hCheck = ::FindFirstFile(check.c_str(),&fd);
		if (hCheck == INVALID_HANDLE_VALUE)
		{
			// do noting
		}
		else if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
		{
			path += _T("\\") + std::wstring(*it);
		}
		else
		{
			// do noting
		}

		::FindClose(hCheck);
	}

	listdirectory();

	index = 0;
}

void FileEx::listdirectory()
{
	filelist.clear();

	WIN32_FIND_DATA fd;
	std::wstring ret(path);
	ret += _T("\\*");
	HANDLE hFile = ::FindFirstFile(ret.c_str(),&fd);
	do{
		bool bDir = ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY);
			filelist.push_back(FileInfo(fd.cFileName,bDir));
	} while (::FindNextFile(hFile,&fd));

	::FindClose(hFile);
}

std::wostream& operator << (std::wostream& os, const FileEx& obj)
{
	std::list<FileInfo>::const_iterator it;
	int i = 0;
	for (it = obj.filelist.begin(); it != obj.filelist.end(); it++, i++)
	{
		if (i == obj.index)
			os << _T(">>");
		else
			os << _T("  ");

		os << *it << std::endl;
	}

	return os;
}
HDC& operator << (HDC& dc, const FileEx& obj)
{
	::SetBkMode(dc, TRANSPARENT);

	std::list<FileInfo>::const_iterator it;
	int i = 0;

	RECT rc = {0,0,500,obj.lineheight};

	::DrawText(dc,obj.path.c_str(), -1, &rc, DT_LEFT);

	::OffsetRect(&rc, 0, obj.lineheight);
	
	for (it = obj.filelist.begin(); it != obj.filelist.end(); it++, i++)
	{
		std::wostringstream oss;

		if (i == obj.index)
			oss << _T(">>");
		else
			oss << _T("  ");

		oss << *it;

		if (i == obj.index)
		{
			::SetDCBrushColor(dc, RGB(30,220,20));
			::FillRect(dc, &rc, (HBRUSH)::GetStockObject(DC_BRUSH));
		}

		else if (i%2 == 0)
		{
			::SetDCBrushColor(dc, RGB(200,200,255));
			::FillRect(dc, &rc, (HBRUSH)::GetStockObject(DC_BRUSH));
		}
		else
		{
			::SetDCBrushColor(dc, RGB(255,255,200));
			::FillRect(dc, &rc, (HBRUSH)::GetStockObject(DC_BRUSH));
		}

		::DrawText(dc,oss.str().c_str(), -1, &rc, DT_LEFT);

		::OffsetRect(&rc, 0, obj.lineheight);
	}

	return dc;
}