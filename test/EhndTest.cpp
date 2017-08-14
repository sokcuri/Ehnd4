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
#include "../include/Interface/Ehnd.h"

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

namespace ehnd
{
	using EH_CREATEINSTANCE = IEhnd*(WINAPI*)(void);
	EH_CREATEINSTANCE EH_CreateInstance = NULL;
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

	printf("Initialization Complete\n");

	auto ehInst = ehnd::EH_CreateInstance();
	printf("Version: %d\n", ehInst->GetVersion());

	if (!ehInst->Open(EHND_ENGINE_EZT_J2K)) {
		printf("Open Failed: %x\n", ehInst->GetLastError());
		return false;
	}

	WCHAR *test = 0;
	if (!ehInst->TranslateText(L"긲뺝뢜갶궓뽦궋뜃귦궧갶? Getchu.com 1999-2017", &test)) {
		printf("Translate Failed: %x\n", ehInst->GetLastError());
	}

	ehInst->SendEngineMessage(EHND_MSG_EZTJ2K_RELOAD_USERDICT, 0, 0);

	printf("String Test: %s\n", test);
	return true;

	auto ET_GetChu_String = []() {
		auto result = ezt::J2K_TranslateMMNT(0, "top귉TOP ?귽긻?긙궟뿕뾭긊귽긤긂긃긳뿗쀰Twitter궇궖궽밲귺?깑긣TOPTOP긒??귺긦긽돶뒁긐긞긛뺱궖뼃룕먒갋랦럮벏릐룛맜뛀DL귺?깑긣긳깓긐     뤬띢뙚랊  긌긿깛긻?깛  궓딠궸볺귟  긇?긣귩뙥귡뜞뙉궻?귽긣깑 깋깛긌깛긐 ?뽵 긜?깑긚 긳깋깛긤덇뿓 벫밫븊 벫밫됪몴 뵯봽볷빾뛛륃뺪 Twitter 긽깑?긊 됵덒긵깒?깛긣긆긚긚긽룮뷼 띮궑궶궋붯룛궻덄궲궔궫 뺱궖뼃긇긫?븊 똟?긞긏긚 긇?긤긲귷귽긣!! 깞귷깛긊?긤G 긳?긚??긬긞긏... 귺?긇긩? 긖긂깛긤긣깋긞긏CD 몥궻붯뺴궻긲긅?깏긛? EXTRA 1 VOCAL걬SOUND COL... 긚긻깑긇?긤긚긣깋귽긏-긖귽긎깈긂긙긳깑?-걅벏... 긐깏긗귽귺 긲귷깛긣?긣깏긊? 묉3뒱 ?긻긚긣깏... Megami MAGAZINE 2017봏6뙉뜂 궓뒁궢귒CD128 To LOVE귡?궴귞귆귡? 긘깏?긛10뢂봏귺긦긫?긖깏... 궞궻멹맧귞궢궋맊둉궸뢪븶귩갏2 묉4뒱 Blu-ray Dis... Twitter걮Getchu.com_n           깒귺귺귽긡?GET궻?긿깛긚걲 몓궋롌룦궭걲궓몓귕궸갏 긚?긞긲뺝뢜뭷궟돒뺝궓뫲궭궢궲귏궥갏  TOP NEWS?궖돷귣궢륡럣궕뽥궑귡긌긿깛긻?깛궸걏muku걐먩맯궻륡럣귩믁돿갏1됷궻뭾빒뗠뒂15,000?댥뤵궳4롰쀞궻륡럣궔귞궓뛆궖궶귖궻귩긵깒?깛긣갏걏muku걐먩맯궻륡럣귩믁돿궢귏궢궫괃뺱궖뼃궳뾎뼹궶걏긲깒긚걐귝귟TV귺긦긽걑긟귽깛긄깛긙긃깑BREAK걒궻긭깓귽깛걏밮뙉귕궙귡걬볽뙉궥귒귢걐궻뺱궖뼃긇긫?궕뵯봽뙂믦갏긌긿깋긏??긢긗귽깛갋몟띿됪듒벬걏뛼떞귒궔걐럞?궖돷귣궢궻띿됪귩뙰궸갂뺱궖뼃긇긫?궸띍밙궶됪렲궸궶귡귝궎띋뮧맢귩뛱궯궫럧뗂궻뺱궖뼃긇긫?갏6/19걁뙉걂뛛륷  걑NEW GAME!!걒BD걬DVD멣6뒱궕?뽵둎럑걲궛궯궭귙멣뒱벫밫궼긆깏긙긥깑B2?긻긚긣깏?갂궠귞궸둫뒱궸궼긆깏긙긥깑?긚긣긇?긤벫밫븊갏먩뭶?뽵긌긿깛긻?깛귖렳?뭷괃묉덇뒱귩궟?뽵뮯궋궫뺴궸궼갂먩뭶궳띿롌갋벦?맫뫞쁚먩맯?궖돷귣궢걏궿귅귒궻A3긏깏귺?긚??걐귖븊궋궲궖귏궥갏뼰궘궶귟렅묉궸뢎뿹궳궥궻궳궓뙥벀궢궶궘갏6/17걁뱘걂뛛륷  긭깓귽깛븵Ver궻걏궺귪궵귣궋궵돿뱻똟걐븊궖궻긲귷깛긳긞긏걑띮궑궶궋붯룛궻덄궲궔궫 Memorial 뙽믦붎걒?뽵둎럑갏빒뚆뼟뢁?궻룷먣귘갂긌긿깋긏??됶먣갂깒귺귽깋긚긣궶궵귩뢁?궢궫뎘땦뺎뫔붎궻걏띮궑긇긩걐긲귷깛긳긞긏궕뱋뤾갏6/16걁뗠걂뛛륷  Getchu.com뮧귊걑2017봏됂귺긦긽붥멺?걒귩뚺둎걲걏NEW GAME!!걐걏밮럊궻3P걐걏먰뷥먥룯긘깛긲긅긎귺AXZ걐궶궵쁞묋궻됂귺긦긽륃뺪귩?긃긞긏갏릯렄륃뺪귩뛛륷궢궲랷귟귏궥궻궳귝귣궢궘궓딂궋궢귏궥갃됂귺긦긽롥묋됊긻?긙걬됂귺긦긽BD갋DVD긻?긙귖뚺둎뭷괃  걙Casket긳깓긐걑뵠깓긐갃걒묉33됷걚걑붯룛궕댶롰뫎궬궯궫뤾뜃?떝궑럔깞귷깛긬귽귺궻듑긣깓쀪뫌뮧떝?걒뼟뒶맟갋긙긿긑갋긲귷귽긣  뎘덁뜈50뢂봏딯봑띿뷼 귺긦긽걏DEVILMAN crybaby걐2018봏룊뢶갂Netflix궸궲벲먫멣맊둉뚺둎갏?듒벬궸뱬먶맠뼻  딖뫲궻됂귺긦긽걑NEW GAME!!걒OP긡??갂ED긡??갂긌긿깋긏???깛긐긘깏?긛1?4궸갂궛궯궭귙뛶볺벫밫갋긆깏긙긥깑?긚긣긇?긤벫밫븊궕뙂믦갏OP갋ED롥묋됊궸궼 긆깏긙긥깑?긚긣긇?긤궕갂긌긿깋긏???깛긐궼vol.1?4쁀벍궳?긚긣긇?긤괪뻼긜긞긣궕벫밫궳귖귞궑귏궥갏  긖귽긤긓긨긏긘깈깛걏돘궰궶궕깏긛?걐묉272됷?7뙉23볷둎띊걑긣깋긹깏깛긐갋긆?긊긚긣2017 ?뱧뙳떮?걒?긑긞긣덇붗뵯봽뭷갏뢯뎶롌륃뺪갋쁝뒁딇뛘뿪긓깋?갋븿뚭뛛륷괃  걑띮궑궶궋붯룛궻덄궲궔궫괂걒BD걬DVD묉1뒱갋?띹뺡릐?궖돷귣궢긙긿긑긞긣귽깋긚긣궕뚺둎걲귽긹깛긣?긑긞긣뾆먩붛봽?뜛뙏궶궵뜈됗벫밫븊궻?뒱궼7/26뵯봽갏똟갋뎟뿙갲갋럪덳먩봸궻릣뭶럓궕炤궢궋?궖돷귣궢긙긿긑긞긣궕뚺둎갏뒶멣맯럀뙽믦붎궸궼뙱띿롌갋듴뚈럍뼻룕궖돷귣궢룷먣똣띦긳긞긏깒긞긣귘긎긿깑긒?긇긫??깛긐뢁?궻벫밫CD궶궵뜈됗벫밫븊궖궳궥귝갏  TV귺긦긽걏궿궶궞궻?궴걐6뙉16볷뺳몭궻묉11쁞걏귚궘궴궢궘귡궴궢걐?뜍벍됪갋궇귞궥궣걬먩뛱긇긞긣궕뚺둎  TV귺긦긽걏긫?긇깛딉먘뮧뜽뒸걐7뙉7볷귝귟뺳몭긚??긣갏?Twitter긌긿깛긻?깛귖렳?뭷  TV귺긦긽걏뱆멢?깑긤깒깛걐궕뢁?궠귢궫뙱띿긓?긞긏궻뙽믦붎9뒱?11뒱궕?뽵둎럑갏묉9뒱궼DVD뛶볺롌귽긹깛긣?긑긞긣뾆먩뛶볺?궢뜛귒뙏궕븬볺궠귢귏궥갃  걑Ninetail Chronicle Vocal Collection걒?뽵둎럑걲ninetail똭띿뷼궻긒??롥묋됊28뗁귩뢜귕궫롮뗃궻긖긂깛긤긣깋긞긏갏ninetail뵯뫉궔귞12봏갃럒뻺긳깋깛긤궳궇귡dualtail갋tritail궻뗁귩귏궴귕궲뢁?갏 륷띿긐긞긛?뽵둎럑갏걏sin 렦궰궻묈띬 긇긥궭귂귺긏깏깑?긿??걁10롰걂걐/걏긳깓긞긓깏?긌긿깋긏??긚깏?긳 먪쀶걭뼔됓 Ver.2걁3롰걂갂TCG뼔?긵깒귽?긞긣걁3롰걂걐/걏긳깓긞긓깏?긌긿깋긏??긚깏?긳 Angel Beats갏갂긌긿깋긏??뼔?깋긫??긞긣 Ver.3갂긌긿깋긏??긢긞긌긑?긚긓깒긏긘깈깛MAX걐/걏긳깓긞긓깏?긌긿깋긏??긚깏?긳 뻷둉먰딯긢귻긚긊귽귺긘깏?긛걁2롰걂갂긌긿깋긏??뼔?깋긫??긞긣걐/걏긌긿깋긏??뼔?깋긫??긞긣 뙅뤻뾈볖궼뾇롌궳궇귡걁2롰걂걐/걏긌긿깋긏??뼔?깋긫??긞긣 CLANNAD?긏깋긥긤?걐/걏긌긿깋긏??뼔?깋긫??긞긣 릋똼궻땺걁2롰걂걐/걏TCG뼔?긵깒귽?긞긣 Charlotte걁2롰걂걐/걏뭶궧궔궑갋궇궘궢귛귪갏궸궋궲귪궟 Free갏-Eternal Summer- 뤌돦셻걐 걁CD걂륷띿?뽵둎럑갏걏BLCD걏긻깛긢깄깋??뢡릐긆긽긊긫?긚?걐[궟뻁뷏긄긞?붦]걐/걏긤깋?CD 궩귢궼궠궠귘궔궶쀶궻궼궣귏귟?뛼쁐뵻릐걁CV갌뜴쁝?뭷걂걐/걏BLCD걏궓쀗궠귪궭궻똝믫럷륃?뱻덁됄궻뤾뜃?걐?뛼믆뭧릐갂뵏덁뾋됳걐/걏걏DIABOLIK LOVERS CHAOS LINEAGE걐 Vol.2 VIOLET걐/걏DIABOLIK LOVERS Para-Selene Vol.5 땤뒱깋귽긣?땤뒱깋귽긣걁CV갌빟먯묈뺛걂걐/걏긤깋?CD걏귺귽궻궇귡맯뒋 Vol.2 벏맩3봏뽞걐?쁝뻶걁CV갌긡긣깋?긞긣뱋걂걐 륷띿?뽵둎럑갏걏?뤾붎?긑긞긣긾깛긚???긌?궸궖귕궫갏?깄?긙긞긏긓깒긏긘깈깛걐/걏BanG Dream갏 긌긿깋긏???깛긐걏?귽긣깑뼟믦걐?랹릟뜾댗걁CV갌묈떞띒뛻걂걐/걏BanG Dream갏 긌긿깋긏???깛긐걏?귽긣깑뼟믦걐?럖깣묳뾎띸걁CV갌댦뱻띒뜾걂걐/걏뙝룷돫궭귗귪궺귡 OP긡???ED긡??걏?귽긣깑뼟믦걐?WAOOON걐6/15걁뽜걂뛛륷  걑Angel Beats갏 PERFECT VOCAL COLLECTION걒긙긿긑긞긣궕뚺둎걲룊됷븬볺벫밫궻걏Key Sounds Label Release Party 2017걐귽긹깛긣?긑긞긣돒뺝긘깏귺깑궸귖뭾뽞갏뎕몴궴돶뒁궻뾝뜃궳?먣궴궶궯궫걑Angel Beats갏걒궻??긇깑뗁귩멣궲뽘뾽갂궠귞궸1봏귆귟궴궶귡 Girls Dead Monster궻륷뗁걏Hungry Song걐귖뢁?궠귢궲귏궥귝!!  PS4붎걑깑긲깋깛궻뭤돷뼽?궴뻷룛긩뿷뭖걒9뙉28볷궸뵯봽갏?뚺렜긖귽긣걬릐??벍됪귩뚺둎  륷띿OVA&귽긹깛긣뤵뎕갂TV귺긦긽묉3딖귖뵯?갏?걏깂?긩긚긚긽뚺렜긲귷깛??긡귻깛긐걐귽긹깛긣깒??긣  걑긊?깑긛걬긬깛긟귷? ?뤾붎걒귺깛긟귻긆뛼뛝궻븲묂뮮걏긻긬깓긦걐궻릣뭶럓귩긩깏궴맖궋궳긲귻긎깄귺돸갏2릐뤸귟궻땺묈궶븖궖쀖귘묇띆궸맰귟뜛귏귢궫띀띢뛊궻CV33궶궵?뫬댥둖궸귖뙥룋뼖띦갏긆?긑긬?긟궸긻?긬?긏깋긲긣귖갏  궓귖궭궩귅궴긳깓긐걓궓귖깓긐걕걫3?븵몧귖궔귦궋궋갏걏궇귡궋궼쀶궴궋궎뼹궻뻷뺷걐궻뛖귟븫빁귩?깋깏  PRESTAR긓깋??yozuca*긢긮깄?15뢂봏딯봑귽긹깛긣둎띊갏 걏PRESTAR LIVE 4th FESTIVAL걐궸긚긻긘긿깑긒긚긣궴궢궲뢯뎶궢귏궥갃  걑딝벍먰럐긊깛?? THE ORIGIN V 똽벺 깑긂?됵먰걒BD걬DVD궕?뽵둎럑걲뜞궶귞먩뭶궳륷딮?궖돷귣궢귽깋긚긣럊뾭궻A4긏깏귺긲귷귽깑벫밫븊궖갏쀝똶뵯뛱븫릶1,000뼔븫귩뚓귡갂댝뷚쀇쁝궸귝귡묈긭긞긣긓?긞긏긚걑딝벍먰럐긊깛?? THE ORIGIN걒궕궰궋궸귺긦긽돸갃궞귢궕덇봏먰몚궻?렳궳궇귡??갃 륷띿긲귻긎깄귺?뽵둎럑갏걏궺귪궵귣궋궵 깏?깏긄걁?긑긞긣긾깛긚?? 긖깛갋??깛걂걐/걏궺귪궵귣궋궵 긂긅?긚긬귽긣걁듞묂궞귢궘궢귛귪 ?듞궞귢?걂걐/걏룊돶?긏GT긵깓긙긃긏긣 깒?긘깛긐?긏2016 TeamUKYO돒뎴Ver.걐/걏뮪렅뙰긒귽? 긨긵긡깄?긧 긩깗?깑 떍뎙릣뭶 뿧궭??긛ver.걐/걏SUWAHIME PROJECT 뙷붨긖깋걐/걏긩?긒??갋긩?깋귽긲 뵏[띋붛]걐 ?뽵믵먛궼걏6/15걐귏궳갏걏긽긊긚긣귺걐똣띦?궖돷귣궢귽깋긚긣궕?긻긚긣깏?궸궶궯궲뱋뤾갏걏귝궎궞궩갏"\
			"긚긑긹긄깑긲궻륺귉 깑?긘긃걬귽깞깏깛 B2?긻긚긣깏?걐/걏밮뙅궋긌긿긞긚깑?귽긚?? 긲귻귺 B2?긻긚긣깏?걐/걏뢶돶귺깏긚걭긐깋? 雲벐뽯갲 B2?긻긚긣깏?걐/걏?깛긡귽긜긳깛 닣븫?귟뽯 B2?긻긚긣깏?갂돘뛞뽶럔 B2?긻긚긣깏?걐 럫뮢벍됪뚺둎갏걏룷뽰뾈롽 3rd?긦귺깑긫?걏긬?긡귻??깛3걐?룷뽰뾈롽걐 럫뮢벍됪뚺둎갏걏걏뭷돍벺봨걐[DVD븊]?귽긣깚긇긘걐/걏긆깑?깛긘귺 2nd긘깛긐깑걏Purple rays걐[DVD븊룊됷뙽믦붦] ?긆깑?깛긘귺걁댦뮼뫚럤걁CV갌룷杉닟뿘걂갂댦뮼뫚뾸됓걁CV갌됓롧귚귒귟걂걐/걏BanG Dream갏 긌긿깋긏???깛긐걏됓?밺딠긎??!!!걐?됓?궫궑걁CV갌묈믆롋뎟걂걐걁CM걂/걏뻃띹닩맯 긹긚긣귺깑긫?걏love your Best걐[DVD븊룊됷맯럀뙽믦붦]?뻃띹닩맯걐 륷띿긐긞긛?뽵둎럑갏걏긄깓?깛긊먩맯 ?긐긇긞긵갂귇궭궞귢갏귺긏깏깑긌?긼깑??걁2롰걂갂긏깏귺긲귷귽깑걁2롰걂걐/걏?깓궔귞럑귕귡뻷뺷궻룕 B2?긻긚긣깏?걁2롰걂갂긏깏귺긲귷귽깑걁2롰걂걐/걏??긤갋긆깋긣깏귺 ?깛긙깈깛궸뢯됵궋귩땫귕귡궻궼듩댾궯궲궋귡궬귣궎궔 둖? B2?긻긚긣깏?갂긾긫귽깑긫긞긡깏?걐/걏귺긏깏깑긌?긼깑?? Re갌CREATORS걁3롰걂갂긌긿깋긬긚갂긪?긤긑?긚 iPhone 6/6s/7뙎뾭갂듙긫긞긙걁3롰걂걐/걏??긤귺?긣갋긆깛깋귽깛 귽긽?긙긬?긇?걁2롰?2긖귽긛걂갂긐깋긚갂긮긞긐긏긞긘깈깛갂긼긞긏븊궖긣?긣긫긞긐갂?긦긏깏귺?긚??걁2롰걂걐/걏깋긳깋귽긳갏긖깛긘긿귽깛!! 깋긫?긚긣깋긞긵긓깒긏긘깈깛걐/걏궞궻멹맧귞궢궋맊둉궸뢪븶귩갏2 B2?긻긚긣깏?갂?긦긏깏귺?긚??걁2롰걂갂깋긫?긚긣깋긞긵긓깒긏긘깈깛걐/걏긇?긤긌긿긵??궠궘귞 긻깛긑?긚걁3롰걂갂긕?깑긤A5깏깛긐긩?긣걁4롰걂갂긕?깑긤A6긽긾걁4롰걂갂븊秀긜긞긣걁2롰걂갂듙볺귟긽긾걁4롰걂갂긓깛긬긏긣?깋?걁2롰걂걐 륷띿?뽵둎럑갏걏?뤾붎 뜒럔궻긫긚긑 LAST GAME Blu-ray Disc 걙벫몧뙽믦붎걚걐/걏뷏룺룛먰럐긜?깋???깛R Blu-ray COLLECTION VOL.1걐/걏돹뽋먰묂긕깋귽?? Blu-ray Disc걐/걏긚?긬?먰묂긘깏?긛 덯뭹먰묂긌깄긂깒깛긙긿? VOL.4걐/걏덯뭹먰묂긌깄긂깒깛긙긿? Episode of 긚긡귻깛긊? Blu-ray Disc걐 륷띿?뽵둎럑갏걏Re:CREATORS ED긡??걏깑긮긓깛걐[DVD븊딖듩맯럀귺긦긽뙽믦붦]/ 랳뙉궻긬깛?긘귺걐/걏긢귻긽깛?깑?깛 깓귽긤궻긇깑긡 SOUNDSHOT?룷뽰뙧뤞걐/걏뙱뾕렳갋볦먪롋뱋궻궾궘궾궘뫚 깋긙긆귺?긇귽긳걐/걏떕둉궻RINNE 묉3긘깏?긛 OP긡??걏긜긟긥깇긽?긘걐[DVD븊룊됷뙽믦붦]/KEYTALK걐/걏몂맦궻덦뾸럗 Music Collection Album걐 륷띿?뽵둎럑갏걏긤깋?CD걏궴귣궴귣 궵귡궭궏 긌긿깋긽깑궑궯궭뺂걐?뻸뛞뾋걁CV갌뱘뽩봎걂걐/걏긤깋?CD걏?긏궫궭궻럏둷궶듫똚걐?SIDE갌2-붶둷?띮?붶둷?띮걁CV갌뱘뽩봎걂걐 걁뎕몴걂륷띿?뽵둎럑갏걏뼯돞뜎궴뼭귢귡100릐궻돞럔뾩 긘깈?긣 DVD 뤵뒱걐/걏븨묇 뱚뙐뿉븨 ?? 떺궻벲듻뿳걙룊됷맯럀뙽믦붎걚 Blu-ray Disc걐 [갷됡땸궻뛛륷뿗쀰궼궞궭귞갃]궇궶궫귉궻긆긚긚긽깓긏궳궶궢뻷뢱뛳럗궴뗕딏떝밫 뫯릣뫯땦긚긡긞긇? 깏귻긄깑걖깒귽긲긅?갷깓긏궳궶궢뻷뢱뛳럗궴뗕딏떝밫 뫯릣뫯땦긚긡긞긇? 깏귻긄깑걖깒귽긲긅?갷귺긦궾귪묈뷨됆걅벏릐럮걆귺긦궾귪묈뷨됆걅벏릐럮걆궞궻멹맧귞궢궋맊둉궸뢪븶귩갏 12 걙긆깏긙긥깑귺긦긽BD븊궖벏뜪붎걚궞궻멹맧귞궢궋맊둉궸뢪븶귩갏 12 걙긆깏긙긥깑귺긦긽BD븊궖벏뜪붎걚sin 렦궰궻묈띬 묉덇궻띬 Blu-ray Disc걙룊됷뙽믦붎걚[갷sin 렦궰궻묈띬 묉덇궻띬 Blu-ray Disc걙룊됷뙽믦붎걚[갷띮궑궶궋붯룛궻덄궲궔궫 Memorial걙궺귪궵귣궋궵돿뱻똟 긭깓귽깛갷띮궑궶궋붯룛궻덄궲궔궫 Memorial걙궺귪궵귣궋궵돿뱻똟 긭깓귽깛갷HULOTTE SONGS BESTHULOTTE SONGS BEST깓긏궳궶궢뻷뢱뛳럗궴뗕딏떝밫 긤?긡깏귺 깏귻긄깑깓긏궳궶궢뻷뢱뛳럗궴뗕딏떝밫 긤?긡깏귺 깏귻긄깑깓긏궳궶궢뻷뢱뛳럗궴뗕딏떝밫 긇긗깏? 깏귻긄깑깓긏궳궶궢뻷뢱뛳럗궴뗕딏떝밫 긇긗깏? 깏귻긄깑긳깓긞긓깏?긌긿깋긏??긚깏?긳 먪쀶걭뼔됓 ?깋긖긽 Ver.2긳깓긞긓깏?긌긿깋긏??긚깏?긳 먪쀶걭뼔됓 ?깋긖긽 Ver.2뙳몒룺룛묈먰뼯뙳몒룺룛묈먰뼯띮궑궶궋붯룛궻덄궲궔궫 뺱궖뼃긇긫?븊 똟?긞긏긚띮궑궶궋붯룛궻덄궲궔궫 뺱궖뼃긇긫?븊 똟?긞긏긚뾠룛먰딯 3 Blu-ray Disc뾠룛먰딯 3 Blu-ray Disc긖긩긫긂귻긞? 긆깏긙긥깑갋긖긂깛긤긣깋긞긏긖긩긫긂귻긞? 긆깏긙긥깑갋긖긂깛긤긣깋긞긏몥궻붯뺴궻긲긅?깏긛? EXTRA 1 VOCAL걬SOUND COL갷몥궻붯뺴궻긲긅?깏긛? EXTRA 1 VOCAL걬SOUND COL갷깓긏궳궶궢뻷뢱뛳럗궴뗕딏떝밫 긬긚긑?긚 깏귻긄깑걖깒귽긲긅?긤깓긏궳궶궢뻷뢱뛳럗궴뗕딏떝밫 긬긚긑?긚 깏귻긄깑걖깒귽긲긅?긤빿뼳쀳됌 깗?긏긚긹긚긣걏FLOWER PAINTER걐?빿뼳쀳됌빿뼳쀳됌 깗?긏긚긹긚긣걏FLOWER PAINTER걐?빿뼳쀳됌긇?긤긲귷귽긣!! 깞귷깛긊?긤G 긳?긚??긬긞긏 뿳뛠둶먂걁1BO갷긇?긤긲귷귽긣!! 깞귷깛긊?긤G 긳?긚??긬긞긏 뿳뛠둶먂걁1BO갷To LOVE귡?궴귞귆귡? 긘깏?긛10뢂봏귺긦긫?긖깏?긳긞긏 궴갷To LOVE귡?궴귞귆귡? 긘깏?긛10뢂봏귺긦긫?긖깏?긳긞긏 궴갷긚긻깑긇?긤긚긣깋귽긏-긼깗귽긣귺깛긤긳깋긞긏-걅벏릐긐긞긛걆긚긻깑긇?긤긚긣깋귽긏-긼깗귽긣귺깛긤긳깋긞긏-걅벏릐긐긞긛걆긐깏긗귽귺 긲귷깛긣?긣깏긊? 묉3뒱 ?긻긚긣깏?벏뜪붎긐깏긗귽귺 긲귷깛긣?긣깏긊? 묉3뒱 ?긻긚긣깏?벏뜪붎Megami MAGAZINE 2017봏6뙉뜂Megami MAGAZINE 2017봏6뙉뜂긐깏긗귽귺 긲귷깛긣?긣깏긊? 묉3뒱긐깏긗귽귺 긲귷깛긣?긣깏긊? 묉3뒱Ceui 10th Anniversary Album - Game 갷Ceui 10th Anniversary Album - Game 갷귺?긇긩? 긖긂깛긤긣깋긞긏CD귺?긇긩? 긖긂깛긤긣깋긞긏CDMegami MAGAZINE 2017봏7뙉뜂Megami MAGAZINE 2017봏7뙉뜂띮궑궶궋붯룛궻덄궲궔궫괂 杉뫚갋긚긻깛긖?갋뎟뿙갲 릣뭶Ver. 1/갷띮궑궶궋붯룛궻덄궲궔궫괂 杉뫚갋긚긻깛긖?갋뎟뿙갲 릣뭶Ver. 1/갷궓뒁궢귒CD128궓뒁궢귒CD128긟귽깛긄깛긙긃깑BREAK 밮뙉귕궙귡 뺱궖뼃긇긫?긟귽깛긄깛긙긃깑BREAK 밮뙉귕궙귡 뺱궖뼃긇긫?궞궻멹맧귞궢궋맊둉궸뢪븶귩갏2 묉4뒱 Blu-ray Disc걙뙽믦갷궞궻멹맧귞궢궋맊둉궸뢪븶귩갏2 묉4뒱 Blu-ray Disc걙뙽믦갷긊깛??긄?긚 2017봏6뙉뜂긊깛??긄?긚 2017봏6뙉뜂깓긏궳궶궢뻷뢱뛳럗궴뗕딏떝밫 뫯릣뫯땦긚긡긞긇? 깏귻긄깑걖깒귽긲긅?갷깓긏궳궶궢뻷뢱뛳럗궴뗕딏떝밫 뫯릣뫯땦긚긡긞긇? 깏귻긄깑걖깒귽긲긅?갷귺긦궾귪묈뷨됆걅벏릐럮걆귺긦궾귪묈뷨됆걅벏릐럮걆궞궻멹맧귞궢궋맊둉궸뢪븶귩갏 12 걙긆깏긙긥깑귺긦긽BD븊궖벏뜪붎걚궞궻멹맧귞궢궋맊둉궸뢪븶귩갏 12 걙긆깏긙긥깑귺긦긽BD븊궖벏뜪붎걚sin 렦궰궻묈띬 묉덇궻띬 Blu-ray Disc걙룊됷뙽믦붎걚[갷sin 렦궰궻묈띬 묉덇궻띬 Blu-ray Disc걙룊됷뙽믦붎걚[갷띮궑궶궋붯룛궻덄궲궔궫 Memorial걙궺귪궵귣궋궵돿뱻똟 긭깓귽깛갷띮궑궶궋붯룛궻덄궲궔궫 Memorial걙궺귪궵귣궋궵돿뱻똟 긭깓귽깛갷HULOTTE SONGS BESTHULOTTE SONGS BEST깓긏궳궶궢뻷뢱뛳럗궴뗕딏떝밫 긤?긡깏귺 깏귻긄깑깓긏궳궶궢뻷뢱뛳럗궴뗕딏떝밫 긤?긡깏귺 깏귻긄깑깓긏궳궶궢뻷뢱뛳럗궴뗕딏떝밫 긇긗깏? 깏귻긄깑깓긏궳궶궢뻷뢱뛳럗궴뗕딏떝밫 긇긗깏? 깏귻긄깑긳깓긞긓깏?긌긿깋긏??긚깏?긳 먪쀶걭뼔됓 ?깋긖긽 Ver.2긳깓긞긓깏?긌긿깋긏??긚깏?긳 먪쀶걭뼔됓 ?깋긖긽 Ver.2뙳몒룺룛묈먰뼯뙳몒룺룛묈먰뼯띮궑궶궋붯룛궻덄궲궔궫 뺱궖뼃긇긫?븊 똟?긞긏긚띮궑궶궋붯룛궻덄궲궔궫 뺱궖뼃긇긫?븊 똟?긞긏긚뾠룛먰딯 3 Blu-ray Disc뾠룛먰딯 3 Blu-ray DiscPrevNext륷뭶룮뷼갏 ?뤾붎몟뢜뺂 긆?긫?깓?긤 멟뺂 븉?롌궻돞 ?뤾붎 듞묂궞귢궘궢귛귪 -듞궞귢- Blu-ray Disc걙뙽믦붎걚 ??긤귺?긣갋긆깛깋귽깛 Blu-ray Disc BOX걙뒶멣맯럀뙽믦붎걚 planetarian?맦궻릐? Blu-ray Disc걙뮪뜈됗붎걚 똍궻뼹궼갃 Blu-ray Disc걙긓깒긏??긛갋긄긢귻긘깈깛 4K Ultra HD Blu-ray 룊됷맯럀뙽믦걚 HULOTTE SONGS BEST 몥궻붯뺴궻긲긅?깏긛? EXTRA 1 VOCAL걬SOUND COLLECTION 귺?긇긩? 긖긂깛긤긣깋긞긏CD 띮궑궶궋붯룛궻덄궲궔궫 Character Song Collection [딖듩맯럀뙽믦붦] 깋긳깋귽긳갏긖깛긘긿귽깛!! Guilty Kiss 2nd긘깛긐깑걏긓깗깒깂긚긌걐?Guilty Kiss ?갋쀶뷥괅뼯몒 -둽뼺- 몥밮궻봢돞 궔귪궫궔?궖돷귣궢 몔?[됗쀔] A1?긻긚긣깏?걓Getchu.com뙽믦붛봽걕 띮궑궶궋붯룛궻덄궲궔궫 뺱궖뼃긇긫?븊 똟?긞긏긚 깓긏궳궶궢뻷뢱뛳럗궴뗕딏떝밫 맕븵깏귻긄깑걬긚긏릣깏귻긄깑 뺱뼃긇긫?밳궋륰긘?긟 궺귪궵귣궋궵 쁝먵롋뼳걁긄깓?깛긊먩맯걂 긐깏긗귽귺 긲귷깛긣?긣깏긊? 궛궯궭귙돫먭봽B2?긻긚긣깏? 긐깏긗귽귺 긲귷깛긣?긣깏긊? 묉3뒱 ?긻긚긣깏?벏뜪붎 FLOWERS -Le volume sur hiver-걁?뺁걂 룊됷뙽믦붎 Harmonia 룊됷뙽믦붎 DESIRE remaster ver. EVE burst error R 룊됷맯럀붎 벫돽긜?깑긓?긥?궓봼궋벦돽둰궻룮뷼귩릯렄믁돿뭷갏긜?깑룮뷼덇뿓궼궞궭귞갃  긓??귽깛긣뚴듂긐긞긛 긓?긑먩뛱붛봽룮뷼 깒긮깄?띍륷궻궟뭾빒깋깛긌깛긐1긳깓긞긓깏?긌긿깋긏??긚깏?긳 먪쀶걭뼔됓 륂뿤審럔 Ver.2긳깓긞긓깏?긐긞긛?뽵믵먛귏궳궇궴7볷2017/08/12뵯봽2띮궑궶궋붯룛궻덄궲궔궫 Memorial걙궺귪궵귣궋궵돿뱻똟 긭깓귽깛븵Ver.갷KADOKAWA룕먒2018/03/돷?뵯봽3딆뫝뫚뎟뿙 ?긦귺깑긫?걏Revolution 걓rei걕걐[DVD븊룊됷뙽믦붦갷OVERLAP RECORD돶뒁2017/03/22뵯봽4HULOTTE SONGS BESTHULOTTE돶뒁2017/06/09뵯봽5긟귽깛긄깛긙긃깑BREAK 밮뙉귕궙귡 뺱궖뼃긇긫?긲깒긚긐긞긛2017/06/돷?뵯봽6긳깓긞긓깏?긌긿깋긏??긚깏?긳 먪쀶걭뼔됓 뮝븧뺽봗 Ver.2긳깓긞긓깏?긐긞긛?뽵믵먛귏궳궇궴7볷2017/08/12뵯봽7뾠룛먰딯 3 Blu-ray Disc긽긢귻귺긲귷긏긣깏?귺긦긽뵯봽귏궳궇궴9볷2017/06/28뵯봽8Z/X -Zillions of enemy X- EX긬긞긏 묉9뭙 긖?갋긤갷긳깓긞긓깏?긐긞긛?뽵믵먛귏궳궇궴17볷2017/08/24뵯봽9딝벍먰럐긊깛?? 밪뙆궻긆깑긲긃깛긛 볭 VOL.08 Blu-ray Disc갷긫깛?귽긮긙깄귺깑귺긦긽뵯봽귏궳궇궴4볷2017/06/23뵯봽10긩?긒??갋긩?깋귽긲 긓깛긵깏?긣?깛긐긚걏NO SONG NO LIFE걐긽긢귻귺긲귷긏긣깏?돶뒁뵯봽귏궳궇궴23볷2017/07/12뵯봽11sin 렦궰궻묈띬 묉덇궻띬 DVD걙룊됷뙽믦붎걚[뭻멗?뽵벫밫갌욼믩뾎롋갋룷몈갷NBC깇긦긫?긖깑갋긄깛??긡귽긽깛긣긙긿긬깛귺긦긽뵯봽귏궳궇궴9볷2017/06/28뵯봽12딝벍먰럐긊깛?? 밪뙆궻긆깑긲긃깛긛 볭 VOL.09 Blu-ray Disc갷긫깛?귽긮긙깄귺깑귺긦긽뵯봽귏궳궇궴4볷2017/06/23뵯봽13?갋?긙긇깑긚긂귻?긣 뺱궖뼃?뫬 160cm?50cm뾭?긞?깛긐깗?깑긤긐긞긛2015/11/30뵯봽14긄깓?깛긊먩맯 1 Blu-ray Disc걙뒶멣맯럀뙽믦붎걚[뙽믦붋벫밫갌귽긹갷귺긦긵깒긞긏긚귺긦긽뵯봽귏궳궇궴9볷2017/06/28뵯봽15릋똼궻땺릐 Season 2 Vol.1 Blu-ray Disc [룊됷벫밫갌갷?긦?긌긿긦긆깛귺긦긽뵯봽귏궳궇궴2볷2017/06/21뵯봽16몥궻붯뺴궻긲긅?깏긛? EXTRA 1 VOCAL걬SOUND COLLECTI갷sprite돶뒁뵯봽귏궳궇궴11볷2017/06/30뵯봽17Re갌CREATORS OP긡??걏gravityWall/sh0ut걐[DVD갷?긦??깄?긙긞긏돶뒁뵯봽귏궳궇궴9볷2017/06/28뵯봽18띮궑궶궋붯룛궻덄궲궔궫 뺱궖뼃긇긫?븊 똟?긞긏긚KADOKAWA긐긞긛?뽵믵먛귏궳궇궴63볷2017/10/?믦19뙳몒룺룛묈먰뼯궠귪귍귪벐벏릐2017/06/17뵯봽20긖긏깋긩럪 ?욼궻륺궻뤵귩븨궎? 뚺렜긮긙깄귺깑귺?긇귽깞몂뾲롊룕먒2017/04/28뵯봽귺긦긽 벫밫븊?귽긣깑                                    궛궯궭귙긳깓긐갋띍륷딯럷궭귗궫궻궓귖귞궢볷딯묉22됷걑궓궸긌긚H 뺱궖뼃긇긫?덇붗붛봽뙂믦갏걒?렅룛뻺뚿귏궿귡벫뢜걙Casket긳깓긐걑뵠깓긐갃걒묉33됷걚걑붯룛궕댶롰뫎궬궯궫뤾뜃?떝궑럔깞귷깛긬귽귺궻듑긣깓쀪뫌뮧떝?걒뼟뒶맟갋긙긿긑갋긲귷귽긣뎘덁뜈50뢂봏딯봑띿뷼 귺긦긽걏DEVILMAN crybaby걐2018봏룊뢶갂Netflix궸궲벲먫멣맊둉뚺둎갏?듒벬궸뱬먶맠뼻걓긖?긇긚긓깋?걕걏D.C.? DreamDays??갋긇????긤깏??긢귽긛걐귽긹깛긣CG뚺둎뭷갏Willplus긓깋?묉250됷?Guilty걑뿸긩렣?됂궻뜈됗땞멏궳遡궠귢귡룉룛궫궭?걒긄깓긘?깛??긮?벫뢜!!긖귽긤긓긨긏긘깈깛걏돘궰궶궕깏긛?걐묉272됷?7뙉23볷둎띊걑긣깋긹깏깛긐갋긆?긊긚긣2017 ?뱧뙳떮?걒?긑긞긣덇붗뵯봽뭷갏뢯뎶롌륃뺪갋쁝뒁딇뛘뿪긓깋?갋븿뚭뛛륷괃TV귺긦긽걏궿궶궞궻?궴걐6뙉16볷뺳몭궻묉11쁞걏귚궘궴궢궘귡궴궢걐?뜍벍됪갋궇귞궥궣걬먩뛱긇긞긣궕뚺둎TV귺긦긽걏긫?긇깛딉먘뮧뜽뒸걐7뙉7볷귝귟뺳몭긚??긣갏?Twitter긌긿깛긻?깛귖렳?뭷PS4붎걑깑긲깋깛궻뭤돷뼽?궴뻷룛긩뿷뭖걒9뙉28볷궸뵯봽갏?뚺렜긖귽긣걬릐??벍됪귩뚺둎륷띿OVA&귽긹깛긣뤵뎕갂TV귺긦긽묉3딖귖뵯?갏?걏깂?긩긚긚긽뚺렜긲귷깛??긡귻깛긐걐귽긹깛긣깒??긣궛궯궭귙긳깓긐갋쁀띦긓?긥?궭귗궫궻궓귖귞궢볷딯묉22됷걑궓궸긌긚H 뺱궖뼃긇긫?덇붗붛봽뙂믦갏걒?렅룛뻺뚿귏궿귡벫뢜걙Casket긳깓긐걑뵠깓긐갃걒묉33됷걚걑붯룛궕댶롰뫎궬궯궫뤾뜃?떝궑럔깞귷깛긬귽귺궻듑긣깓쀪뫌뮧떝?걒뼟뒶맟갋긙긿긑갋긲귷귽긣걓긖?긇긚긓깋?걕걏D.C.? DreamDays??갋긇????긤깏??긢귽긛걐귽긹깛긣CG뚺둎뭷갏Willplus긓깋?묉250됷?Guilty걑뿸긩렣?됂궻뜈됗땞멏궳遡궠귢귡룉룛궫궭?걒긄깓긘?깛??긮?벫뢜!! 긑??귽긖귽긣QR긓?긤 똤뫱궳귖궟뭾빒됀?갏됵덒뱋?궳듗뭁깓긐귽깛갃궓딠똹궸믅붛궳궖귏궥갃긑??귽궳뜺궻QR긓?긤귩벶귒롦귟귺긏긜긚궢궲궘궬궠궋갃걁뤬궢궘궼궞궭귞걂긚??긣긲긅깛긖귽긣QR긓?긤 긚??긣긲긅깛궳귖?뿓됀?궶SP긾?긤붎귩뚺둎뭷궳궥갃뜺궻QR긓?긤귩벶귒롦귟귺긏긜긚궢궲궘궬궠궋갃걁뤬궢궘궼궞궭귞걂 긽?깑?긊긙깛뱋?걅긽?깑?긊긙깛뱋?궼궞궭귞걆믅붛궟뿕뾭뺴뺷 | 궳궣궫귡궛궯궭귙뗤뒁븫 | 룮뷼뛶볺궻뺴뺷 | 뵯봽볷빾뛛궸궰궋궲 | 뙂띙뺴뺷 | 궓벾궚궸궰궋궲 | 긜긌깄깏긡귻? | FAQ 뺷딮궸딈궱궘?렑 | 긘깈긞긯깛긐긇?긣궻뭷릆귩뙥귡 | 됵덒륃뺪빾뛛 | 뛶볺뿗쀰궻랷뤖 ?귽긻?긙 | 긖귽긣먣뼻 | 긖귽긣?긞긵 | 궟뿕뾭뽵듉 | 궓뽦궋뜃귦궧 | 뛎뜍똣띦 | 깏깛긏궸궰궋궲 | 긚?긞긲뺝뢜 | 뙿릐륃뺪뺎뚯뺴릌긫긥?* 깏깛긏긲깏?궳궥갃 ** 뱰긖귽긣궸똣띦궠귢궲궋귡멣궲궻긡긌긚긣갂됪몴뱳궻뼰뭚?띦귩뗕궣귏궥갃겂궞궻긻?긙궻TOP귉갶긣긞긵귉뽣귡갶똤뫱긖귽긣Getchu.com mobile갶?긂깛깓?긤긖귽긣DL.Getchu.com갶귺긲귻깏긄귽긣갶긚?긞긲뺝뢜갶궓뽦궋뜃귦궧갶? Getchu.com 1999-2017");
		printf(result);
		ezt::J2K_FreeMem(result);
	};

	auto ET_GetChu_String2 = []() {
		auto result = ezt::J2K_TranslateMMNT(0, "｜トップへ戻る｜携帯サイトGetchu.com mobile｜ダウンロードサイトDL.Getchu.com｜アフィリエイト｜スタッフ募集｜お問い合わせ｜\n"\
			"© Getchu.com 1999 - 2017"); 
		printf(result);
		ezt::J2K_FreeMem(result);
	};

	auto ET_Overflow_Test = []() {
		auto result = ezt::J2K_TranslateMMNT(0, "asdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfjaasdfasdfajsdhfklajsdlfjaskldfja");
		if (!result) {
			printf("translate failed\n");
			return 0;
		}
	};

	ET_GetChu_String2();
	


	//for (int i = 0; i < 100; i++)
	//{
	//	printf("%03d: ", i);
	//	printf(ezt::J2K_TranslateMMNT(0, "걁긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚깋긞긵긚긡귻긞긏긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵긚긡긞긵갷갷걂"));
	//	//printf(ezt::J2K_TranslateMMNT(0, "귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋귺긏긜긚궢궲궘궬궠궋"));
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
		{ "EH_CreateInstance", &ehnd::EH_CreateInstance }
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
