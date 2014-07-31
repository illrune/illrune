#include "FileEx.h"

FileInfo::FileInfo()
: bDirectory(false)
{
}
FileInfo::FileInfo(const TCHAR* _name, bool bDir)
: bDirectory(bDir), name(_name)
{
}

bool FileInfo::operator == (const std::wstring& o) const
{
	return (name == o);
}
FileInfo::operator std::wstring () const
{
	return name;
}
std::wostream& operator << (std::wostream& os, const FileInfo& obj)
{
	if (obj.bDirectory)
		os << _T("[");
	os << obj.name;
	if (obj.bDirectory)
		os << _T("]");

	return os;
}