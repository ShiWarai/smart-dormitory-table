#include <gui/welcomescreen_screen/WelcomeScreenView.hpp>
#include <gui/welcomescreen_screen/WelcomeScreenPresenter.hpp>

WelcomeScreenPresenter::WelcomeScreenPresenter(WelcomeScreenView& v)
    : view(v)
{

}

void WelcomeScreenPresenter::activate()
{

}

void WelcomeScreenPresenter::deactivate()
{

}

void WelcomeScreenPresenter::setLoadingProgress(uint8_t value)
{
    view.updateProgressValue(value % 101);
}
