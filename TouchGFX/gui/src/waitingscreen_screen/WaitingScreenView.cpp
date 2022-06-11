#include <gui/waitingscreen_screen/WaitingScreenView.hpp>

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
            application().gotoMainScreenScreenSlideTransitionWest();
        }
    }
}