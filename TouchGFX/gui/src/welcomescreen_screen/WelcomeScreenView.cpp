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
}

void WelcomeScreenView::connectionInit() {
    presenter->requestConnectionInit();
}