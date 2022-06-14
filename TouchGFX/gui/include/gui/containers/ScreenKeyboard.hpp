#ifndef SCREENKEYBOARD_HPP
#define SCREENKEYBOARD_HPP

#include <gui_generated/containers/ScreenKeyboardBase.hpp>
#include <gui/common/CustomKeyboard.hpp>
#include "../../../../../Core/Inc/InputsCollection.h"

class ScreenKeyboard : public ScreenKeyboardBase
{
public:
    ScreenKeyboard();
    virtual ~ScreenKeyboard() {}

    virtual void initialize();

    void raise(InputsController* inputController);
    void updateInputBuffer();
    void hideKeyboard();
protected:
    CustomKeyboard keyboard;
private:
    InputsController* inputController;
};

#endif // SCREENKEYBOARD_HPP
