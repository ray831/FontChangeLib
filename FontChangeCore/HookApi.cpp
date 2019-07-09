#include "stdafx.h"
#include "HookApi.h"

CHAR m_szFontName[LF_FACESIZE] = "\0";
WCHAR w_szFontName[LF_FACESIZE] = L"\0";

CHAR m_szVertFontName[LF_FACESIZE] = "@";
WCHAR w_szVertFontName[LF_FACESIZE] = L"@";

bool CanChangeFontStyle = false;
bool IsUnicode = false;
short FontWeight = 400;
double FontSizeRatio = 1.0;

void WINAPI HookFontInit(FCFONTINFO fi)
{
	StringCchCopyW(w_szFontName, LF_FACESIZE, fi.FontName);
	StringCchCatW(w_szVertFontName, LF_FACESIZE, fi.FontName);

	WideCharToMultiByte(CP_ACP, 0, w_szFontName, -1, m_szFontName, LF_FACESIZE, NULL, 0);
	WideCharToMultiByte(CP_ACP, 0, w_szVertFontName, -1, m_szVertFontName, LF_FACESIZE, NULL, 0);

	if (fi.HookFlag & HOOK_SELECTOBJECT_UNICODE)
		IsUnicode = true;

	if (CanChangeFontStyle = fi.CanChangeFontStyle) {
		FontWeight = fi.FontWeight;
		FontSizeRatio = 1.0 + (fi.FontSizeRatio / 100.0);
	}
	
}

void WINAPI ChangeFontStyle(int& height, int& width, int& weight)
{
	height *= FontSizeRatio;
	width  *= 0;
	weight = FontWeight;
}

void WINAPI ChangeFontStyle(long& height, long& width, long& weight)
{
	height *= FontSizeRatio;
	width  *= 0;
	weight = FontWeight;
}


HFONT WINAPI NewCreateFontA(
	_In_ int     nHeight,
	_In_ int     nWidth,
	_In_ int     nEscapement,
	_In_ int     nOrientation,
	_In_ int     fnWeight,
	_In_ DWORD   fdwItalic,
	_In_ DWORD   fdwUnderline,
	_In_ DWORD   fdwStrikeOut,
	_In_ DWORD   fdwCharSet,
	_In_ DWORD   fdwOutputPrecision,
	_In_ DWORD   fdwClipPrecision,
	_In_ DWORD   fdwQuality,
	_In_ DWORD   fdwPitchAndFamily,
	_In_ LPCSTR  lpszFace
)
{
	if (CanChangeFontStyle) {
		ChangeFontStyle(nHeight, nWidth, fnWeight);
	}

	LPCSTR pstr = (lpszFace[0] != '@') ? m_szFontName : m_szVertFontName;

	return CreateFontA(nHeight, nWidth, nEscapement, nOrientation, fnWeight, fdwItalic, fdwUnderline, fdwStrikeOut, fdwCharSet,
		fdwOutputPrecision, fdwClipPrecision, fdwQuality, fdwPitchAndFamily, pstr);
}


HFONT WINAPI NewCreateFontIndirectA(LOGFONTA *lplf)
{
	if(lplf->lfFaceName[0] != '@')
		StringCchCopyA(lplf->lfFaceName, LF_FACESIZE, m_szFontName);
	else
		StringCchCopyA(lplf->lfFaceName, LF_FACESIZE, m_szVertFontName);

	if (CanChangeFontStyle) {
		ChangeFontStyle(lplf->lfHeight, lplf->lfWidth, lplf->lfWeight);
	}

	return CreateFontIndirectA(lplf);
}

// #######################################

HFONT WINAPI NewCreateFontW(
	_In_ int     nHeight,
	_In_ int     nWidth,
	_In_ int     nEscapement,
	_In_ int     nOrientation,
	_In_ int     fnWeight,
	_In_ DWORD   fdwItalic,
	_In_ DWORD   fdwUnderline,
	_In_ DWORD   fdwStrikeOut,
	_In_ DWORD   fdwCharSet,
	_In_ DWORD   fdwOutputPrecision,
	_In_ DWORD   fdwClipPrecision,
	_In_ DWORD   fdwQuality,
	_In_ DWORD   fdwPitchAndFamily,
	_In_ LPCWSTR lpszFace
)
{
	if (CanChangeFontStyle) {
		ChangeFontStyle(nHeight, nWidth, fnWeight);
	}

	LPCWSTR pwstr = (lpszFace[0] != L'@') ? w_szFontName : w_szVertFontName;

	return CreateFontW(nHeight, nWidth, nEscapement, nOrientation, fnWeight, fdwItalic, fdwUnderline, fdwStrikeOut, fdwCharSet,
		fdwOutputPrecision, fdwClipPrecision, fdwQuality, fdwPitchAndFamily, pwstr);
}


HFONT WINAPI NewCreateFontIndirectW(LOGFONTW *lplf)
{
	if (lplf->lfFaceName[0] != L'@')
		StringCchCopyW(lplf->lfFaceName, LF_FACESIZE, w_szFontName);
	else
		StringCchCopyW(lplf->lfFaceName, LF_FACESIZE, w_szVertFontName);

	if (CanChangeFontStyle) {
		ChangeFontStyle(lplf->lfHeight, lplf->lfWidth, lplf->lfWeight);
	}

	return CreateFontIndirectW(lplf);
}

HOOK_TRACE_INFO htCreateFontA = { NULL };
HOOK_TRACE_INFO htCreateFontW = { NULL };
HOOK_TRACE_INFO htCreateFontIndirectA = { NULL };
HOOK_TRACE_INFO htCreateFontIndirectW = { NULL };

