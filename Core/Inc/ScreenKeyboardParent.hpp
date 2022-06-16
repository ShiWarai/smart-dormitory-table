#ifndef SCREENKEYBOARDPARENT_HPP
#define SCREENKEYBOARDPARENT_HPP

class ScreenKeyboardParent
{
public:
	virtual void showKeyboardCallback() {};
	virtual void hideOkKeyboardCallback() {};
	virtual void hideCancelKeyboardCallback() {};
};

#endif