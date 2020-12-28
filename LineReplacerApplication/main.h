#pragma once

#include <iostream>
#include "line-replacer-library.h"

void performStaticImport(char originalString[]);

void performDynamicImport(char originalString[]);

void performThreadInjection();
