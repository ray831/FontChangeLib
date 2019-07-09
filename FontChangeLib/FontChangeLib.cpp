#include "FontChangeLib.h"

NTSTATUS WINAPI CreateFontChange(_Out_ LPWSTR fcpath)
{
	PWSTR dllpath = new WCHAR[MAX_PATH];

	GetTempPathW(MAX_PATH * sizeof(WCHAR), dllpath);

	WCHAR szHash[20];
	StringCchPrintfW( szHash, 20, L"%x", XXH32( FontChangeDLL, ARRAYSIZE(FontChangeDLL), 0) );
	StringCchCatW( dllpath, MAX_PATH, szHash );

	if (GetFileAttributes(dllpath) != INVALID_FILE_ATTRIBUTES)
		return FC_FILE_EXIST;

	char* buf = new char[orignalSize];
	if (FAILED(LZ4_decompress_safe(FontChangeDLL, buf, ARRAYSIZE(FontChangeDLL), orignalSize)))
		return FC_DECOMPRESS_FAILED;

	HANDLE hfile = CreateFileW(
		dllpath,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_HIDDEN,
		NULL
	);

	DWORD dwWritten = 0;
	WriteFile(hfile, buf, orignalSize, &dwWritten, NULL);
	CloseHandle(hfile);

	delete[] buf;

	if (dwWritten != orignalSize)
		return FC_FILE_WRITE_FAILED;
	
	fcpath = dllpath;
}

DWORD WINAPI LoadFontChange(_In_ LPWSTR fcpath, _In_ DWORD PID, _In_ FCFONTINFO fi)
{
	NTSTATUS nt = RhInjectLibrary(
		PID,
		0,           // ThreadId to wake up upon injection
		EASYHOOK_INJECT_DEFAULT,
		fcpath, // 32-bit
		NULL,		 // 64-bit not provided
		&fi, // data to send to injected DLL entry point
		sizeof(FCFONTINFO)// size of data to send
	);


	return nt;
}