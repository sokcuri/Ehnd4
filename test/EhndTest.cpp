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
#include "minhook.h"

struct EZT_INITINFO
{
	bool sig = true;
	int version = 0;
	char dat[MAX_PATH] = { 0, };
	char dll[MAX_PATH] = { 0, };
};

HMODULE hDLL;
bool EZT_Load(HMODULE &hDLL);
bool EZT_Unload(HMODULE &hDLL);
bool EZT_Init(char *AppSig, EZT_INITINFO *InitInfo);

namespace ezt
{
	using J2K_INITIALIZE = int(WINAPI*)(char *);
	J2K_INITIALIZE J2K_Initialize = NULL;

	using J2K_INITIALIZEEX = int(WINAPI*)(char *, char*);
	J2K_INITIALIZEEX J2K_InitializeEx = NULL;

	using J2K_FREEMEM = int(WINAPI*)(void*);
	J2K_FREEMEM J2K_FreeMem = NULL;

	using J2K_GETPRIORDICT = int(WINAPI*)(void);
	J2K_GETPRIORDICT J2K_GetPriorDict = NULL;

	using J2K_GETPROPERTY = int(WINAPI*)(void);
	J2K_GETPROPERTY J2K_GetProperty = NULL;

	using J2K_RELOADUSERDICT = int(WINAPI*)(void);
	J2K_RELOADUSERDICT J2K_ReloadUserDict = NULL;

	using J2K_SETDELJPN = int(WINAPI*)(void);
	J2K_SETDELJPN J2K_SetDelJPN = NULL;

	using J2K_SETFIELD = int(WINAPI*)(void);
	J2K_SETFIELD J2K_SetField = NULL;

	using J2K_SETHNJ2HAN = int(WINAPI*)(void);
	J2K_SETHNJ2HAN J2K_SetHnj2han = NULL;

	using J2K_SETJWIN = int(WINAPI*)(void);
	J2K_SETJWIN J2K_SetJWin = NULL;

	using J2K_SETPRIORDICT = int(WINAPI*)(void);
	J2K_SETPRIORDICT J2K_SetPriorDict = NULL;

	using J2K_SETPROPERTY = int(WINAPI*)(void);
	J2K_SETPROPERTY J2K_SetProperty = NULL;

	using J2K_STOPTRANSLATION = int(WINAPI*)(void);
	J2K_STOPTRANSLATION J2K_StopTranslation = NULL;

	using J2K_TERMINATE = int(WINAPI*)(void);
	J2K_TERMINATE J2K_Terminate = NULL;

	using J2K_TRANSLATECHAT = int(WINAPI*)(void);
	J2K_TRANSLATECHAT J2K_TranslateChat = NULL;

	using J2K_TRANSLATEFM = int(WINAPI*)(void);
	J2K_TRANSLATEFM J2K_TranslateFM = NULL;

	using J2K_TRANSLATEMM = char*(WINAPI*)(void);
	J2K_TRANSLATEMM J2K_TranslateMM = NULL;

	using J2K_TRANSLATEMMEX = char*(WINAPI*)(void);
	J2K_TRANSLATEMMEX J2K_TranslateMMEx = NULL;

	using J2K_TRANSLATEMMNT = char*(WINAPI*)(int, char*);
	J2K_TRANSLATEMMNT J2K_TranslateMMNT = NULL;

	using J2K_GETJ2KMAINDIR = char*(WINAPI*)(void);
	J2K_GETJ2KMAINDIR J2K_GetJ2KMainDir = NULL;

}
// implementation
std::string GetCurrentPathA()
{
	std::string &f([] {
		char _f[MAX_PATH] = { 0, };
		GetModuleFileNameA(GetModuleHandle(NULL), _f, MAX_PATH);
		return std::string(_f);
	}());

	return f.substr(0, f.rfind('\\') + 1);
}

std::wstring GetCurrentPathW()
{
	std::wstring &f([] {
		wchar_t _f[MAX_PATH] = { 0, };
		GetModuleFileNameW(GetModuleHandle(NULL), _f, MAX_PATH);
		return std::wstring(_f);
	}());

	return f.substr(0, f.rfind(L'\\') + 1);
}

