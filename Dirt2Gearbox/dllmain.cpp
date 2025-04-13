#include "version/version.h"
#include <gearbox.h>

BOOL APIENTRY DllMain( HMODULE hModule,
					   DWORD  ul_reason_for_call,
					   LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		setupWrappers();
		char exePath[MAX_PATH + 1];
		uint32_t exeNameLength = GetModuleFileNameA(NULL, exePath, MAX_PATH + 1);
		bool isGameExe = strncmp(exePath + exeNameLength - Dirt::exeNameLength, "dirt2_game.exe", Dirt::exeNameLength) == 0;
		if (isGameExe)
			Dirt::Get().OnProcessAttach();
		break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
