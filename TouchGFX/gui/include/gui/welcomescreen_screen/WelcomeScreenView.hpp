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
    virtual void handleTickEvent();
    
    void updateProgressValue(unsigned short value);

    void connectionInit();

private:
    static const uint16_t WAITING_DURATION = 180;
    uint16_t waitingCounter = 0;
};

#endif // WELCOMESCREENVIEW_HPP
