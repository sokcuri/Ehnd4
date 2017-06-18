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
#include "Scripts.h"

std::string EH_DoScript_Input(std::string input)
{
	const char *do_func_name = "input";

	int result;
	if (luaL_dofile(L, fmt::format("{0}script.lua", GetLoadPathA()).c_str()))
	{
		printf("Couldn't load file: script.lua, %s\n", lua_tostring(L, -1));
		return input;
	}

	std::string utf8 = MBCStoUTF8(932, input);
	lua_getglobal(L, do_func_name);
	lua_pushstring(L, utf8.c_str()); // utf-8
	if ((result = lua_pcall(L, 1, LUA_MULTRET, 0)))
	{
		printf("failed to run script: %d %s\n", result, lua_tostring(L, -1));
		return input;
	}

	const char *lua_retn = lua_tostring(L, -1);
	lua_pop(L, 1);
	std::string mbcs = UTF8toMBCS(932, lua_retn);
	printf("EH_DoScript_Input: %s\n", mbcs.c_str());

	return mbcs;
}

char *EH_DoScript_Output(char *input)
{
	const char *do_func_name = "output";

	int result;
	if (luaL_dofile(L, fmt::format("{0}script.lua", GetLoadPathA()).c_str()))
	{
		printf("Couldn't load file: script.lua, %s\n", lua_tostring(L, -1));
		return input;
	}

	std::string utf8 = MBCStoUTF8(949, input);

	// Free memory to translated string
	fpJ2KFreeMem(input);

	lua_getglobal(L, do_func_name);
	lua_pushstring(L, utf8.c_str()); // utf-8
	if ((result = lua_pcall(L, 1, LUA_MULTRET, 0)))
	{
		printf("failed to run script: %d %s\n", result, lua_tostring(L, -1));
		return input;
	}

	const char *lua_retn = lua_tostring(L, -1);
	lua_pop(L, 1);
	std::string mbcs = UTF8toMBCS(949, lua_retn);
	printf("EH_DoScript_Output: %s\n", mbcs.c_str());

	// allocate memomry
	char *func_retn = new char[mbcs.length() + 1];
	strcpy(func_retn, mbcs.c_str());
	return func_retn;
}
