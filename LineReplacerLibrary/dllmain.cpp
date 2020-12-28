// dllmain.cpp : Определяет точку входа для приложения DLL.
//#include "framework.h"
#include "line-replacer-library.h"

char originalString[] = "OriginalString";
char replacementString[] = "Qwerty_____";

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		replaceString(originalString, replacementString);
		break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}