// stdafx.h : �i�b�����Y�ɤ��]�t�зǪ��t�� Include �ɡA
// �άO�g�`�ϥΫo�ܤ��ܧ�
// �M�ױM�� Include �ɮ�
//

#pragma once

//#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �q Windows ���Y�ư����`�ϥΪ�����
// Windows ���Y��: 
//#include <windows.h>



// TODO:  �b���Ѧұz���{���һݭn����L���Y
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