#pragma once

#ifndef _HOOKAPI_H_
#define _HOOKAPI_H_

#include "stdafx.h"


// ANSI
// Hook CreateFontA
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
);


// Hook CreateFontIndirectA
HFONT WINAPI NewCreateFontIndirectA(LOGFONTA *lplf);


// UNICODE
// Hook CreateFontW
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
);


// Hook CreateFontIndirectW
HFONT WINAPI NewCreateFontIndirectW(LOGFONTW *lplf);


// #######################################
// Hook SelectObject
HGDIOBJ WINAPI NewSelectObject(
	_In_ HDC     hdc,
	_In_ HGDIOBJ hgdiobj);


// #######################################

void WINAPI HookFontInit(FCFONTINFO fi);

NTSTATUS WINAPI HookCreateFont();
NTSTATUS WINAPI HookSelectObject();


#endif