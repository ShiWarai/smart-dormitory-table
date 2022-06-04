#include <gui/welcomescreen_screen/WelcomeScreenView.hpp>

WelcomeScreenView::WelcomeScreenView()
{

}

void WelcomeScreenView::setupScreen()
{
    WelcomeScreenViewBase::setupScreen();
}

void WelcomeScreenView::tearDownScreen()
{
    WelcomeScreenViewBase::tearDownScreen();
}

void WelcomeScreenView::updateProgressValue(unsigned short value)
{
    initialProgress.setValue(value);
    initialProgress.invalidate();

    if (value >= 100)
    {
        wifiDoneTitle.setVisible(true);
        wifiDoneTitle.invalidate();

        initialProgress.setVisible(false);
        initialProgress.invalidate();

        waitingCounter = WAITING_DURATION;
    }
}

//Handles delays
void WelcomeScreenView::handleTickEvent()
{
    if (waitingCounter > 0)
    {
        waitingCounter--;
        if (waitingCounter == 0)
        {
            //changeScreen
            application().gotoWaitingScreenScreenNoTransition();
        }
    }
}
