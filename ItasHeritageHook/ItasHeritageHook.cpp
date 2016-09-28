#include "stdafx.h"
#include "ItasHeritageHook.h"

HHOOK _hhook = NULL;

ITASHERITAGEHOOK_API int StartHooking(void)
{
	_hhook = SetWindowsHookEx(
		WH_GETMESSAGE,
		GetMsgProc,
		(HINSTANCE)NULL, GetCurrentThreadId());
	return 0;
}

LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	//switch (nCode)
	//{
	//	case 
	//}

	return CallNextHookEx(_hhook, nCode, wParam, lParam);
}

// This is the constructor of a class that has been exported.
// see ItasHeritageHook.h for the class definition
CItasHeritageHook::CItasHeritageHook()
{
	return;
}