ULONG			CreateFontA_ACLEntries[1] = { 0 };
ULONG			CreateFontW_ACLEntries[1] = { 0 };
ULONG			CreateFontIndirectA_ACLEntries[1] = { 0 };
ULONG			CreateFontIndirectW_ACLEntries[1] = { 0 };

NTSTATUS WINAPI HookCreateFont()
{
	if ( SUCCEEDED(LhInstallHook(
			GetProcAddress(GetModuleHandleA("GDI32"), "CreateFontA"),
			NewCreateFontA,
			NULL,
			&htCreateFontA)))
		LhSetExclusiveACL(CreateFontA_ACLEntries, 1, &htCreateFontA);

	if ( SUCCEEDED(LhInstallHook(
			GetProcAddress(GetModuleHandleA("GDI32"), "CreateFontW"),
			NewCreateFontW,
			NULL,
			&htCreateFontW)))
		LhSetExclusiveACL(CreateFontW_ACLEntries, 1, &htCreateFontW);

	if ( SUCCEEDED(LhInstallHook(
			GetProcAddress(GetModuleHandleA("GDI32"), "CreateFontIndirectA"),
			NewCreateFontIndirectA,
			NULL,
			&htCreateFontIndirectA)))
		LhSetExclusiveACL(CreateFontIndirectA_ACLEntries, 1, &htCreateFontIndirectA);

	if ( SUCCEEDED(LhInstallHook(
			GetProcAddress(GetModuleHandleA("GDI32"), "CreateFontIndirectW"),
			NewCreateFontIndirectW,
			NULL,
			&htCreateFontIndirectW)))
		LhSetExclusiveACL(CreateFontIndirectW_ACLEntries, 1, &htCreateFontIndirectW);

	return 0;
}



ud_map_hf HFontTable;

unsigned WINAPI DeleteOldFontThreadProc(PVOID lpParam)
{
	ud_map_hf::iterator iter = HFontTable.begin();

	while (iter != HFontTable.end())
	{
		if (GetObjectType(iter->first) == FALSE) {
			DeleteObject(iter->second);
			iter = HFontTable.erase(iter);
		}
		else if (GetObjectType(iter->second) == FALSE) {
			DeleteObject(iter->first);
			iter = HFontTable.erase(iter);
		}

		else iter++;
	}

	return 0;
}

HFONT WINAPI CreateNewFontByHFONT(HFONT hfont)
{
	if (!(HFontTable.size() % 128)) {
		HANDLE hdf = (HANDLE)_beginthreadex(NULL, 0, &DeleteOldFontThreadProc, NULL, 0, NULL);
		WaitForSingleObject(hdf, INFINITE);
		CloseHandle(hdf);
	}

	HFONT newFont = hfont;

	if (!IsUnicode) {
		LOGFONTA lf;
		ZeroMemory(&lf, sizeof(LOGFONTA));

		GetObjectA(hfont, sizeof(LOGFONTA), &lf);
		if ((_stricmp(lf.lfFaceName, "System") == 0) ||
			(_stricmp(lf.lfFaceName, "Microsoft JhengHei UI") == 0))
			return hfont;

		if (lf.lfFaceName[0] == '@') StringCchCopyA(lf.lfFaceName, LF_FACESIZE, m_szVertFontName);
		else StringCchCopyA(lf.lfFaceName, LF_FACESIZE, m_szFontName);

		
		if ( !(newFont = CreateFontIndirectA(&lf)) )
			newFont = hfont;
		else
			HFontTable.insert(std::pair<HFONT, HFONT>(hfont, newFont));
	}
	else {
		LOGFONTW lf;
		ZeroMemory(&lf, sizeof(LOGFONTW));

		GetObjectW(hfont, sizeof(LOGFONTW), &lf);
		if ((_wcsicmp(lf.lfFaceName, L"System") == 0) ||
			(_wcsicmp(lf.lfFaceName, L"Microsoft JhengHei UI") == 0))
			return hfont;

		if (lf.lfFaceName[0] == L'@') StringCchCopyW(lf.lfFaceName, LF_FACESIZE, w_szVertFontName);
		else StringCchCopyW(lf.lfFaceName, LF_FACESIZE, w_szFontName);


		if ( !(newFont = CreateFontIndirectW(&lf)) )
			newFont = hfont;
		else
			HFontTable.insert(std::pair<HFONT, HFONT>(hfont, newFont));
	}
	

	return newFont;
}

HGDIOBJ WINAPI NewSelectObject(
	_In_ HDC     hdc,
	_In_ HGDIOBJ hgdiobj)
{
	if (GetObjectType(hgdiobj) == OBJ_FONT)
	{
		ud_map_hf::iterator iter = HFontTable.find((HFONT)hgdiobj);

		HFONT newFont = (iter != HFontTable.end()) ? iter->second
			: CreateNewFontByHFONT((HFONT)hgdiobj);


		hgdiobj = newFont;
	}

	return SelectObject(hdc, hgdiobj);
}

HOOK_TRACE_INFO htSelectObject = { NULL };
ULONG			SelectObject_ACLEntries[1] = { 0 };

NTSTATUS WINAPI HookSelectObject()
{
	if (SUCCEEDED(LhInstallHook(
			GetProcAddress(GetModuleHandleA("GDI32"), "SelectObject"),
			NewSelectObject,
			NULL,
			&htSelectObject)))
		LhSetExclusiveACL(SelectObject_ACLEntries, 1, &htSelectObject);

	return 0;
}