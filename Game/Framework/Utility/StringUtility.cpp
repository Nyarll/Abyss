#include "StringUtility.h"

std::wstring StringUtiltiy::StringToWstring(std::string str)
{
	// <ShiftJIS -> wstring>
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, (wchar_t*)NULL, 0);

	// <�o�b�t�@�擾>
	wchar_t* cpUCS2 = new wchar_t[iBufferSize];
	
	//<ShiftJIS -> wstring>
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, cpUCS2, iBufferSize);

	std::wstring output(cpUCS2, cpUCS2 + iBufferSize - 1);

	delete[] cpUCS2;

	return output;
}
