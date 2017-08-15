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
#include "../include/Interface/EhndLib.h"

// implementation
int main()
{
	EhndLib ehnd;

	EHNDERR error = ehnd.Create(L"Ehnd.dll");
	if (error) {
		printf("Initialize Failed : %x\n", error);
		return false;
	}

	printf("Initialization Complete\n"); 
	printf("Version: %x\n", ehnd.GetVersion());

	if (!ehnd.Open(EHND_ENGINE_EZT_J2K)) {
		printf("Open Failed: %x\n", ehnd.GetLastError());
		return false;
	}

	char *test = 0;
	if (!ehnd.TranslateText("긲뺝뢜갶궓뽦궋뜃귦궧갶? Getchu.com 1999-2017", &test)) {
		printf("Translate Failed: %x\n", ehnd.GetLastError());
	}

	ehnd.SendEngineMessage(EHND_MSG_EZTJ2K_RELOAD_USERDICT, 0, 0);

	printf("String Test: %s\n", test);
	return true;
}