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
#include "minhook.h"

struct EZT_INITINFO
{
	bool sig = true;
	int version = 0;
	char dat[MAX_PATH] = { 0, };
	char dll[MAX_PATH] = { 0, };
};

HMODULE hDLL;
bool EZT_Load(HMODULE &hDLL);
bool EZT_Unload(HMODULE &hDLL);
bool EZT_Init(char *AppSig, EZT_INITINFO *InitInfo);

namespace ezt
{
	using J2K_INITIALIZE = int(WINAPI*)(char *);
	J2K_INITIALIZE J2K_Initialize = NULL;

	using J2K_INITIALIZEEX = int(WINAPI*)(char *, char*);
	J2K_INITIALIZEEX J2K_InitializeEx = NULL;

	using J2K_FREEMEM = int(WINAPI*)(void*);
	J2K_FREEMEM J2K_FreeMem = NULL;

	using J2K_GETPRIORDICT = int(WINAPI*)(void);
	J2K_GETPRIORDICT J2K_GetPriorDict = NULL;

	using J2K_GETPROPERTY = int(WINAPI*)(void);
	J2K_GETPROPERTY J2K_GetProperty = NULL;

	using J2K_RELOADUSERDICT = int(WINAPI*)(void);
	J2K_RELOADUSERDICT J2K_ReloadUserDict = NULL;

	using J2K_SETDELJPN = int(WINAPI*)(void);
	J2K_SETDELJPN J2K_SetDelJPN = NULL;

	using J2K_SETFIELD = int(WINAPI*)(void);
	J2K_SETFIELD J2K_SetField = NULL;

	using J2K_SETHNJ2HAN = int(WINAPI*)(void);
	J2K_SETHNJ2HAN J2K_SetHnj2han = NULL;

	using J2K_SETJWIN = int(WINAPI*)(void);
	J2K_SETJWIN J2K_SetJWin = NULL;

	using J2K_SETPRIORDICT = int(WINAPI*)(void);
	J2K_SETPRIORDICT J2K_SetPriorDict = NULL;

	using J2K_SETPROPERTY = int(WINAPI*)(void);
	J2K_SETPROPERTY J2K_SetProperty = NULL;

	using J2K_STOPTRANSLATION = int(WINAPI*)(void);
	J2K_STOPTRANSLATION J2K_StopTranslation = NULL;

	using J2K_TERMINATE = int(WINAPI*)(void);
	J2K_TERMINATE J2K_Terminate = NULL;

	using J2K_TRANSLATECHAT = int(WINAPI*)(void);
	J2K_TRANSLATECHAT J2K_TranslateChat = NULL;

	using J2K_TRANSLATEFM = int(WINAPI*)(void);
	J2K_TRANSLATEFM J2K_TranslateFM = NULL;

	using J2K_TRANSLATEMM = char*(WINAPI*)(void);
	J2K_TRANSLATEMM J2K_TranslateMM = NULL;

	using J2K_TRANSLATEMMEX = char*(WINAPI*)(void);
	J2K_TRANSLATEMMEX J2K_TranslateMMEx = NULL;

	using J2K_TRANSLATEMMNT = char*(WINAPI*)(int, char*);
	J2K_TRANSLATEMMNT J2K_TranslateMMNT = NULL;

	using J2K_GETJ2KMAINDIR = char*(WINAPI*)(void);
	J2K_GETJ2KMAINDIR J2K_GetJ2KMainDir = NULL;

}
// implementation
std::string GetCurrentPathA()
{
	std::string &f([] {
		char _f[MAX_PATH] = { 0, };
		GetModuleFileNameA(GetModuleHandle(NULL), _f, MAX_PATH);
		return std::string(_f);
	}());

	return f.substr(0, f.rfind('\\') + 1);
}

std::wstring GetCurrentPathW()
{
	std::wstring &f([] {
		wchar_t _f[MAX_PATH] = { 0, };
		GetModuleFileNameW(GetModuleHandle(NULL), _f, MAX_PATH);
		return std::wstring(_f);
	}());

	return f.substr(0, f.rfind(L'\\') + 1);
}

