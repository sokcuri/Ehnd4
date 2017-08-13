/**
* This file is part of Ehnd.
*
* Ehnd is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* The Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Ehnd is distributed in the hope that it will be useful,
*
* But WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Ehnd.
*
*   If not, see <http://www.gnu.org/licenses/>.
*
**/
#include "stdafx.h"
#include "Utils.h"

std::string GetLoadPathA()
{
	std::string &f([]
	{
		char _f[MAX_PATH] = { 0, };
		GetModuleFileNameA(g_hInst, _f, MAX_PATH);
		return std::string(_f);
	}());

	return f.substr(0, f.rfind('\\') + 1);
}

std::wstring GetLoadPathW()
{
	std::wstring &f([]
	{
		wchar_t _f[MAX_PATH] = { 0, };
		GetModuleFileNameW(g_hInst, _f, MAX_PATH);
		return std::wstring(_f);
	}());

	return f.substr(0, f.rfind(L'\\') + 1);
}

/*
IsWritableMemory : 주어진 메모리 주소의 상태가 쓰기가능인지 체크하는 함수
Param :
LPVOID  pMemoryAddr : 검사하고자 하는 메모리의 주소
Return Value :
ERROR_SUCCESS : 인자로 주어진 주소의 메모리가 Read/Write 가능한 경우
기타 값 : Read/Write 가능한 메모리가 아니면 해당 주소의 Protect Mode 를
나타내는 0이 아닌 값을 리턴함.
http://msdn.microsoft.com/en-us/library/aa915370.aspx 참조
*/
INT IsWritableMemory(LPVOID pMemoryAddr)
{
	MEMORY_BASIC_INFORMATION    MemInfo = { 0, };
	SIZE_T  nResult = 0;

	nResult = VirtualQuery(pMemoryAddr, &MemInfo, sizeof(MemInfo));

	if (nResult == 0) // 커널 영역인 경우 VirtualQuery 자체가 Fail함.  
	{
		return -1;
	}
	else if (MemInfo.Protect & (PAGE_EXECUTE_READWRITE | PAGE_READWRITE))
	{
		return  ERROR_SUCCESS;
	}
	else
	{
		return  MemInfo.Protect;
	}
}

/*
IsReadableMemory : 주어진 메모리 주소의 상태가 참조(Read)가능인지 체크하는 함수
Param :
LPVOID  pMemoryAddr : 검사하고자 하는 메모리의 주소
Return Value :
ERROR_SUCCESS : 인자로 주어진 주소의 메모리가 Read 가능한 경우
기타 값 : Read 가능한 메모리가 아니면 해당 주소의 State 를
나타내는 0이 아닌 값을 리턴함.
http://msdn.microsoft.com/en-us/library/aa915370.aspx 참조
*/
INT IsReadableMemory(LPVOID pMemoryAddr)
{
	MEMORY_BASIC_INFORMATION    MemInfo = { 0, };
	SIZE_T  nResult = 0;

	nResult = VirtualQuery(pMemoryAddr, &MemInfo, sizeof(MemInfo));

	if (nResult == 0) // 커널 영역인 경우 VirtualQuery 자체가 Fail함.  
	{
		return -1;
	}
	else if (MemInfo.State & MEM_COMMIT)
	{
		return  ERROR_SUCCESS;
	}
	else
	{
		return  MemInfo.State;
	}
}

int search_ptn(LPWORD ptn, size_t ptn_size, LPBYTE *addr, char *module_name)
{
	HMODULE hDll = GetModuleHandleA(module_name);
	if (hDll == NULL) MessageBox(0, fmt::format(L"{0} not loaded", module_name).c_str(), L"search_ptn error", 0);

	MODULEINFO dllInfo;
	GetModuleInformation(GetCurrentProcess(), hDll, &dllInfo, sizeof(dllInfo));

	// Modified BMH - http://en.wikipedia.org/wiki/Boyer-Moore-Horspool_algorithm

	UINT i;
	int scan;
	LPBYTE p;

	UINT defSkipLen;
	UINT skipLen[UCHAR_MAX + 1];
	UINT searchSuccessCount;

	UINT ptnEnd = ptn_size - 1;
	while ((HIBYTE(ptn[ptnEnd]) != 0x00) && (ptnEnd > 0)) {
		ptnEnd--;
	}
	defSkipLen = ptnEnd;
	for (i = 0; i < ptnEnd; i++)
	{
		if (HIBYTE(ptn[i]) != 0x00) {
			defSkipLen = ptnEnd - i;
		}
	}

	for (i = 0; i < UCHAR_MAX + 1; i++)
	{
		skipLen[i] = defSkipLen;
	}

	for (i = 0; i < ptnEnd; i++)
	{
		if (HIBYTE(ptn[i]) == 0x00)
		{
			skipLen[LOBYTE(ptn[i])] = ptnEnd - i;
		}
	}

	searchSuccessCount = 0;
	p = (LPBYTE)dllInfo.lpBaseOfDll;
	LPBYTE searchEnd = (LPBYTE)dllInfo.lpBaseOfDll + dllInfo.SizeOfImage;

	while (p + ptn_size < searchEnd)
	{
		scan = ptnEnd;
		while (scan >= 0)
		{
			if ((HIBYTE(ptn[scan]) == 0x00) && (LOBYTE(ptn[scan]) != p[scan]))
				break;
			if (scan == 0)
			{
				*addr = p;
				searchSuccessCount++;
			}
			scan--;
		}
		p += skipLen[p[ptnEnd]];
	}
	if (searchSuccessCount != 1) addr = 0;
	return searchSuccessCount;
}

std::wstring MultiByteToWideChar(int CodePage, const std::string multibyte)
{
	int len = MultiByteToWideChar(CodePage, 0, multibyte.c_str(), multibyte.length(), NULL, NULL);
	wchar_t *wsz = new wchar_t[len + 1];
	MultiByteToWideChar(CodePage, 0, multibyte.c_str(), multibyte.length(), wsz, len);
	wsz[len] = '\0';

	std::wstring ret = wsz;
	delete[] wsz;
	return ret;
}

std::string WideCharToMultiByte(int CodePage, const std::wstring widechar)
{
	int len = WideCharToMultiByte(CodePage, 0, widechar.c_str(), widechar.length(), NULL, 0, NULL, NULL);
	char *sz = new char[len + 1];
	WideCharToMultiByte(CodePage, 0, widechar.c_str(), widechar.length(), sz, len, NULL, NULL);
	sz[len] = '\0';

	std::string ret = sz;
	delete[] sz;
	return ret;
}

std::string MBCStoUTF8(int CodePage, const std::string input)
{
	return WideCharToMultiByte(CP_UTF8, MultiByteToWideChar(CodePage, input));
}
std::string UTF8toMBCS(int CodePage, const std::string input)
{
	return WideCharToMultiByte(CodePage, MultiByteToWideChar(CP_UTF8, input));
}
