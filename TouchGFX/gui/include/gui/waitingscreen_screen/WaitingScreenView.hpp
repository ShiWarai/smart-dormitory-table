#ifndef WAITINGSCREENVIEW_HPP
#define WAITINGSCREENVIEW_HPP

#include <gui_generated/waitingscreen_screen/WaitingScreenViewBase.hpp>
#include <gui/waitingscreen_screen/WaitingScreenPresenter.hpp>

class WaitingScreenView : public WaitingScreenViewBase
{
public:
    WaitingScreenView();
    virtual ~WaitingScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();

    void setStudentId(long currentStudentId);
private:
    bool confirm_tag(long tag);
    static const uint16_t WAITING_DURATION = 180;
    uint16_t waitingCounter = 0;
};

#endif // WAITINGSCREENVIEW_HPP
