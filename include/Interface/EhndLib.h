#pragma once
#include "Ehnd.h"
#include <string>
#include <Windows.h>

using EH_CREATEINSTANCE = IEhnd*(cdecl*)(void);

class EhndLib : public IEhnd
{
public:
	EhndLib()
	{

	}
	virtual ~EhndLib()
	{
		Release();
	}

	EHNDERR Create(LPCSTR szDLLPath)
	{
		std::string DLLPath = szDLLPath;

		// wszDLLPath가 절대경로가 아니다면 절대경로로 만들어준다
		// Working Directory의 DLL이 불리는것을 방지하기 위함
		if (strstr(szDLLPath, ":") == NULL)
			DLLPath = GetCurrentPathA() + szDLLPath;

		m_hDLL = LoadLibraryA(DLLPath.c_str());
		if (m_hDLL == NULL)
		{
			printf("Ehnd Load DLL '%s' Failed.\n", DLLPath.c_str());
			ASSERT(0);
			return EHNDERR_LOADLIBRARY_FAILED;
		}

		m_pCreateInstance = (EH_CREATEINSTANCE)(GetProcAddress(m_hDLL, "EH_CreateInstance"));

		if (!m_pCreateInstance)
		{
			printf("GetProcAddress Failed\n");
			ASSERT(0);
			return EHNDERR_GETPROCADDRESS_FAILED;
		}

		m_pEhnd = m_pCreateInstance();
		printf("Success\n");
		return EHNDERR_NOERR;
	}

	EH_METHOD(void) Release()
	{
		m_pEhnd->Release();
		FreeLibrary(m_hDLL);
	}
	EH_METHOD(UINT32) GetVersion() const
	{
		return m_pEhnd->GetVersion();
	}
	EH_METHOD(EHNDERR) GetLastError() const
	{
		return m_pEhnd->GetLastError();
	}
	EH_METHOD(BOOL32) Open(EHND_ENGINE engine, EHND_TL_LANG srcLang = EHND_TL_LANG_UNKNOWN, EHND_TL_LANG destLang = EHND_TL_LANG_UNKNOWN)
	{
		return m_pEhnd->Open(engine, srcLang, destLang);
	}
	EH_METHOD(BOOL32) TranslateText(LPCSTR srcText, char **outText)
	{
		return m_pEhnd->TranslateText(srcText, outText);
	}
	EH_METHOD(BOOL32) TranslateText(LPCWSTR srcText, WCHAR **outText)
	{
		return m_pEhnd->TranslateText(srcText, outText);
	}
	EH_METHOD(BOOL32) SendEngineMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		return m_pEhnd->SendEngineMessage(Message, wParam, lParam);
	}

private:
	HMODULE m_hDLL = NULL;
	IEhnd *m_pEhnd = NULL;
	EH_CREATEINSTANCE m_pCreateInstance = NULL;

private:
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

};
