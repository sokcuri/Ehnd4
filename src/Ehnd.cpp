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
#include "Ehnd.h"
#include "MinHook.h"
#include "J2K_Functions.hpp"

lua_State *L = NULL;

MESSAGEBOXW fpMessageBoxW = NULL;
char *space = NULL;
void AssignFreeSpace()
{

}
using RETN = void(*)();
RETN fpReturn = NULL;
LPBYTE lpfnRetn1;
LPBYTE lpfnRetn2;
LPBYTE lpfnRetn3;
void DetourInitializeEx(char *a, char *b)
{

}

char *assign_memory(char *str)
{
	return new char[strlen(str) + 1];
}
void destroy_memory(char *str)
{
	return delete[] str;
}

__declspec(naked) void Patch_1()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [ESP + 0x20]
		CMP EAX, 0x0E
		JNE TEnd

		PUSH EBP
		CALL assign_memory
		ADD ESP, 0x04
		MOV DWORD PTR DS : [ESP + 0x2C], EAX

		MOV EDX, DWORD PTR SS : [ESP + 0x2C]
		PUSH EBP
		PUSH EDX

		CALL EDI

		TEnd:
		JMP lpfnRetn1
	}
}
__declspec(naked) void Patch_2()
{
	__asm
	{
		ADD ESP, 4
		MOV EAX, DWORD PTR SS : [ESP + 0x2C]
		JMP lpfnRetn2
	}
}
__declspec(naked) void Patch_3()
{
	__asm
	{
		PUSH DWORD PTR SS: [ESP + 0x2C]
		CALL destroy_memory
		ADD ESP, 4

		PUSH 0x0F
		PUSH EBP
		JMP lpfnRetn3
	}
	//MessageBox(0, L"Patched", 0, 0);
}
bool EH_UpdateCheck()
{
	return true;
}

bool EH_InitLua()
{
	// Create lua state
	L = luaL_newstate();
	luaL_openlibs(L);
	
	// opens the basic, table, I/O, string, math library
	luaopen_base(L);
	luaopen_table(L);
	luaopen_table(L);
	luaopen_io(L);
	luaopen_string(L);
	luaopen_math(L);
	return true;
}

bool EH_UninitLua()
{
	lua_close(L);
	return true;
}

bool EH_InstallHook(char *libPath)
{
	// Initialize Lua
	EH_InitLua();

	// Update Check
	EH_UpdateCheck();

	// Initialize minhook
	MH_Initialize();

	HINSTANCE hDLL;
	
	// Load J2KEngine.dlx
	if ((hDLL = LoadLibraryA(libPath)) == NULL)
	{
		MessageBox(0, fmt::format(L"LoadLibrary to J2KEngine.dlx Failed: {0}", libPath).c_str(), L"Error", MB_ICONERROR);
		return false;
	}

	// Declare eztrans function tables
	std::list<std::pair<char *, LPVOID>> fpTable =
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
	
	g_bInit = true;

	// fix to function (hook)
	([] {
		// 101D66B0   > \6A FF               PUSH -1
		// 101D66B2   .  68 6A5B1F10         PUSH J2KEngin.101F5B6A                   ;  SE handler installation
		// 101D66B7   .  64:A1 00000000      MOV EAX,DWORD PTR FS:[0]
		// 101D66BD   .  50                  PUSH EAX
		// 101D66BE   .  64:8925 00000000    MOV DWORD PTR FS:[0],ESP
		// 101D66C5      81EC 1C010000       SUB ESP,11C
		// 101D66CB   .  53                  PUSH EBX
		// 101D66CC   .  55                  PUSH EBP
		// 101D66CD   .  56                  PUSH ESI
		// 101D66CE   .  57                  PUSH EDI
		// 101D66CF   .  8BD9                MOV EBX,ECX
		// 101D66D1   .  6A 30               PUSH 30

		// 6A FF 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 64 89 25 00 00 00 00 81 EC 1C 01 00 00

		// +0x248 | LEA EDX,DWORD PTR SS:[ESP+2C] // CALL EDI (lstrcpyA)
		// +0x263 | ADD ESP,4; MOV ESI, EBP // LEA EAX,DWORD PTR SS:[ESP+2C]
		// +0x2A1 | PUSH 0x0F; PUSH EBP; MOV ECX, EBX
		WORD ptn[] = { 0x6A, 0xFF, 0x68, -1, -1, -1, -1, 0x64, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x50, 0x64, 0x89, 0x25, 0x00, 0x00, 0x00, 0x00, 0x81, 0xEC, 0x1C, 0x01, 0x00, 0x00 };
		LPBYTE addr = NULL;
		if (search_ptn(ptn, _countof(ptn), &addr, g_szDLLName) == 1)
		{
			if (MH_CreateHook(addr + 0x248, Patch_1, NULL) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x263, Patch_2, NULL) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			if (MH_CreateHook(addr + 0x2A1, Patch_3, NULL) != MH_OK)
			{
				MessageBox(0, L"Patch Failed", 0, 0);
			}
			lpfnRetn1 = addr + 0x248 + 0x08;
			lpfnRetn2 = addr + 0x263 + 0x09;
			lpfnRetn3 = addr + 0x2A1 + 0x05;
			MH_EnableHook(addr + 0x248);
			MH_EnableHook(addr + 0x263);
			MH_EnableHook(addr + 0x2A1);
			//MH_EnableHook(addr + 0x268);
			//MH_EnableHook(addr + 0x6E0);
		}
	}());
	
	return true;
	// return
	/*
	for (const auto &t : eztFuncTuple)
	{
		auto addr = (LPVOID)GetProcAddress(hDLL, std::get<0>(t));
		std::string msg = std::get<0>(t);
		if (addr == NULL)
		{
			msg = "J2KEngine.dlx Load Failed : " + msg;
			MessageBoxA(0, msg.c_str(), "Hook Error", MB_ICONERROR);
			return false;
		}
		if (MH_CreateHook(std::get<1>(t), addr, NULL) != MH_OK)
		{
			msg = "J2KEngine.dlx Patch Failed : " + msg;
			MessageBoxA(0, msg.c_str(), "Hook Error", MB_ICONERROR);
			return false;
		}

		if (MH_EnableHook(std::get<1>(t)) != MH_OK)
		{
			msg = "J2KEngine.dlx EnableHook Failed : " + msg;
			MessageBoxA(0, msg.c_str(), "Hook Error", MB_ICONERROR);
			return false;
		}
	}*/



	return true;

	fpJ2KInitializeEx = (J2K_INITIALIZEEX)GetProcAddress(hDLL, "J2K_InitializeEx");

	MessageBox(0, L"Loading", 0, 0);

	if (MH_CreateHook(&J2K_InitializeEx, DetourInitializeEx, NULL) != MH_OK)
	{
		MessageBox(0, L"Patch Failed", 0, 0);
	}

	MH_EnableHook(&J2K_InitializeEx);
	return true;
}

bool EH_UninstallHook()
{
	EH_UninitLua();
	MH_Uninitialize();
	return true;
}

// 내보낸 변수의 예제입니다.
EHND_API int nEhnd=0;

// 내보낸 함수의 예제입니다.
EHND_API int fnEhnd(void)
{
    return 42;
}

// 내보낸 클래스의 생성자입니다.
// 클래스 정의를 보려면 Ehnd.h를 참조하십시오.
CEhnd::CEhnd()
{
    return;
}
