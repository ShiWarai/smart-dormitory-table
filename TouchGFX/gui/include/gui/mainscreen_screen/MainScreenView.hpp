#ifndef MAINSCREENVIEW_HPP
#define MAINSCREENVIEW_HPP

#include <gui_generated/mainscreen_screen/MainScreenViewBase.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>
#include "../../../../../Core/Inc/Object.h"

#include <vector>

class MainScreenView : public MainScreenViewBase
{
public:
    MainScreenView();
    virtual ~MainScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void updateStudentId();
    virtual void updateResident();
    void updateObjectsList();
    virtual void goBack();
    virtual void showProfileView();
    virtual void showObjectsListView();

    void hideAllContainers();
    void setResidentToProfile(Resident resident);
    void setObjectsToObjectsList(std::vector<Object> list);
protected:
};

#endif // MAINSCREENVIEW_HPP
