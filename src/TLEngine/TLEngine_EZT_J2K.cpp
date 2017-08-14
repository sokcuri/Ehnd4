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
#include "TLEngine_EZT_J2K.h"

TLEngine_EZT_J2K::TLEngine_EZT_J2K() : m_lastErr(EHNDERR_NOERR)
{

}

TLEngine_EZT_J2K::~TLEngine_EZT_J2K()
{

}

BOOL32 TLEngine_EZT_J2K::TranslateText(LPCSTR srcText, char ** outText)
{	
	char *_transText = J2K_TranslateMMNT(0, (char *)srcText);
	if (_transText == NULL)
	{
		SetLastError(EHNDERR_EZTJ2K_TRANSLATE_FAILED);
		return false;
	}

	*outText = new char[strlen(_transText) + 1];
	strcpy(*outText, _transText);
	
	J2K_FreeMem(_transText);

	SetLastError(EHNDERR_NOERR);
	return true;
}

BOOL32 TLEngine_EZT_J2K::TranslateText(LPCWSTR srcText, WCHAR ** outText)
{
	int nBytes;
	
	nBytes = WideCharToMultiByte(932, 0, srcText, -1, NULL, NULL, NULL, NULL);
	char *szSrcText = new char[(nBytes + 1) * 3];
	if (szSrcText == NULL)
	{
		SetLastError(EHNDERR_MEMORY_ALLOC_FAILED);
		return false;
	}
	WideCharToMultiByte(932, 0, srcText, -1, szSrcText, nBytes, NULL, NULL);

	char *_transText = J2K_TranslateMMNT(0, szSrcText);

	nBytes = MultiByteToWideChar(949, MB_PRECOMPOSED, _transText, -1, NULL, NULL);

	*outText = new WCHAR[nBytes + 1];
	if (*outText == NULL)
	{
		SetLastError(EHNDERR_MEMORY_ALLOC_FAILED);
		return false;
	}
	MultiByteToWideChar(949, 0, _transText, -1, *outText, nBytes);

	SetLastError(EHNDERR_NOERR);
	return true;
}

BOOL32 TLEngine_EZT_J2K::SendEngineMessage(UINT Message, WPARAM wParam, LPARAM lParam)
{
	SetLastError(EHNDERR_NOERR);
	return true;
}
