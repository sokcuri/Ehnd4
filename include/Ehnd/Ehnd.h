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

#include "../../include/Interface/Ehnd.h"
#include "../../include/Interface/TLEngine.h"

#include "../../include/TLEngine/TLEngine_EZT_J2K.h"

class CEhnd : public IEhnd
{
public:
	CEhnd()
		: m_srcLang(EHND_TL_LANG_UNKNOWN), m_destLang(EHND_TL_LANG_UNKNOWN)
			, m_outTextA(0), m_outTextW(0)
			, m_lastErr(EHNDERR_NOERR)
			, m_transEngine(NULL)
	{
		
	}

	EH_METHOD(void) Release()
	{
		delete this;
	}

	EH_METHOD(UINT32) GetVersion() const
	{
		return EHND_VERSION;
	}

	EH_METHOD(EHNDERR) GetLastError() const
	{
		return m_lastErr;
	}

	EH_METHOD(BOOL32) Open(EHND_ENGINE engine, EHND_TL_LANG srcLang, EHND_TL_LANG destLang)
	{
		if (_GetEngineType() != EHND_ENGINE_NULL)
		{
			_SetLastError(EHNDERR_ALREADY_ENGINE_OPENED);
			return false;
		}

		switch (engine)
		{
			case EHND_ENGINE_EZT_J2K:
			{
				m_destLang = EHND_TL_LANG_JAPANESE;
				m_srcLang = EHND_TL_LANG_KOREAN;
			}
			break;

			case EHND_ENGINE_EZT_K2J: // not implemented
			{
				m_destLang = EHND_TL_LANG_KOREAN;
				m_srcLang = EHND_TL_LANG_JAPANESE;
				_SetLastError(EHNDERR_NOT_IMPL);
				return false;
			}
			break;

			default:
			{
				_SetLastError(EHNDERR_NOT_SUPPORTED_TLENGINE);
				return false;
			}
		}

		m_transEngine = new TLEngine_EZT_J2K();
		if (!m_transEngine->Init())
		{
			_SetLastError(m_transEngine->GetLastError());
			m_transEngine->Release();
			m_transEngine = NULL;
			return false;
		}
		else
		{
			_SetLastError(EHNDERR_NOERR);
		}

		return true;
	}

	EH_METHOD(BOOL32) Close()
	{
		delete m_transEngine;

		// uninitialize variable
		m_transEngine = NULL;
		m_srcLang = m_destLang = EHND_TL_LANG_UNKNOWN;

		_SetLastError(EHNDERR_NOERR);
		return true;
	}

	EH_METHOD(BOOL32) TranslateText(LPCSTR srcText, CHAR **outText)
	{
		if (_GetEngineType() == EHND_ENGINE_NULL)
		{
			_SetLastError(EHNDERR_REQUIRE_ENGINE_OPEN);
			return false;
		}

		if (m_outTextA)
		{
			delete[] m_outTextA;
		}

		m_transEngine->TranslateText(srcText, outText);

		m_outTextA = *outText;
		_SetLastError(m_transEngine->GetLastError());
		return true;
		
	}
	EH_METHOD(BOOL32) TranslateText(LPCWSTR srcText, WCHAR **outText)
	{
		if (_GetEngineType() == EHND_ENGINE_NULL)
		{
			_SetLastError(EHNDERR_REQUIRE_ENGINE_OPEN);
			return false;
		}

		if (m_outTextW)
		{
			delete[] m_outTextW;
		}

		m_transEngine->TranslateText(srcText, outText);

		m_outTextW = *outText;
		_SetLastError(m_transEngine->GetLastError());
		return true;
	}
	EH_METHOD(BOOL32) SendEngineMessage(UINT Message, WPARAM wParam, LPARAM lParam)
	{
		if (_GetEngineType() == EHND_ENGINE_NULL)
		{
			_SetLastError(EHNDERR_REQUIRE_ENGINE_OPEN);
			return false;
		}

		m_transEngine->SendEngineMessage(Message, wParam, lParam);
		_SetLastError(m_transEngine->GetLastError());
		return true;
	}

private:
	char *_SetOutText(char *outText)
	{
		if (m_outTextA)
		{
			delete[] m_outTextA;
		}
		m_outTextA = new char[strlen(outText) + 1];
		strcpy(m_outTextA, outText);
		return m_outTextA;
	}
	WCHAR *_SetOutText(WCHAR *outText)
	{
		if (m_outTextW)
		{
			delete[] m_outTextW;
		}
		m_outTextW = new WCHAR[wcslen(outText) + 1];
		wcscpy(m_outTextW, outText);
		return m_outTextW;
	}

	void _SetLastError(EHNDERR error)
	{
		m_lastErr = error;
	}

	EHND_ENGINE _GetEngineType() const
	{
		if (m_transEngine)
			return m_transEngine->GetEngineType();
		return EHND_ENGINE_NULL;
	}

private:
	TLEngine *m_transEngine;
	EHND_TL_LANG m_srcLang;
	EHND_TL_LANG m_destLang;

	char *m_outTextA;
	WCHAR *m_outTextW;

	EHNDERR m_lastErr;
};

bool EH_UpdateCheck();
bool EH_InitLua();
bool EH_UninitLua();
//bool EH_InstallHook(char *libPath);
//bool EH_UninstallHook();