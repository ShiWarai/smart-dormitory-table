#ifndef SCREENKEYBOARDPARENT_HPP
#define SCREENKEYBOARDPARENT_HPP
#include "../../../../../Core/Inc/InputsCollection.h"

class ScreenKeyboardParent
{
public:
	virtual void showKeyboardCallback() {};
	virtual void hideOkKeyboardCallback() {};
	virtual void hideCancelKeyboardCallback() {};
};

#endif