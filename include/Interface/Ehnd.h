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

#define EHND_VERSION (0x20170813)

// error code
enum EHNDERR
{
	EHNDERR_NOERR						= 0x00000000,
	EHNDERR_NOT_IMPL					= 0xa0000010,
	EHNDERR_REQUIRE_ENGINE_OPEN			= 0xa0000030,
	EHNDERR_ALREADY_ENGINE_OPENED		= 0xa0000031,
	EHNDERR_NOT_SUPPORTED_TLENGINE		= 0xa0000032,
};

// engine type
enum EHND_ENGINE
{
	EHND_ENGINE_NULL					= 0,
	EHND_ENGINE_EZT_J2K					= 1,
	EHND_ENGINE_EZT_K2J					= 2,
	EHND_ENGINE_GOOGLE					= 10,
	EHND_ENGINE_NAVER					= 20,
};

// ezTrans Message
enum EHND_MSG_EZTJ2K
{
	EHND_MSG_EZTJ2K_SET_USERDICT		= 40,
	EHND_MSG_EZTJ2K_RELOAD_USERDICT		= 50,
};

// support language
enum EHND_TL_LANG
{
	EHND_TL_LANG_UNKNOWN = 0,
	EHND_TL_LANG_KOREAN = 1,
	EHND_TL_LANG_JAPANESE = 2
};

// define default data types
#ifndef TRUE
#define FALSE               0
#define TRUE                1
typedef char				CHAR;
typedef wchar_t				WCHAR;
typedef unsigned int		UINT32;
typedef const char*			LPCSTR;
typedef const wchar_t*		LPCWSTR;
#endif

// WINAPI stuff
#ifdef _WIN32
typedef signed __int64      INT64;
#define WINAPI				__stdcall
#else
typedef signed long long	INT64;
#define WINAPI				
#define THREAD_PRIORITY_NORMAL 0
#endif

// using BOOL32 instead int
typedef int				BOOL32;
typedef unsigned char   EHNDBYTE;

// pure method preprocessor
#define EH_METHOD(type) virtual type WINAPI
#define PURE = 0

// IEhnd Interface
struct IEhnd
{
	EH_METHOD(void) Release() PURE;
	EH_METHOD(UINT32) GetVersion() const PURE;
	EH_METHOD(EHNDERR) GetLastError() const PURE;
	EH_METHOD(BOOL32) Open(EHND_ENGINE engine, EHND_TL_LANG srcLang = EHND_TL_LANG_UNKNOWN, EHND_TL_LANG destLang = EHND_TL_LANG_UNKNOWN) PURE;
	
	EH_METHOD(BOOL32) TranslateText(LPCSTR srcText, char **outText) PURE;
	EH_METHOD(BOOL32) TranslateText(LPCWSTR srcText, WCHAR **outText) PURE;

	EH_METHOD(BOOL32) SendEngineMessage(UINT Message, WPARAM wParam, LPARAM lParam) PURE;
};

// Create instance function
IEhnd *EH_CreateInstance();