int main()
{
	if (!EZT_Load(hDLL))
	{
		printf("EZT_Load Failed\n");
		return 0;
	}

	EZT_INITINFO InitInfo;
	InitInfo.version = 1;
	strcpy(InitInfo.dat, (GetCurrentPathA() + "..\\Common\\Dat").c_str());
	strcpy(InitInfo.dll, (GetCurrentPathA() + "..\\Common\\J2KEngine.dll").c_str());
	
	if (!EZT_Init("EHND", &InitInfo))
	{
		printf("EZT_Init Failed\n");
		return 0;
	}

	printf("Initialization Complete");
	scanf("");
	
	char *trans = ezt::J2K_TranslateMMNT(0, "（ステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップスラップスティックステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップ……）");
	if (!trans)
	{
		printf("translate failed\n");
		return 0;
	}
	printf("%s\n", trans);
	ezt::J2K_FreeMem(trans);
	//for (int i = 0; i < 100; i++)
	//{
	//	printf("%03d: ", i);
	//	printf(ezt::J2K_TranslateMMNT(0, "（ステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップスラップスティックステップステップステップステップステップステップステップステップステップステップステップステップステップステップステップ……）"));
	//	//printf(ezt::J2K_TranslateMMNT(0, "アクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてくださいアクセスしてください"));
	//	printf("\n");
	//}

	if (!EZT_Unload(hDLL))
	{
		printf("EZT_Unload Failed\n");
		return 0;
	}
    return 0;
}

bool EZT_Load(HMODULE &hDLL)
{
	std::wstring dllName = fmt::format(L"{0}Ehnd.dll", GetCurrentPathW());
	hDLL = LoadLibrary(dllName.c_str());
	if (hDLL == NULL)
	{
		MessageBox(0, fmt::format(L"Ehnd file not found: {0}", dllName).c_str(), L"Load Error", MB_ICONERROR);
		return false;
	}

	// Declare eztrans function tables
	std::list<std::pair<char *, LPVOID>> fpTable =
	{
		{ "J2K_Initialize", &ezt::J2K_Initialize },
		{ "J2K_InitializeEx", &ezt::J2K_InitializeEx },
		{ "J2K_FreeMem", &ezt::J2K_FreeMem },
		{ "J2K_GetPriorDict", &ezt::J2K_GetPriorDict },
		{ "J2K_GetProperty", &ezt::J2K_GetProperty },
		{ "J2K_ReloadUserDict", &ezt::J2K_ReloadUserDict },
		{ "J2K_SetDelJPN", &ezt::J2K_SetDelJPN },
		{ "J2K_SetField", &ezt::J2K_SetField },
		{ "J2K_SetHnj2han", &ezt::J2K_SetHnj2han },
		{ "J2K_SetJWin", &ezt::J2K_SetJWin },
		{ "J2K_SetPriorDict", &ezt::J2K_SetPriorDict },
		{ "J2K_SetProperty", &ezt::J2K_SetProperty },
		{ "J2K_StopTranslation", &ezt::J2K_StopTranslation },
		{ "J2K_Terminate", &ezt::J2K_Terminate },
		{ "J2K_TranslateChat", &ezt::J2K_TranslateChat },
		{ "J2K_TranslateFM", &ezt::J2K_TranslateFM },
		{ "J2K_TranslateMM", &ezt::J2K_TranslateMM },
		{ "J2K_TranslateMMEx", &ezt::J2K_TranslateMMEx },
		{ "J2K_TranslateMMNT", &ezt::J2K_TranslateMMNT },
	};
	for (auto &p : fpTable)
	{
		if ((*reinterpret_cast<LPVOID *>(p.second) =
			reinterpret_cast<LPVOID>(
				GetProcAddress(hDLL, p.first)
				)) == NULL)
		{
			MessageBoxA(0, fmt::format("Load Failed - {0}", p.first).c_str(), "Hook Error", MB_ICONERROR);
			return false;
		}
	}
	return true;
}

bool EZT_Unload(HMODULE &hDLL)
{
	FreeLibrary(hDLL);
	hDLL = NULL;
	return true;
}

bool EZT_Init(char *AppSig, EZT_INITINFO *InitInfo)
{
	return ezt::J2K_InitializeEx("Ehnd", reinterpret_cast<char *>(InitInfo));
}
