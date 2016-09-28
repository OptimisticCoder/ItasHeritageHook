#ifdef ITASHERITAGEHOOK_EXPORTS
#define ITASHERITAGEHOOK_API  __declspec(dllexport)
#else
#define ITASHERITAGEHOOK_API __declspec(dllimport)
#endif

class ITASHERITAGEHOOK_API CItasHeritageHook {
public:
	CItasHeritageHook(void);
	
	const static std::string CItasHeritageHook::currentDateTime();
};

extern "C" ITASHERITAGEHOOK_API void StartHook(HWND hWnd);
extern "C" LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam);
