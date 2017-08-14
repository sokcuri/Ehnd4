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
#include <Windows.h>
#include "Ehnd.h"

struct TLEngine
{
	EH_METHOD(bool) Init() PURE;
	EH_METHOD(void) Release() PURE;
	EH_METHOD(EHND_ENGINE) GetEngineType() const PURE;

	EH_METHOD(BOOL32) TranslateText(LPCSTR srcText, char **outText) PURE;
	EH_METHOD(BOOL32) TranslateText(LPCWSTR srcText, WCHAR **outText) PURE;

	EH_METHOD(BOOL32) SendEngineMessage(UINT Message, WPARAM wParam, LPARAM lParam) PURE;

	EH_METHOD(EHNDERR) GetLastError() const PURE;
	EH_METHOD(void) SetLastError(EHNDERR error) PURE;
};