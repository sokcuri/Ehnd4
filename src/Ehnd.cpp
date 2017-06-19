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
#include "CrashFix.h"

lua_State *L = NULL;

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
	HINSTANCE hDLL;

	// Initialize Lua
	EH_InitLua();

	// Update Check
	EH_UpdateCheck();

	// Initialize minhook
	MH_Initialize();

	// Load J2KEngine.dlx
	if ((hDLL = LoadLibraryA(libPath)) == NULL)
	{
		MessageBox(0, fmt::format(L"LoadLibrary to J2KEngine.dlx Failed: {0}", libPath).c_str(), L"Error", MB_ICONERROR);
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
			MessageBoxA(0, fmt::format("Load Failed - {0}", p.first).c_str(), "Hook Error", MB_ICONERROR);
			return false;
		}
	}
	if (!CrashFixHook())
		return false;

	g_bInit = true;
	return true;
}

bool EH_UninstallHook()
{
	EH_UninitLua();
	MH_Uninitialize();
	return true;
}
