#include <gui/containers/ProfileView.hpp>
#include <gui/mainscreen_screen/MainScreenView.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>

ProfileView::ProfileView() : textAreaClickCallback(this, &ProfileView::textAreaClickHandler)
{
    pinCodeText.setClickAction(textAreaClickCallback);
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

void ProfileView::updateResident()
{
    if (isResidentUpdated)
    {
        isResidentUpdated = false;
        confirmButton.setVisible(false);
        confirmButton.invalidate();

        printf("NEW RESIDENT DATA:\r\n\r\n");

        printf("Surname: %s\r\n", resident.surname.c_str());
        printf("Student ID: %s\r\n", resident.studentId.c_str());
        printf("Birthdate: %s\r\n", resident.birthdate.c_str());
        printf("Pin-code: %s\r\n", resident.pinCode.c_str());
        printf("Room: %d\r\n", resident.room);
        printf("Role: %s\r\n", resident.role.c_str());

        presenter->requestUpdateResident(resident);
    }
}

void ProfileView::setResident(Resident resident) 
{
    this->resident = resident;

    printf("Surname: %s\r\n", resident.surname.c_str());
    printf("Student ID: %s\r\n", resident.studentId.c_str());
    printf("Birthdate: %s\r\n", resident.birthdate.c_str());
    printf("Pin-code: %s\r\n", resident.pinCode.c_str());
    printf("Room: %d\r\n", resident.room);
    printf("Role: %s\r\n", resident.role.c_str());

    std::string FIO = resident.surname + " " + resident.name + " " + resident.patronymic;
    Unicode::fromUTF8((const uint8_t*) FIO.c_str(), fioTextBuffer, FIOTEXT_SIZE);
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

void ProfileView::hideOkKeyboardCallback()
{
    if (std::strlen(inputController.inputBuffer) == 4) 
    {
        resident.pinCode = std::string(inputController.inputBuffer);

        isResidentUpdated = true;
        confirmButton.setVisible(true);
        confirmButton.invalidate();
    }
    else
        printf("NOT 4 DIGITS!\r\n");
}

void ProfileView::hideCancelKeyboardCallback()
{
    printf("CLOSE WITHOUT CHANGING!\r\n");
}

void ProfileView::textAreaClickHandler(const TextAreaWithOneWildcard& textArea, const ClickEvent& e)
{
    if (&textArea == &pinCodeText) 
    {
        sprintf(inputController.inputBuffer, "");
        inputController.selectedInput = INPUTS::PIN_CODE;

        view->showKeyboard(&inputController, (ScreenKeyboardParent*)this);
    }
}
