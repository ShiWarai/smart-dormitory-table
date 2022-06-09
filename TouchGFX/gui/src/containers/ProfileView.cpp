#include <gui/containers/ProfileView.hpp>
#include <gui/mainscreen_screen/MainScreenView.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>

ProfileView::ProfileView()
{

}

void ProfileView::initialize()
{
    ProfileViewBase::initialize();
}

void ProfileView::setPtr(MainScreenView* ptr1, MainScreenPresenter* ptr2)
{
    view = ptr1;
    presenter = ptr2;
}

void ProfileView::setStudentId(long studentId) {
    Unicode::itoa(studentId, titleTextBuffer, TITLETEXT_SIZE, 10);
    titleText.invalidate();
}

