#include "FileEx.h"

FontInfo::FontInfo()
: bLoad(false)
{
	//::GetModuleFileName(			// MSDN보고 구현 숙제
	std::fstream fontfile;

	fontfile.open("Font.info", std::ios_base::in | std::ios_base::binary);

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
		std::fstream fontfile;

		fontfile.open("Font.info", std::ios_base::out | std::ios_base::binary);

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