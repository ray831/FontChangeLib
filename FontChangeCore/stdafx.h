// stdafx.h : 可在此標頭檔中包含標準的系統 Include 檔，
// 或是經常使用卻很少變更的
// 專案專用 Include 檔案
//

#pragma once

//#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 從 Windows 標頭排除不常使用的成員
// Windows 標頭檔: 
//#include <windows.h>



// TODO:  在此參考您的程式所需要的其他標頭
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

#include <strsafe.h>
#include <process.h>

#include <unordered_map>
typedef std::unordered_map<HFONT, HFONT> ud_map_hf;