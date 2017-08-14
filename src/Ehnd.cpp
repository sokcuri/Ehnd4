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

IEhnd *EH_CreateInstance()
{
	auto Inst = new CEhnd();
	return Inst;
}