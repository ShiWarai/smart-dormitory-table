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
    successExit = false;

    printf("Start input text: %s\r\n", inputController->inputBuffer);

    Unicode::UnicodeChar buffer[MAX_INPUT];

    Unicode::fromUTF8((const uint8_t*)(inputController->inputBuffer), buffer, MAX_INPUT);

    keyboard.updateBuffer(buffer, MAX_INPUT, std::strlen(inputController->inputBuffer));

    // Set placeholder by input
    switch (inputController->selectedInput)
    {
    case T_PINCODEINPUT:
        enterTitle.setWildcard(TypedText(T_PINCODEINPUT).getText());
        break;
    case T_DATETIMEINPUT:
        enterTitle.setWildcard(TypedText(T_DATETIMEINPUT).getText());
        break;
    default:
        break;
    }

    this->setVisible(true);
    this->invalidate();
}

void ScreenKeyboard::updateInputBuffer()
{
    Unicode::UnicodeChar* buffer = keyboard.getBuffer();
    Unicode::toUTF8(buffer, (uint8_t*) inputController->inputBuffer, MAX_INPUT);
    printf("Update to: %s\r\n", inputController->inputBuffer);
    successExit = true;
}

void ScreenKeyboard::hideKeyboard() {
    printf("Go back!\r\n");

    this->setVisible(false);
    this->invalidate();

    if (successExit)
        parent->hideOkKeyboardCallback();
    else
        parent->hideCancelKeyboardCallback();
}
