#include "line-replacer-library.h"

void replaceString(const char *originalString, const char *replacementString)
{
	HANDLE currentProcessHandle = GetCurrentProcess();

	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);
	MEMORY_BASIC_INFORMATION memoryInformation{};

	int originalStringLength = strlen(originalString);
	int replacementStringLength = strlen(replacementString);

	for (char *baseAddress = (char *) systemInfo.lpMinimumApplicationAddress;
		baseAddress <= systemInfo.lpMaximumApplicationAddress;
		baseAddress += memoryInformation.RegionSize) 
	{
		if (!VirtualQueryEx(currentProcessHandle, baseAddress, &memoryInformation, sizeof(memoryInformation))) 
		{
			continue;
		}

		if (!((memoryInformation.State == MEM_COMMIT) && (memoryInformation.AllocationProtect == PAGE_READWRITE))) 
		{
			continue;
		}

		char *memoryData = new char[memoryInformation.RegionSize];
		
		if (memoryData == NULL) 
		{
			continue;
		}

		ZeroMemory(memoryData, memoryInformation.RegionSize);

		SIZE_T numberOfReadBytes = 0;
		baseAddress = (char *) memoryInformation.BaseAddress;
		
		if (!ReadProcessMemory(currentProcessHandle, baseAddress, memoryData, memoryInformation.RegionSize, &numberOfReadBytes)) 
		{
			delete[] memoryData;
			continue;
		}

		for (int memoryShift = 0; memoryShift < (numberOfReadBytes - originalStringLength); memoryShift++)
		{
			if (memcmp(originalString, &memoryData[memoryShift], originalStringLength) == 0)
			{
				char *startStringReference = baseAddress + memoryShift;
				
				for (int j = 0; j < replacementStringLength; j++) 
				{
					startStringReference[j] = replacementString[j];
				}
				
				startStringReference[replacementStringLength] = '\0';
			}
		}

		delete[] memoryData;
	}
}
