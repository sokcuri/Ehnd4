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

#pragma once
#include "../Interface/Ehnd.h"
#include "../Interface/TLEngine.h"
#include "../Hook/EZTJ2K_FixHook.h"

class TLEngine_EZT_J2K : public TLEngine
{
public:
	TLEngine_EZT_J2K();
	~TLEngine_EZT_J2K();

public:
	EH_METHOD(BOOL32) TranslateText(LPCSTR srcText, char **outText);
	EH_METHOD(BOOL32) TranslateText(LPCWSTR srcText, WCHAR **outText);
	EH_METHOD(BOOL32) SendEngineMessage(UINT Message, WPARAM wParam, LPARAM lParam);

public:
	EH_METHOD(EHND_ENGINE) GetEngineType() const
	{
		return EHND_ENGINE_EZT_J2K;
	}
	EH_METHOD(EHNDERR) GetLastError() const
	{
		return m_lastErr;
	}

private:
	EH_METHOD(void) SetLastError(EHNDERR error)
	{
		m_lastErr = error;
	}

private:
	EHNDERR m_lastErr;

private:
	struct EZT_INITINFO
	{
		bool sig = false;
		int version = 0;
		char dat[MAX_PATH] = { 0, };
		char dll[MAX_PATH] = { 0, };
	};

	// J2K Functions
	using J2K_INITIALIZE = int(WINAPI*)(char *);
	J2K_INITIALIZE fpJ2KInitialize = NULL;

	using J2K_INITIALIZEEX = int(WINAPI*)(char *, char*);
	J2K_INITIALIZEEX fpJ2KInitializeEx = NULL;

	using J2K_FREEMEM = int(WINAPI*)(void*);
	J2K_FREEMEM fpJ2KFreeMem = NULL;

	using J2K_GETPRIORDICT = int(WINAPI*)(void);
	J2K_GETPRIORDICT fpJ2KGetPriorDict = NULL;

	using J2K_GETPROPERTY = int(WINAPI*)(void);
	J2K_GETPROPERTY fpJ2KGetProperty = NULL;

	using J2K_RELOADUSERDICT = int(WINAPI*)(void);
	J2K_RELOADUSERDICT fpJ2KReloadUserDict = NULL;

	using J2K_SETDELJPN = int(WINAPI*)(void);
	J2K_SETDELJPN fpJ2KSetDelJPN = NULL;

	using J2K_SETFIELD = int(WINAPI*)(void);
	J2K_SETFIELD fpJ2KSetField = NULL;

	using J2K_SETHNJ2HAN = int(WINAPI*)(void);
	J2K_SETHNJ2HAN fpJ2KSetHnj2han = NULL;

	using J2K_SETJWIN = int(WINAPI*)(void);
	J2K_SETJWIN fpJ2KSetJWin = NULL;

	using J2K_SETPRIORDICT = int(WINAPI*)(void);
	J2K_SETPRIORDICT fpJ2KSetPriorDict = NULL;

	using J2K_SETPROPERTY = int(WINAPI*)(void);
	J2K_SETPROPERTY fpJ2KSetProperty = NULL;

	using J2K_STOPTRANSLATION = int(WINAPI*)(void);
	J2K_STOPTRANSLATION fpJ2KStopTranslation = NULL;

	using J2K_TERMINATE = int(WINAPI*)(void);
	J2K_TERMINATE fpJ2KTerminate = NULL;

	using J2K_TRANSLATECHAT = int(WINAPI*)(void);
	J2K_TRANSLATECHAT fpJ2KTranslateChat = NULL;

	using J2K_TRANSLATEFM = int(WINAPI*)(void);
	J2K_TRANSLATEFM fpJ2KTranslateFM = NULL;

	using J2K_TRANSLATEMM = char*(WINAPI*)(void);
	J2K_TRANSLATEMM fpJ2KTranslateMM = NULL;

	using J2K_TRANSLATEMMEX = char*(WINAPI*)(void);
	J2K_TRANSLATEMMEX fpJ2KTranslateMMEx = NULL;

	using J2K_TRANSLATEMMNT = char*(WINAPI*)(int, const char*);
	J2K_TRANSLATEMMNT fpJ2KTranslateMMNT = NULL;

	using J2K_GETJ2KMAINDIR = char*(WINAPI*)(void);
	J2K_GETJ2KMAINDIR fpJ2KGetJ2KMainDir = NULL;

