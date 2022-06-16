#ifndef SCREENKEYBOARD_HPP
#define SCREENKEYBOARD_HPP

#include <gui_generated/containers/ScreenKeyboardBase.hpp>
#include <gui/common/CustomKeyboard.hpp>
#include "../../../../../Core/Inc/InputsCollection.h"
#include "../../../../../Core/Inc/ScreenKeyboardParent.hpp"

class ScreenKeyboard : public ScreenKeyboardBase
{
public:
    ScreenKeyboard();
    virtual ~ScreenKeyboard() {}

    virtual void initialize();
    void setParent(ScreenKeyboardParent* parent);

    void raise(InputsController* inputController);
    void updateInputBuffer();
    void hideKeyboard();
protected:
    CustomKeyboard keyboard;
private:
    InputsController* inputController;
    bool successExit;

    ScreenKeyboardParent* parent;
};

#endif // SCREENKEYBOARD_HPP
