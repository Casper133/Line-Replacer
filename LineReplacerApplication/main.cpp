#include "main.h"

#define ORIGINAL_STRING "OriginalString"
#define REPLACEMENT_STRING "Qwerty"

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
		performThreadInjection(string);
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

void performThreadInjection(char originalString[])
{
    // TODO
}
