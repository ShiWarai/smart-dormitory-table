#ifndef WELCOMESCREENVIEW_HPP
#define WELCOMESCREENVIEW_HPP

#include <gui_generated/welcomescreen_screen/WelcomeScreenViewBase.hpp>
#include <gui/welcomescreen_screen/WelcomeScreenPresenter.hpp>

class WelcomeScreenView : public WelcomeScreenViewBase
{
public:
    WelcomeScreenView();
    virtual ~WelcomeScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // WELCOMESCREENVIEW_HPP
