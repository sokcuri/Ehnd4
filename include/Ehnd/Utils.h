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

std::string GetLoadPathA();
std::wstring GetLoadPathW();

INT IsWritableMemory(LPVOID pMemoryAddr);
INT IsReadableMemory(LPVOID pMemoryAddr);

int search_ptn(LPWORD ptn, size_t ptn_size, LPBYTE * addr, char *module_name);

std::wstring MultiByteToWideChar(int CodePage, const std::string multibyte);

std::string WideCharToMultiByte(int CodePage, const std::wstring widechar);

std::string MBCStoUTF8(int CodePage, const std::string input);

std::string UTF8toMBCS(int CodePage, const std::string input);

std::string CreateUUID();
