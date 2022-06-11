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

void ProfileView::setStudentId(long currentStudentId) {
    Unicode::itoa(currentStudentId, titleTextBuffer, TITLETEXT_SIZE, 10);
    titleText.invalidate();
}

void ProfileView::setResident(Resident resident) {
    printf("FIO: %s\r\n", resident.FIO.c_str());
    printf("Student ID: %s\r\n", resident.studentId.c_str());
}
