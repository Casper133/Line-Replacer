#pragma once

#include <windows.h>

#define WIN32_LEAN_AND_MEAN
#define DLL_EXPORT __declspec(dllexport)

DLL_EXPORT void replaceString(const char *originalString, const char *replacementString);
