#include "FileEx.h"

FontInfo::FontInfo()
: bLoad(false)
{
	//::GetModuleFileName(			// MSDN보고 구현 숙제

	TCHAR mPath[_MAX_PATH];
	::GetModuleFileName(NULL, mPath, _MAX_PATH);

	std::fstream fontfile;
	std::wstring loadpath;

	for (int i = 0; i < _MAX_PATH; i++)
	{
		loadpath += *(mPath+i);
	}

	loadpath = loadpath.substr(0, loadpath.find_last_of(_T('\\')));
	loadpath += _T("\\Font.info");

	fontfile.open(loadpath.c_str(), std::ios_base::in | std::ios_base::binary);

	if (!fontfile.good())
		return;

	fontfile.read((char*)&lfont, sizeof(LOGFONT));
	fontfile.read((char*)&color, sizeof(COLORREF));

	fontfile.close();

	bLoad = true;
}
FontInfo::~FontInfo()
{
	if (bLoad)
	{
		TCHAR mPath[_MAX_PATH];
		::GetModuleFileName(NULL, mPath, _MAX_PATH);

		std::fstream fontfile;
		std::wstring savepath;

		for (int i = 0; i < _MAX_PATH; i++)
		{
			savepath += *(mPath+i);
		}

		savepath = savepath.substr(0, savepath.find_last_of(_T('\\')));
		savepath += _T("\\Font.info");

		fontfile.open(savepath.c_str(), std::ios_base::out | std::ios_base::binary);

		fontfile.write((const char*)&lfont, sizeof(LOGFONT));
		fontfile.write((const char*)&color, sizeof(COLORREF));

		fontfile.close();
	}
}

bool FontInfo::IsLoad() const
{
	return bLoad;
}
void FontInfo::SetLoad()
{
	bLoad = true;
}