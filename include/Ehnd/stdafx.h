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

#include "targetver.h"

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

// common include
#include <windows.h>
#include <time.h>
#include <psapi.h>

// warning disable
#pragma warning(disable: 4838)

// standard library
#include <string>
#include <list>
#include <vector>
#include <tuple>

// fmt
#include "format.h"

// various library
#include "reverse_iterate.hpp"
#include "Utils.h"
#include "Scripts.h"

#include <lua.hpp>

#include "J2K_Functions.h"

// define naked
#define NAKED __declspec(naked)

// extern variable
extern HINSTANCE g_hInst;
extern BOOL g_bInit;
extern char g_szDLLName[MAX_PATH];
extern lua_State *L;