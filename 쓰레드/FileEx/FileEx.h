#pragma once

#ifdef FILEEX_EXPORTS
#define FILEEXAPI __declspec(dllexport)
#else
#define FILEEXAPI __declspec(dllimport)
#endif

#pragma warning(disable:4251)

#include <windows.h>
#include <tchar.h>
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

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

struct FontInfo
{
	LOGFONT lfont;
	COLORREF color;

	FontInfo();
	~FontInfo();

	bool IsLoad() const;
	void SetLoad();
private :
	bool bLoad;
};

class FILEEXAPI FileEx
{
public :
	FileEx();
	FileEx(const TCHAR* dir);
	~FileEx();

	void up();
	void down();
	void enter();

	bool setpos(POINT pt);

	void SetFontInfo(const LOGFONT& lfont, const COLORREF& color);

	friend FILEEXAPI std::wostream& operator << (std::wostream& os, const FileEx& obj);
	friend FILEEXAPI HDC& operator << (HDC& dc, const FileEx& obj);

private :
	void listdirectory();
private :
	std::wstring path;
	std::list<FileInfo> filelist;
	int index;
	int lineheight;

	FontInfo fontinfo;
};