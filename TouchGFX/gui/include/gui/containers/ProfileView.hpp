#ifndef PROFILEVIEW_HPP
#define PROFILEVIEW_HPP

#include <gui_generated/containers/ProfileViewBase.hpp>
#include "../../../../../Core/Inc/ScreenKeyboardParent.hpp"
#include "../../../../../Core/Inc/Resident.h"

class MainScreenView;
class MainScreenPresenter;

class ProfileView : public ProfileViewBase, public virtual ScreenKeyboardParent
{
public:
    ProfileView();
    virtual ~ProfileView() {}

    virtual void initialize();
    virtual void updateResident();

    void setParent(MainScreenView* ptr1, MainScreenPresenter* ptr2);
    void setResident(Resident resident);
    void hideOkKeyboardCallback();
    void hideCancelKeyboardCallback();
protected:
    bool isResidentUpdated = false;
    Resident resident;

    void textAreaClickHandler(const TextAreaWithOneWildcard& textArea, const ClickEvent& e);
    touchgfx::Callback<ProfileView, const TextAreaWithOneWildcard&, const ClickEvent&> textAreaClickCallback;

    MainScreenView* view;
    MainScreenPresenter* presenter;
    InputsController inputController;
};

#endif // PROFILEVIEW_HPP
