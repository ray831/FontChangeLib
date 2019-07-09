#pragma once

#ifndef _FONTCHANGELIB_H_
#define _FONTCHANGELIB_H_

#pragma warning(disable:4099)

#define FC_FILE_EXIST 9000
#define FC_DECOMPRESS_FAILED 9001
#define FC_FILE_WRITE_FAILED 9002

#include "FontChangeBIN.h"

#include <Windows.h>

#include <strsafe.h>
#include <xxhash.h>
#include <lz4hc.h>
#include <easyhook.h>

#include <fontchangestruct.h>

#if _M_X64
#pragma comment(lib, "EasyHook64.lib")
#pragma comment(lib, "AUX_ULIB_x64.lib")
#else
#pragma comment(lib, "EasyHook32.lib")
#pragma comment(lib, "AUX_ULIB_x86.lib")
#endif

#pragma comment(lib, "psapi.lib")

#pragma comment(lib, "lz4_static.lib")
#pragma comment(lib, "xxhash.lib")

#ifdef __cplusplus
EXTERN_C { 
#endif

	DWORD WINAPI LoadFontChange(_In_ LPWSTR fcpath, _In_ DWORD PID, _In_ FCFONTINFO fi);
	NTSTATUS WINAPI CreateFontChange(_Out_ LPWSTR fcpath);

#ifdef __cplusplus
}
#endif


#endif