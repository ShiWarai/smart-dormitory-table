#ifndef WAITINGSCREENVIEW_HPP
#define WAITINGSCREENVIEW_HPP

#include <gui_generated/waitingscreen_screen/WaitingScreenViewBase.hpp>
#include <gui/waitingscreen_screen/WaitingScreenPresenter.hpp>
#include "../../../../../Core/Inc/ScreenKeyboardParent.hpp"

class WaitingScreenView : public WaitingScreenViewBase, public virtual ScreenKeyboardParent
{
public:
    WaitingScreenView();
    virtual ~WaitingScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();

    void setStudentId(long currentStudentId);
    void hideKeyboardCallback();
    void setAuth(bool auth);
private:
    InputsController inputController;
    static const uint16_t WAITING_DURATION = 180;
    uint16_t waitingLoadingCounter = 0;
    uint16_t waitingPinCodeCounter = 0;

    bool confirm_tag(long tag);
};

#endif // WAITINGSCREENVIEW_HPP
