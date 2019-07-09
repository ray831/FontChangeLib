#pragma once

#ifndef _FONTCHANGESTRUCT_H_
#define _FONTCHANGESTRUCT_H_


/* FontChange Injected Function */
#define HOOK_CREATEFONT				1
#define HOOK_SELECTOBJECT_ANSI		2
#define HOOK_SELECTOBJECT_UNICODE	4


typedef struct _FCFONTINFO {
	BYTE	HookFlag;
	WCHAR	FontName[LF_FACESIZE];
	BOOLEAN	CanChangeFontStyle;
	UINT16	FontWeight;
	UINT16	FontSizeRatio;
}FCFONTINFO, *PFCFONTINFO;


#endif