#include <gui/containers/ScreenKeyboard.hpp>

ScreenKeyboard::ScreenKeyboard()
{
    keyboard.setPosition(80, 44, 320, 276);
    add(keyboard);
}

void ScreenKeyboard::initialize()
{
    ScreenKeyboardBase::initialize();
}

void ScreenKeyboard::raise(InputsController* inputController) {
    this->inputController = inputController;

    printf("INPUT: %u\r\n", this->inputController->selectedInput);

    // Set placeholder by input
    switch (this->inputController->selectedInput)
    {
    case T_PINCODEINPUT:
        enterTitle.setWildcard(TypedText(T_PINCODEINPUT).getText());
    default:
        break;
    }

    this->setVisible(true);
    this->invalidate();
}

void ScreenKeyboard::updateInputBuffer()
{
    printf("UPDATE!\r\n");
    Unicode::UnicodeChar* buffer = keyboard.getBuffer();
    Unicode::toUTF8(buffer, (uint8_t*) inputController->textInputs, MAX_INPUT);
}

void ScreenKeyboard::hideKeyboard() {
    printf("GO BACK!\r\n");
    this->setVisible(false);
    this->invalidate();
}
