#pragma once

#include <gui/common/FrontendApplication.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Unicode.hpp>

enum INPUTS {
	PIN_CODE = T_PINCODEINPUT,
};

#define COUNT_INPUTS 1
#define MAX_INPUT 18

struct InputsController {
	char inputBuffer[MAX_INPUT];
	unsigned short selectedInput = -1;
};