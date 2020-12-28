#pragma once

#include <windows.h>

#define WIN32_LEAN_AND_MEAN
#define DLL_EXPORT __declspec(dllexport)
#define ORIGINAL_STRING "OriginalString"
#define REPLACEMENT_STRING "Qwerty"

extern "C" DLL_EXPORT void replaceString(const char *originalString, const char *replacementString);
