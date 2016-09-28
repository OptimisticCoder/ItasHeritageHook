#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <Psapi.h>
#include <stdlib.h>
#include "ItasHeritageHook.h"

#pragma message("library is linking with \"Psapi.lib\"")
#pragma comment(lib, "Psapi.lib")

typedef struct
{
	HHOOK     g_hHook;
	HWND      g_hWnd;
	HINSTANCE g_hInstance;
} SCGLOBALDATA;

HANDLE hMappedFile;  
SCGLOBALDATA* pData; 
bool bStartingProcess = false;

BOOL WINAPI DllMain(HINSTANCE hInst, ULONG uReason, LPVOID lpReserved)
{
	switch (uReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		char  szBaseName[_MAX_FNAME] = "\0",
			szTmp[_MAX_FNAME];

		if (GetModuleBaseNameA(GetCurrentProcess(), hInst, szTmp, sizeof(szTmp)))
			_splitpath(szTmp, NULL, NULL, szBaseName, NULL);

		strcat(szBaseName, "RCMSharedMemMMF");

		hMappedFile = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(SCGLOBALDATA), szBaseName);
		pData = (SCGLOBALDATA*)MapViewOfFile(hMappedFile, FILE_MAP_WRITE, 0, 0, 0);
		bStartingProcess = (hMappedFile != NULL) && (GetLastError() != ERROR_ALREADY_EXISTS);

		if (bStartingProcess)
		{
			pData->g_hInstance = hInst;
			pData->g_hWnd = NULL;      
			pData->g_hHook = NULL;
		}

		DisableThreadLibraryCalls(hInst);
	}
	break;

	case DLL_PROCESS_DETACH:
		CloseHandle(hMappedFile);
		break;
	}

	return TRUE;
}

ITASHERITAGEHOOK_API void StartHook(HWND hWnd)
{
	if (bStartingProcess)
	{
		pData->g_hWnd = hWnd;
		pData->g_hHook = SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)GetMsgProc, pData->g_hInstance, 0);
	}
}

LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)
		return CallNextHookEx(pData->g_hHook, nCode, wParam, lParam);

	std::string wParamStr = "PM_NOREMOVE";
	if (wParam == 1)
		wParamStr = "PM_REMOVE";

	MSG* msg = (MSG*)lParam;

	// the message identifier is in msg.message as an unsigned integer.
	// https://wiki.winehq.org/List_Of_Windows_Messages

	FILE* file = fopen("wndProc.log", "a");
	std::string log = CItasHeritageHook::currentDateTime();
	log = log.append(": ").append(wParamStr).append(" - ").append(std::to_string(msg->message)).append("\r\n");

	fprintf(file, log.c_str());
	fclose(file);

	return CallNextHookEx(pData->g_hHook, nCode, wParam, lParam);
}

const std::string CItasHeritageHook::currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