int main()
{
	if (!EZT_Load(hDLL))
	{
		printf("EZT_Load Failed\n");
		return 0;
	}

	EZT_INITINFO InitInfo;
	InitInfo.version = 1;
	strcpy(InitInfo.dat, (GetCurrentPathA() + "..\\Common\\Dat").c_str());
	strcpy(InitInfo.dll, (GetCurrentPathA() + "..\\Common\\J2KEngine.dll").c_str());
	
	if (!EZT_Init("EHND", &InitInfo))
	{
		printf("EZT_Init Failed\n");
		return 0;
	}

	printf("Initialization Complete");
	scanf("");
	
	printf(ezt::J2K_TranslateMMNT(0, "‚©‚½ •ø‚«–ƒJƒo?•t Œb?ƒbƒNƒXKADOKAWAƒOƒbƒY?–ñ’÷Ø‚Ü‚Å‚ ‚Æ63“ú2017/10/?’è19Œ¶‘z­—‘åí–²‚³‚ñ‚Ú‚ñ“°“¯l2017/06/17”­”„20ƒTƒNƒ‰ƒm ?ŸN‚ÌX‚Ìã‚ğ•‘‚¤? Œö®ƒrƒWƒ…ƒAƒ‹ƒA?ƒJƒCƒ”‘o—tĞ‘Ğ2017/04/28”­”„ƒAƒjƒ “Á“T•t?ƒCƒgƒ‹                                    ‚°‚Á‚¿‚ãƒuƒƒOEÅV‹L–‚¿‚á‚½‚Ì‚¨‚à‚ç‚µ“ú‹L‘æ22‰ñw‚¨‚ÉƒLƒXH •ø‚«–ƒJƒo?ˆê”Ê”Ì”„Œˆ’èIx?Ÿ—–…Œû‚Ü‚Ğ‚é“ÁWƒCasketƒuƒƒOw” ƒƒOBx‘æ33‰ñ„w”Ş—‚ªˆÙí‘°‚¾‚Á‚½ê‡?‹³‚¦qƒ”‚şƒ“ƒpƒCƒA‚ÌŠÃƒgƒ—ê‘®’²‹³?x–¢Š®¬EƒWƒƒƒPEƒt‚şƒCƒg‰iˆä‹50ü”N‹L”Oì•i ƒAƒjƒuDEVILMAN crybabyv2018”N‰tANetflix‚É‚Ä“Æè‘S¢ŠEŒöŠJI?ŠÄ“Â‚É“’ó­–¾yƒT?ƒJƒXƒRƒ‰?zuD.C.? DreamDays??EƒJ????ƒhƒŠ??ƒfƒCƒYvƒCƒxƒ“ƒgCGŒöŠJ’†IWillplusƒRƒ‰?‘æ250‰ñ?Guiltyw—¸ƒm´?‰Ä‚Ì‹‰Ø‹q‘D‚ÅáÏ‚³‚ê‚éˆ—‚½‚¿?xƒGƒƒV?ƒ“??ƒr?“ÁW!!ƒTƒCƒhƒRƒlƒNƒVƒ‡ƒ“u‰¡‚Â‚È‚ªƒŠƒY?v‘æ272‰ñ?7Œ23“úŠJÃwƒgƒ‰ƒxƒŠƒ“ƒOEƒI?ƒKƒXƒg2017 ?“Œ¶‹¾?x?ƒPƒbƒgˆê”Ê”­”„’†Io‰‰Òî•ñE˜aŠyŠíU—ªƒRƒ‰?E•¨ŒêXVôTVƒAƒjƒu‚Ğ‚È‚±‚Ì?‚Æv6Œ16“ú•ú‘—‚Ì‘æ11˜bu‚ä‚­‚Æ‚µ‚­‚é‚Æ‚µv?“®‰æE‚ ‚ç‚·‚¶•æsƒJƒbƒg‚ªŒöŠJTVƒAƒjƒuƒo?ƒJƒ“ŠïÕ’²¸Š¯v7Œ7“ú‚æ‚è•ú‘—ƒX??ƒgI?TwitterƒLƒƒƒ“ƒy?ƒ“‚àÀ?’†PS4”Åwƒ‹ƒtƒ‰ƒ“‚Ì’n‰º–À?‚Æ–‚—ƒm—·’cx9Œ28“ú‚É”­”„I?Œö®ƒTƒCƒg•l??“®‰æ‚ğŒöŠJVìOVA&ƒCƒxƒ“ƒgã‰fATVƒAƒjƒ‘æ3Šú‚à”­?I?uƒ„?ƒmƒXƒXƒŒö®ƒt‚şƒ“??ƒeƒBƒ“ƒOvƒCƒxƒ“ƒgƒŒ??ƒg‚°‚Á‚¿‚ãƒuƒƒOE˜AÚƒR?ƒi?‚¿‚á‚½‚Ì‚¨‚à‚ç‚µ“ú‹L‘æ22‰ñw‚¨‚ÉƒLƒXH •ø‚«–ƒJƒo?ˆê”Ê”Ì”„Œˆ’èIx?Ÿ—–…Œû‚Ü‚Ğ‚é“ÁWƒCasketƒuƒƒOw” ƒƒOBx‘æ33‰ñ„w”Ş—‚ªˆÙí‘°‚¾‚Á‚½ê‡?‹³‚¦qƒ”‚şƒ“ƒpƒCƒA‚ÌŠÃƒgƒ—ê‘®’²‹³?x–¢Š®¬EƒWƒƒƒPEƒt‚şƒCƒgyƒT?ƒJƒXƒRƒ‰?zuD.C.? DreamDays??EƒJ????ƒhƒŠ??ƒfƒCƒYvƒCƒxƒ“ƒgCGŒöŠJ’†IWillplusƒRƒ‰?‘æ250‰ñ?Guiltyw—¸ƒm´?‰Ä‚Ì‹‰Ø‹q‘D‚ÅáÏ‚³‚ê‚éˆ—‚½‚¿?xƒGƒƒV?ƒ“??ƒr?“ÁW!! ƒP??ƒCƒTƒCƒgQRƒR?ƒh Œg‘Ñ‚Å‚à‚²’•¶‰Â?I‰ïˆõ“o?‚ÅŠÈ’PƒƒOƒCƒ“B‚¨‹CŒy‚É’Ê”Ì‚Å‚«‚Ü‚·BƒP??ƒC‚Å¶‚ÌQRƒR?ƒh‚ğ“Ç‚İæ‚èƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢BiÚ‚µ‚­‚Í‚±‚¿‚çjƒX??ƒgƒtƒHƒ“ƒTƒCƒgQRƒR?ƒh ƒX??ƒgƒtƒHƒ“‚Å‚à?——‰Â?‚ÈSPƒ‚?ƒh”Å‚ğŒöŠJ’†‚Å‚·B¶‚ÌQRƒR?ƒh‚ğ“Ç‚İæ‚èƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢BiÚ‚µ‚­‚Í‚±‚¿‚çj ƒ?ƒ‹?ƒKƒWƒ““o?mƒ?ƒ‹?ƒKƒWƒ““o?‚Í‚±‚¿‚çn’Ê”Ì‚²—˜—p•û•ş | ‚Å‚¶‚½‚é‚°‚Á‚¿‚ã‹äŠy•” | ¤•iw“ü‚Ì•û•ş | ”­”„“ú•ÏX‚É‚Â‚¢‚Ä | ŒˆÏ•û•ş | ‚¨“Í‚¯‚É‚Â‚¢‚Ä | ƒZƒLƒ…ƒŠƒeƒB? | FAQ •ş‹K‚ÉŠî‚Ã‚­?¦ | ƒVƒ‡ƒbƒsƒ“ƒOƒJ?ƒg‚Ì’†g‚ğŒ©‚é | ‰ïˆõî•ñ•ÏX | w“ü—š—ğ‚ÌQÆ ?ƒCƒy?ƒW | ƒTƒCƒgà–¾ | ƒTƒCƒg?ƒbƒv | ‚²—˜—p–ñŠ¼ | ‚¨–â‚¢‡‚í‚¹ | LŒfÚ | ƒŠƒ“ƒN‚É‚Â‚¢‚Ä | ƒX?ƒbƒt•åW | ŒÂlî•ñ•ÛŒì•ûjƒoƒi?* ƒŠƒ“ƒNƒtƒŠ?‚Å‚·B ** “–ƒTƒCƒg‚ÉŒfÚ‚³‚ê‚Ä‚¢‚é‘S‚Ä‚ÌƒeƒLƒXƒgA‰æ‘œ“™‚Ì–³’f?Ú‚ğ‹Ö‚¶‚Ü‚·B£‚±‚Ìƒy?ƒW‚ÌTOP‚Öbƒgƒbƒv‚Ö–ß‚ébŒg‘ÑƒTƒCƒgGetchu.com mobileb?ƒEƒ“ƒ?ƒhƒTƒCƒgDL.Getchu.combƒAƒtƒBƒŠƒGƒCƒgbƒX?ƒbƒt•åWb‚¨–â‚¢‡‚í‚¹b? Getchu.com 1999-2017"));

	/*char *trans = ezt::J2K_TranslateMMNT(0, "asdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfja");
	if (!trans)
	{
		printf("translate failed\n");
		return 0;
	}
	printf("%s\n", trans);
	ezt::J2K_FreeMem(trans);*/


	//for (int i = 0; i < 100; i++)
	//{
	//	printf("%03d: ", i);
	//	printf(ezt::J2K_TranslateMMNT(0, "iƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒ‰ƒbƒvƒXƒeƒBƒbƒNƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvƒXƒeƒbƒvccj"));
	//	//printf(ezt::J2K_TranslateMMNT(0, "ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢ƒAƒNƒZƒX‚µ‚Ä‚­‚¾‚³‚¢"));
	//	printf("\n");
	//}

	if (!EZT_Unload(hDLL))
	{
		printf("EZT_Unload Failed\n");
		return 0;
	}
    return 0;
}

