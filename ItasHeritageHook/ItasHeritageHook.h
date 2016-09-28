// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ITASHERITAGEHOOK_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ITASHERITAGEHOOK_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef ITASHERITAGEHOOK_EXPORTS
#define ITASHERITAGEHOOK_API __declspec(dllexport)
#else
#define ITASHERITAGEHOOK_API __declspec(dllimport)
#endif

// This class is exported from the ItasHeritageHook.dll
class ITASHERITAGEHOOK_API CItasHeritageHook {
public:
	CItasHeritageHook(void);
	// TODO: add your methods here.
};

extern ITASHERITAGEHOOK_API int nItasHeritageHook;

ITASHERITAGEHOOK_API int fnItasHeritageHook(void);
