#ifndef FRONTENDAPPLICATION_HPP
#define FRONTENDAPPLICATION_HPP

#include <gui_generated/common/FrontendApplicationBase.hpp>

// SCREENS
enum SCREENS {
    WELCOME_SCREEN,
    WAITING_SCREEN,
    MAIN_SCREEN
};

class FrontendHeap;

using namespace touchgfx;

class FrontendApplication : public FrontendApplicationBase
{
public:
    FrontendApplication(Model& m, FrontendHeap& heap);
    virtual ~FrontendApplication() { }

    virtual void handleTickEvent()
    {
        model.tick();
        FrontendApplicationBase::handleTickEvent();
    }

    void gotoScreen(SCREENS targetScreen);
private:
};

#endif // FRONTENDAPPLICATION_HPP
