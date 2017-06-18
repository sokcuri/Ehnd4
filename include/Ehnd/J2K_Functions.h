#pragma once
#include <Windows.h>

struct EZT_INITINFO
{
	bool sig = false;
	int version = 0;
	char dat[MAX_PATH] = { 0, };
	char dll[MAX_PATH] = { 0, };
};

// J2K Functions
using J2K_INITIALIZE = int(WINAPI*)(char *);
extern J2K_INITIALIZE fpJ2KInitialize;

using J2K_INITIALIZEEX = int(WINAPI*)(char *, char*);
extern J2K_INITIALIZEEX fpJ2KInitializeEx;

using J2K_FREEMEM = int(WINAPI*)(void*);
extern J2K_FREEMEM fpJ2KFreeMem;

using J2K_GETPRIORDICT = int(WINAPI*)(void);
extern J2K_GETPRIORDICT fpJ2KGetPriorDict;

using J2K_GETPROPERTY = int(WINAPI*)(void);
extern J2K_GETPROPERTY fpJ2KGetProperty;

using J2K_RELOADUSERDICT = int(WINAPI*)(void);
extern J2K_RELOADUSERDICT fpJ2KReloadUserDict;

using J2K_SETDELJPN = int(WINAPI*)(void);
extern J2K_SETDELJPN fpJ2KSetDelJPN;

using J2K_SETFIELD = int(WINAPI*)(void);
extern J2K_SETFIELD fpJ2KSetField;

using J2K_SETHNJ2HAN = int(WINAPI*)(void);
extern J2K_SETHNJ2HAN fpJ2KSetHnj2han;

using J2K_SETJWIN = int(WINAPI*)(void);
extern J2K_SETJWIN fpJ2KSetJWin;

using J2K_SETPRIORDICT = int(WINAPI*)(void);
extern J2K_SETPRIORDICT fpJ2KSetPriorDict;

using J2K_SETPROPERTY = int(WINAPI*)(void);
extern J2K_SETPROPERTY fpJ2KSetProperty;

using J2K_STOPTRANSLATION = int(WINAPI*)(void);
extern J2K_STOPTRANSLATION fpJ2KStopTranslation;

using J2K_TERMINATE = int(WINAPI*)(void);
extern J2K_TERMINATE fpJ2KTerminate;

using J2K_TRANSLATECHAT = int(WINAPI*)(void);
extern J2K_TRANSLATECHAT fpJ2KTranslateChat;

using J2K_TRANSLATEFM = int(WINAPI*)(void);
extern J2K_TRANSLATEFM fpJ2KTranslateFM;

using J2K_TRANSLATEMM = char*(WINAPI*)(void);
extern J2K_TRANSLATEMM fpJ2KTranslateMM;

using J2K_TRANSLATEMMEX = char*(WINAPI*)(void);
extern J2K_TRANSLATEMMEX fpJ2KTranslateMMEx;

using J2K_TRANSLATEMMNT = char*(WINAPI*)(int, const char*);
extern J2K_TRANSLATEMMNT fpJ2KTranslateMMNT;

using J2K_GETJ2KMAINDIR = char*(WINAPI*)(void);
extern J2K_GETJ2KMAINDIR fpJ2KGetJ2KMainDir;