bool EZT_Load(HMODULE &hDLL)
{
	std::wstring dllName = fmt::format(L"{0}Ehnd.dll", GetCurrentPathW());
	hDLL = LoadLibrary(dllName.c_str());
	if (hDLL == NULL)
	{
		MessageBox(0, fmt::format(L"Ehnd file not found: {0}", dllName).c_str(), L"Load Error", MB_ICONERROR);
		return false;
	}

	// Declare eztrans function tables
	std::list<std::pair<char *, LPVOID>> fpTable =
	{
		{ "J2K_Initialize", &ezt::J2K_Initialize },
		{ "J2K_InitializeEx", &ezt::J2K_InitializeEx },
		{ "J2K_FreeMem", &ezt::J2K_FreeMem },
		{ "J2K_GetPriorDict", &ezt::J2K_GetPriorDict },
		{ "J2K_GetProperty", &ezt::J2K_GetProperty },
		{ "J2K_ReloadUserDict", &ezt::J2K_ReloadUserDict },
		{ "J2K_SetDelJPN", &ezt::J2K_SetDelJPN },
		{ "J2K_SetField", &ezt::J2K_SetField },
		{ "J2K_SetHnj2han", &ezt::J2K_SetHnj2han },
		{ "J2K_SetJWin", &ezt::J2K_SetJWin },
		{ "J2K_SetPriorDict", &ezt::J2K_SetPriorDict },
		{ "J2K_SetProperty", &ezt::J2K_SetProperty },
		{ "J2K_StopTranslation", &ezt::J2K_StopTranslation },
		{ "J2K_Terminate", &ezt::J2K_Terminate },
		{ "J2K_TranslateChat", &ezt::J2K_TranslateChat },
		{ "J2K_TranslateFM", &ezt::J2K_TranslateFM },
		{ "J2K_TranslateMM", &ezt::J2K_TranslateMM },
		{ "J2K_TranslateMMEx", &ezt::J2K_TranslateMMEx },
		{ "J2K_TranslateMMNT", &ezt::J2K_TranslateMMNT },
	};
	for (auto &p : fpTable)
	{
		if ((*reinterpret_cast<LPVOID *>(p.second) =
			reinterpret_cast<LPVOID>(
				GetProcAddress(hDLL, p.first)
				)) == NULL)
		{
			MessageBoxA(0, fmt::format("Load Failed - {0}", p.first).c_str(), "Hook Error", MB_ICONERROR);
			return false;
		}
	}
	return true;
}

bool EZT_Unload(HMODULE &hDLL)
{
	FreeLibrary(hDLL);
	hDLL = NULL;
	return true;
}

bool EZT_Init(char *AppSig, EZT_INITINFO *InitInfo)
{
	return ezt::J2K_InitializeEx("Ehnd", reinterpret_cast<char *>(InitInfo));
}
