#include "main.h"

#define DLL_NAME "LineReplacerLibrary.dll"
#define DLL_PROC_NAME "replaceString"

// DLL_PROC is a pointer type
// DLL_PROC points to function with signature: void funcName(const char*, const char*)
typedef void(__cdecl* DLL_PROC)(const char*, const char*);

using namespace std;

int main()
{
    char string[] = ORIGINAL_STRING;

	int action = 0;

	cout << "1. Static import" << endl <<
		"2. Dynamic import" << endl <<
		"3. Thread injection" << endl <<
		"0. Exit" << endl <<
		"Choose action: ";

	cin >> action;

	switch (action)
	{
	case 1:
		performStaticImport(string);
		break;
	case 2:
		performDynamicImport(string);
		break;
	case 3:
		performThreadInjection();
		break;
	default:
		return 0;
		break;
	}

    cout << endl << "Original: " << ORIGINAL_STRING << endl << "Replaced: " << string << endl;

	return 0;
}

void performStaticImport(char originalString[])
{
    replaceString(originalString, REPLACEMENT_STRING);
}

void performDynamicImport(char originalString[])
{

	HMODULE hLibrary;					// Library descriptor
	DLL_PROC ProcAddr;					// Pointer to a fucntion
	BOOL runTimeLinkSuccessful = FALSE;

	hLibrary = LoadLibrary(TEXT(DLL_NAME));
    
	// Get function address if library was loaded
	if (hLibrary != NULL)
	{
		ProcAddr = (DLL_PROC)GetProcAddress(hLibrary, DLL_PROC_NAME);

		if (NULL != ProcAddr)
		{	
			runTimeLinkSuccessful = TRUE;
			(ProcAddr)(originalString, REPLACEMENT_STRING);
		}
	}
	if (!runTimeLinkSuccessful) { cout << "Run Time Linking Failled."; }
}

void performThreadInjection()
{
	DWORD pid = GetCurrentProcessId();
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	if (hProcess == INVALID_HANDLE_VALUE) {
		return;
	}

	void* loc = VirtualAllocEx(hProcess, NULL, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	if (!loc) {
		return;
	}

	WriteProcessMemory(hProcess, loc, DLL_NAME, strlen(DLL_NAME) + 1, 0);

	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, loc, 0, 0);

	if (hThread) {
		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);
	}

	if (hProcess) {
		CloseHandle(hProcess);
	}
}
