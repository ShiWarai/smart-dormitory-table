#include <gui/waitingscreen_screen/WaitingScreenView.hpp>
#include "../../../../../Core/Inc/InputsCollection.h"

WaitingScreenView::WaitingScreenView()
{
    keyboard.setParent(this);
}

void WaitingScreenView::setupScreen()
{
    WaitingScreenViewBase::setupScreen();
}

void WaitingScreenView::tearDownScreen()
{
    WaitingScreenViewBase::tearDownScreen();
}

void WaitingScreenView::setStudentId(long currentStudentId) 
{
	Unicode::itoa(currentStudentId, studentIdTextBuffer, STUDENTIDTEXT_SIZE, 10);
	studentIdText.invalidate();

    waitingLoadingCounter = WAITING_DURATION;
}

//Handles delays
void WaitingScreenView::handleTickEvent()
{
    if (waitingLoadingCounter > 0)
    {
        waitingLoadingCounter--;
        if (waitingLoadingCounter == 0)
        {
            // open keyboard
            memset(inputController.inputBuffer, '\0', MAX_INPUT);
            inputController.selectedInput = INPUTS::PIN_CODE;
            keyboard.raise(&inputController);
            // hide
            authResult.setVisible(false);
        }
    }

    if (waitingPinCodeCounter > 0)
    {
        waitingPinCodeCounter--;
        if (waitingPinCodeCounter == 0)
        {
            // change screen
            application().gotoMainScreenScreenSlideTransitionWest();
        }
    }

    if (errorCooldownCounter > 0)
    {
        errorCooldownCounter--;
        if (errorCooldownCounter == 0)
        {
            Unicode::itoa(0, studentIdTextBuffer, STUDENTIDTEXT_SIZE, 10);
            studentIdText.invalidate();

            authResult.setVisible(false);
            authResult.invalidate();
        }
    }
}

void WaitingScreenView::hideOkKeyboardCallback() 
{
    std::string pinCode(inputController.inputBuffer);
    printf("INPUT DATA: %s\r\n", pinCode.c_str());

    presenter->setCredentialsToModel((long) Unicode::atoi(studentIdTextBuffer), pinCode);
}

void WaitingScreenView::hideCancelKeyboardCallback()
{
    errorCooldownCounter = WAITING_DURATION;
}

void WaitingScreenView::setAuth(bool isAuth)
{
    if (isAuth)
        waitingPinCodeCounter = WAITING_DURATION;
    else
        errorCooldownCounter = WAITING_DURATION;

    if(isAuth)
        authResult.setWildcard(TypedText(T_SUCCESS).getText());
    else
        authResult.setWildcard(TypedText(T_ERROR).getText());
    authResult.setVisible(true);
    authResult.invalidate();
}
