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
            inputController.selectedInput = INPUTS::PIN_CODE;
            keyboard.raise(&inputController);
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
}

void WaitingScreenView::hideKeyboardCallback() 
{

    std::string pinCode(inputController.textInputs);
    printf("INPUT DATA: %s\r\n", pinCode.c_str());

    presenter->setCredentialsToModel((long) Unicode::atoi(studentIdTextBuffer), pinCode);

    //waitingPinCodeCounter = WAITING_DURATION;
}

void WaitingScreenView::setAuth(bool isAuth)
{
    if (isAuth)
        waitingPinCodeCounter = WAITING_DURATION;
    else
        printf("No auth!\r\n");

    authResult.setVisible(isAuth);
}
