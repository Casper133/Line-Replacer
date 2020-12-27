#include "main.h"

#define ORIGINAL_STRING "OriginalString"
#define REPLACEMENT_STRING "Qwerty"

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
    // TODO
}

void performThreadInjection(char originalString[])
{
    // TODO
}
