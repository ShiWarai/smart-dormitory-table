#include <gui/waitingscreen_screen/WaitingScreenView.hpp>
#include "../../../../../Core/Inc/InputsCollection.h"

InputsController inputController;

WaitingScreenView::WaitingScreenView()
{

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

    waitingCounter = WAITING_DURATION;
}

//Handles delays
void WaitingScreenView::handleTickEvent()
{
    if (waitingCounter > 0)
    {
        waitingCounter--;
        if (waitingCounter == 0)
        {
            //changeScreen
            inputController.selectedInput = INPUTS::PIN_CODE;
            printf("CHANGE: %u\r\n", inputController.selectedInput);
            keyboard.raise(&inputController);
            //application().gotoMainScreenScreenSlideTransitionWest();
        }
    }
}
