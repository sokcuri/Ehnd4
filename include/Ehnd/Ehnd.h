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
#ifdef EHND_EXPORTS
#define EHND_API __declspec(dllexport)
#else
#define EHND_API __declspec(dllimport)
#endif

class EHND_API CEhnd {
public:
	CEhnd(void);
};

extern EHND_API int nEhnd;

bool EH_UpdateCheck();

bool EH_InstallHook(char *libPath);
bool EH_UninstallHook();

EHND_API int fnEhnd(void);

using MESSAGEBOXW = int(*)(HWND, LPCWSTR, LPCWSTR, UINT);
extern MESSAGEBOXW fpMessageBoxW;