	EZT_INITINFO InitInfo;

public:
	EH_METHOD(bool) Init()
	{
		HINSTANCE hDLL;
		std::string basePath;

		printf("%s\n", GetLoadPathA().c_str());

		if (_IsFileExist(fmt::format("{0}J2KEngine.dll", GetLoadPathA()).c_str()))
			basePath = GetLoadPathA();
		else if (_IsFileExist(fmt::format("{0}{1}J2KEngine.dll", GetLoadPathA(), "..\\Common\\").c_str()))
			basePath = GetLoadPathA() + "..\\Common\\";
		else
			basePath = "";

		strcpy(InitInfo.dll, fmt::format("{0}J2KEngine.dll", basePath).c_str());
		strcpy(InitInfo.dat, fmt::format("{0}Dat", basePath).c_str());
		
		printf("J2KEngine: %s\n", InitInfo.dll);

		// Load J2KEngine.dlx
		if ((hDLL = LoadLibraryA(InitInfo.dll)) == NULL)
		{
			MessageBox(0, fmt::format(L"LoadLibrary to J2KEngine.dll Failed: {0}", InitInfo.dll).c_str(), L"Error", MB_ICONERROR);
			SetLastError(EHNDERR_EZTJ2K_DLL_NOT_FOUND);
			return false;
		}

		// Declare eztrans function tables
		std::list<std::pair<char *, LPVOID>> fpEztTable =
		{
			{ "J2K_Initialize", &fpJ2KInitialize },
			{ "J2K_InitializeEx", &fpJ2KInitializeEx },
			{ "J2K_FreeMem", &fpJ2KFreeMem },
			{ "J2K_GetPriorDict", &fpJ2KGetPriorDict },
			{ "J2K_GetProperty", &fpJ2KGetProperty },
			{ "J2K_ReloadUserDict", &fpJ2KReloadUserDict },
			{ "J2K_SetDelJPN", &fpJ2KSetDelJPN },
			{ "J2K_SetField", &fpJ2KSetField },
			{ "J2K_SetHnj2han", &fpJ2KSetHnj2han },
			{ "J2K_SetJWin", &fpJ2KSetJWin },
			{ "J2K_SetPriorDict", &fpJ2KSetPriorDict },
			{ "J2K_SetProperty", &fpJ2KSetProperty },
			{ "J2K_StopTranslation", &fpJ2KStopTranslation },
			{ "J2K_Terminate", &fpJ2KTerminate },
			{ "J2K_TranslateChat", &fpJ2KTranslateChat },
			{ "J2K_TranslateFM", &fpJ2KTranslateFM },
			{ "J2K_TranslateMM", &fpJ2KTranslateMM },
			{ "J2K_TranslateMMEx", &fpJ2KTranslateMMEx },
			{ "J2K_TranslateMMNT", &fpJ2KTranslateMMNT },
			{ "?GetJ2KMainDir@@YA?AVCString@@XZ", &fpJ2KGetJ2KMainDir },
		};
		for (auto &p : fpEztTable)
		{
			if ((*reinterpret_cast<LPVOID *>(p.second) =
				reinterpret_cast<LPVOID>(
					GetProcAddress(hDLL, p.first)
					)) == NULL)
			{
				printf("%s\n", fmt::format("[Hook] Not found function : {0}", p.first).c_str());
				SetLastError(EHNDERR_EZTJ2K_LOAD_FAILED);
				return false;
			}
		}

		if (!EZTJ2K_FixHook(InitInfo.dll))
		{
			printf("FixHook Failed\n");
			SetLastError(EHNDERR_EZTJ2K_FIXHOOK_FAILED);
			return false;
		}

		if (!J2K_InitializeEx())
		{
			SetLastError(EHNDERR_EZTJ2K_INITIALIZE_FAILED);
			return false;
		}

		return true;
	}

	EH_METHOD(void) Release()
	{
		delete this;
	}

private:
	int WINAPI J2K_Initialize()
	{
		return fpJ2KInitialize("OHUSER123455");
	}
	int WINAPI J2K_InitializeEx()
	{
		//if (!g_bInit)
		//	EH_InstallHook(InitInfo.dll);

		return fpJ2KInitializeEx("OHUSER123455", InitInfo.dat);
	}
	int WINAPI J2K_FreeMem(void *mem)
	{
		// MFC 버전이 달라 호환되지 않음
		return fpJ2KFreeMem(mem);

		//delete[] mem;
		//return 0;
	}
	int WINAPI J2K_GetPriorDict(void)
	{
		return fpJ2KGetPriorDict();
	}
	int WINAPI J2K_GetProperty(void)
	{
		return fpJ2KGetProperty();
	}
	int WINAPI J2K_ReloadUserDict(void)
	{
		return fpJ2KReloadUserDict();
	}
	int WINAPI J2K_SetDelJPN(void)
	{
		return fpJ2KSetDelJPN();
	}
	int WINAPI J2K_SetField(void)
	{
		return fpJ2KSetField();
	}
	int WINAPI J2K_SetHnj2han(void)
	{
		return fpJ2KSetHnj2han();
	}
	int WINAPI J2K_SetJWin(void)
	{
		return fpJ2KSetJWin();
	}
	int WINAPI J2K_SetPriorDict(void)
	{
		return fpJ2KSetPriorDict();
	}
	int WINAPI J2K_SetProperty(void)
	{
		return fpJ2KSetProperty();
	}
	int WINAPI J2K_StopTranslation(void)
	{
		return fpJ2KStopTranslation();
	}
	int WINAPI J2K_Terminate(void)
	{
		return fpJ2KTerminate();
	}
	int WINAPI J2K_TranslateChat(void)
	{
		return fpJ2KTranslateChat();
	}
	int WINAPI J2K_TranslateFM(void)
	{
		return fpJ2KTranslateFM();
	}
	char * WINAPI J2K_TranslateMM(void)
	{
		return fpJ2KTranslateMM();
	}
	char * WINAPI J2K_TranslateMMEx(void)
	{
		return fpJ2KTranslateMMEx();
	}

	char *WINAPI J2K_TranslateMMNT(int data0, char *text)
	{
		char *output = NULL;
		std::string input = EH_DoScript_Input(text);

		char *trans = fpJ2KTranslateMMNT(data0, input.c_str());
		if (trans)
		{
			printf("Trans: %s\n", trans);
			output = EH_DoScript_Output(trans);
		}
		return output;
	}
	char * WINAPI J2K_GetJ2KMainDir(void)
	{
		return fpJ2KGetJ2KMainDir();
	}
private:
	bool _IsFileExist(LPCSTR fileName)
	{
		DWORD dwAttrib = GetFileAttributesA(fileName);

		return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
			!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	}
};

