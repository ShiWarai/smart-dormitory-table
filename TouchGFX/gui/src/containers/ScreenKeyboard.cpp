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

void ScreenKeyboard::setParent(ScreenKeyboardParent* parent)
{
    this->parent = parent;
}

void ScreenKeyboard::raise(InputsController* inputController) {
    this->inputController = inputController;

    printf("INPUT: %u\r\n", this->inputController->selectedInput);

    Unicode::UnicodeChar buffer[MAX_INPUT];

    Unicode::fromUTF8((const uint8_t*)(this->inputController->textInputs), buffer, MAX_INPUT);

    keyboard.updateBuffer(buffer, MAX_INPUT);

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
    Unicode::UnicodeChar* buffer = keyboard.getBuffer();
    Unicode::toUTF8(buffer, (uint8_t*) inputController->textInputs, MAX_INPUT);
    printf("Update to: %s\r\n", inputController->textInputs);
    successExit = true;
}

void ScreenKeyboard::hideKeyboard() {
    printf("Go back!\r\n");

    this->setVisible(false);
    this->invalidate();

    if(successExit)
        parent->hideKeyboardCallback();
}
