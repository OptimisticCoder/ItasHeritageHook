// ItasHeritageHook.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ItasHeritageHook.h"


// This is an example of an exported variable
ITASHERITAGEHOOK_API int nItasHeritageHook=0;

// This is an example of an exported function.
ITASHERITAGEHOOK_API int fnItasHeritageHook(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see ItasHeritageHook.h for the class definition
CItasHeritageHook::CItasHeritageHook()
{
	return;
}
