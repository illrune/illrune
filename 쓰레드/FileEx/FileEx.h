#pragma once

#ifdef FILEEX_EXPORTS
#define FILEEXAPI __declspec(dllexport)
#else
#define FILEEXAPI __declspec(dllimport)
#endif

#include <windows.h>
#include <tchar.h>
#include <list>
#include <string>
#include <iostream>
#include <sstream>

enum keycode_id
{
	SPECIAL = 0xE0,
	UP		= 0x48,
	DOWN	= 0x50,
	ENTER	= 0x0D,
	ESC		= 0X1B,
};

struct FileInfo
{
	std::wstring name;
	bool bDirectory;

	FileInfo();
	FileInfo(const TCHAR* _name, bool bDir);

	bool operator == (const std::wstring& o) const;
	operator std::wstring () const;
	friend std::wostream& operator << (std::wostream& os, const FileInfo& obj);
};

class FILEEXAPI FileEx
{
public :
	FileEx();
	FileEx(const TCHAR* dir);
	~FileEx();

	void up();
	void down();
	void mouse(int y);
	void enter();

	void setpos(POINT pt);

	int GetSize();

	friend FILEEXAPI std::wostream& operator << (std::wostream& os, const FileEx& obj);
	friend FILEEXAPI HDC& operator << (HDC& dc, const FileEx& obj);

private :
	void listdirectory();
private :
	std::wstring path;
	std::list<FileInfo> filelist;
	int index;
	int lineheight;
};