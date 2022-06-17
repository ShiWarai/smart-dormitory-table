#ifndef MAINSCREENVIEW_HPP
#define MAINSCREENVIEW_HPP

#include <gui_generated/mainscreen_screen/MainScreenViewBase.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>

class MainScreenView : public MainScreenViewBase
{
public:
    MainScreenView();
    virtual ~MainScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void updateStudentId();
    virtual void updateResident();
    virtual void goBack();
    virtual void showProfileView();
    virtual void showObjectsListView();

    void hideAllContainers();
    void setResidentToProfile(Resident resident);
protected:
};

#endif // MAINSCREENVIEW_HPP
