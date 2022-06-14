#include <gui/screenkeyboard_screen/ScreenKeyboardView.hpp>
#include <texts/TextKeysAndLanguages.hpp>

#define COUNT_INPUTS 1
#define MAX_INPUT 4

Unicode::UnicodeChar textInputs[COUNT_INPUTS][MAX_INPUT];
uint8_t selectedInput = -1;

ScreenKeyboardView::ScreenKeyboardView()
{
    keyboard.setPosition(80, 44, 320, 276);
    add(keyboard);
}

void ScreenKeyboardView::setupScreen()
{
    printf("INPUT: %u\r\n", selectedInput);

    // Set placeholder by input
    switch (selectedInput)
    {
    case 0:
        enterTitle.setWildcard(TypedText(T_PINCODEINPUT).getText());
    default:
        break;
    }

    ScreenKeyboardViewBase::setupScreen();
}

void ScreenKeyboardView::tearDownScreen()
{
    ScreenKeyboardViewBase::tearDownScreen();
}

void ScreenKeyboardView::updateInputBuffer()
{
    Unicode::UnicodeChar* buffer = keyboard.getBuffer();
    Unicode::strncpy(textInputs[selectedInput], buffer, Unicode::strlen(buffer) + 1);
}