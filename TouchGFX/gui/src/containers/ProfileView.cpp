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

void ProfileView::setParent(MainScreenView* ptr1, MainScreenPresenter* ptr2)
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
    printf("Birthdate: %s\r\n", resident.birthdate.c_str());
    printf("Pin-code: %s\r\n", resident.pinCode.c_str());
    printf("Room: %d\r\n", resident.room);
    printf("Role: %s\r\n", resident.role.c_str());

    Unicode::fromUTF8((const uint8_t*) resident.FIO.c_str(), fioTextBuffer, FIOTEXT_SIZE);
    fioText.resizeToCurrentText();
    fioText.invalidate();

    Unicode::fromUTF8((const uint8_t*)resident.birthdate.c_str(), birthdateTextBuffer, BIRTHDATETEXT_SIZE);
    birthdateText.resizeToCurrentText();
    birthdateText.invalidate();

    Unicode::fromUTF8((const uint8_t*)resident.pinCode.c_str(), pinCodeTextBuffer, PINCODETEXT_SIZE);
    pinCodeText.resizeToCurrentText();
    pinCodeText.invalidate();

    Unicode::itoa(resident.room, roomTextBuffer, ROOMTEXT_SIZE, 10);
    roomText.resizeToCurrentText();
    roomText.invalidate();

    Unicode::fromUTF8((const uint8_t*)resident.role.c_str(), roleTextBuffer, ROLETEXT_SIZE);
    roleText.resizeToCurrentText();
    roleText.invalidate();
}
