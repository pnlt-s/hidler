#include <Windows.h>

BOOL WINAPI DllMain(
	HINSTANCE hInstDLL, 
	DWORD fdwReason, 
	LPVOID lpvReserved )
{
	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH: {
			auto proc = GetCurrentProcessId();
			EnumWindows([](HWND hWnd, LPARAM lParam) {
				DWORD pidOR;
				auto goven = GetWindowThreadProcessId(hWnd, &pidOR);
				if (pidOR == lParam)
				{
					SetWindowDisplayAffinity(hWnd, WDA_EXCLUDEFROMCAPTURE);
				}
				return TRUE;
				}, proc);
			break;
		}
		case DLL_PROCESS_DETACH: {
			auto proc = GetCurrentProcessId();
			EnumWindows([](HWND hWnd, LPARAM lParam) {
				DWORD pidOR;
				auto goven = GetWindowThreadProcessId(hWnd, &pidOR);
				if (pidOR == lParam)
				{
					SetWindowDisplayAffinity(hWnd, WDA_NONE);
				}
				return TRUE;
				}, proc);
			break;
		}
	}

	return TRUE;
}