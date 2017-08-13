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

J2K_INITIALIZE fpJ2KInitialize = NULL;
J2K_INITIALIZEEX fpJ2KInitializeEx = NULL;
J2K_FREEMEM fpJ2KFreeMem = NULL;
J2K_GETPRIORDICT fpJ2KGetPriorDict = NULL;
J2K_GETPROPERTY fpJ2KGetProperty = NULL;
J2K_RELOADUSERDICT fpJ2KReloadUserDict = NULL;
J2K_SETDELJPN fpJ2KSetDelJPN = NULL;
J2K_SETFIELD fpJ2KSetField = NULL;
J2K_SETHNJ2HAN fpJ2KSetHnj2han = NULL;
J2K_SETJWIN fpJ2KSetJWin = NULL;
J2K_SETPRIORDICT fpJ2KSetPriorDict = NULL;
J2K_SETPROPERTY fpJ2KSetProperty = NULL;
J2K_STOPTRANSLATION fpJ2KStopTranslation = NULL;
J2K_TERMINATE fpJ2KTerminate = NULL;
J2K_TRANSLATECHAT fpJ2KTranslateChat = NULL;
J2K_TRANSLATEFM fpJ2KTranslateFM = NULL;
J2K_TRANSLATEMM fpJ2KTranslateMM = NULL;
J2K_TRANSLATEMMEX fpJ2KTranslateMMEx = NULL;
J2K_TRANSLATEMMNT fpJ2KTranslateMMNT = NULL;
J2K_GETJ2KMAINDIR fpJ2KGetJ2KMainDir = NULL;

EZT_INITINFO InitInfo;

int WINAPI J2K_Initialize(char *AppSig)
{
	strcpy(InitInfo.dll, fmt::format("{0}J2KEngine.dlx", GetLoadPathA()).c_str());
	strcpy(InitInfo.dat, fmt::format("{0}Dat", GetLoadPathA()).c_str());

	if (!g_bInit)
		EH_InstallHook(InitInfo.dll);

	return fpJ2KInitialize("OHUSER123455");
}
int WINAPI J2K_InitializeEx(char *AppSig, char *path)
{
	if (!strcmp(AppSig, "Ehnd"))
	{
		const auto &_InitInfo = reinterpret_cast<EZT_INITINFO *>(path);
		memcpy(&InitInfo, _InitInfo, sizeof(EZT_INITINFO));
	}
	else
	{
		strcpy(InitInfo.dll, fmt::format("{0}J2KEngine.dlx", GetLoadPathA()).c_str());
		strcpy(InitInfo.dat, fmt::format("{0}Dat", GetLoadPathA()).c_str());
	}

	for (int i = strlen(InitInfo.dll) - 1; i >= 0; i--)
	{
		if (InitInfo.dll[i] == '\\')
		{
			strcpy(g_szDLLName, InitInfo.dll + i + 1);
			break;
		}
	}

	if (!g_bInit)
		EH_InstallHook(InitInfo.dll);

	return fpJ2KInitializeEx("OHUSER123455", InitInfo.dat);
}
int WINAPI J2K_FreeMem(void *mem)
{
	// MFC 버전이 달라 호환되지 않음
	return fpJ2KFreeMem(mem);

	//delete[] mem;
	//return 0;
}
int WINAPI J2K_GetPriorDict(void)
{
	return fpJ2KGetPriorDict();
}
int WINAPI J2K_GetProperty(void)
{
	return fpJ2KGetProperty();
}
int WINAPI J2K_ReloadUserDict(void)
{
	return fpJ2KReloadUserDict();
}
int WINAPI J2K_SetDelJPN(void)
{
	return fpJ2KSetDelJPN();
}
int WINAPI J2K_SetField(void)
{
	return fpJ2KSetField();
}
int WINAPI J2K_SetHnj2han(void)
{
	return fpJ2KSetHnj2han();
}
int WINAPI J2K_SetJWin(void)
{
	return fpJ2KSetJWin();
}
int WINAPI J2K_SetPriorDict(void)
{
	return fpJ2KSetPriorDict();
}
int WINAPI J2K_SetProperty(void)
{
	return fpJ2KSetProperty();
}
int WINAPI J2K_StopTranslation(void)
{
	return fpJ2KStopTranslation();
}
int WINAPI J2K_Terminate(void)
{
	return fpJ2KTerminate();
}
int WINAPI J2K_TranslateChat(void)
{
	return fpJ2KTranslateChat();
}
int WINAPI J2K_TranslateFM(void)
{
	return fpJ2KTranslateFM();
}
char * WINAPI J2K_TranslateMM(void)
{
	return fpJ2KTranslateMM();
}
char * WINAPI J2K_TranslateMMEx(void)
{
	return fpJ2KTranslateMMEx();
}

char *WINAPI J2K_TranslateMMNT(int data0, char *text)
{
	char *output = NULL;
	std::string input = EH_DoScript_Input(text);

	char *trans = fpJ2KTranslateMMNT(data0, input.c_str());
	if (trans)
	{
		printf("Trans: %s\n", trans);
		output = EH_DoScript_Output(trans);
	}
	return output;
}
char * WINAPI J2K_GetJ2KMainDir(void)
{
	return fpJ2KGetJ2KMainDir();
}