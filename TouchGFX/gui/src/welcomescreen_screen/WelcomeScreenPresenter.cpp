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

void WelcomeScreenPresenter::setLoadingProgress(unsigned short value)
{
    view.updateProgressValue(value % 100);
}

void WelcomeScreenPresenter::requestConnectionInit()
{
    model->connectionInit();
}