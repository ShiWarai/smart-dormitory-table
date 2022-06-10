#ifndef PROFILEVIEW_HPP
#define PROFILEVIEW_HPP

#include <gui_generated/containers/ProfileViewBase.hpp>
#include "../../../simulator/msvs/Resident.h"

class MainScreenView;
class MainScreenPresenter;

class ProfileView : public ProfileViewBase
{
public:
    ProfileView();
    virtual ~ProfileView() {}

    virtual void initialize();

    void setPtr(MainScreenView* ptr1, MainScreenPresenter* ptr2);
    void setStudentId(long studentId);
    void setResident(Resident resident);
private:
    MainScreenView* view;
    MainScreenPresenter* presenter;
};

#endif // PROFILEVIEW_HPP
