// FontChangeCore.cpp : �w�q DLL ���ε{�����ץX�禡�C
//

#include "stdafx.h"

#include "HookApi.h"

EXTERN_C
__declspec(dllexport)
void WINAPI NativeInjectionEntryPoint(REMOTE_ENTRY_INFO* inRemoteInfo)
{
	FCFONTINFO fi = { 0 };
	memcpy_s(&fi, sizeof(FCFONTINFO), inRemoteInfo->UserData, inRemoteInfo->UserDataSize);

	HookFontInit(fi);

	if (fi.HookFlag & HOOK_CREATEFONT)
		HookCreateFont();
	else
		HookSelectObject();
}