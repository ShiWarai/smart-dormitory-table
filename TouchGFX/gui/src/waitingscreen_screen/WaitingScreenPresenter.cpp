#include <gui/waitingscreen_screen/WaitingScreenView.hpp>
#include <gui/waitingscreen_screen/WaitingScreenPresenter.hpp>

WaitingScreenPresenter::WaitingScreenPresenter(WaitingScreenView& v)
    : view(v)
{

}

void WaitingScreenPresenter::activate()
{

}

void WaitingScreenPresenter::deactivate()
{

}

void WaitingScreenPresenter::setStudentIdToView(long currentStudentId)
{
    view.setStudentId(currentStudentId);
}

void WaitingScreenPresenter::setCredentialsToModel(long studentId, std::string pinCode)
{
    Resident resident;

    resident.studentId = std::to_string(studentId);
    resident.pinCode = pinCode;

    model->setCredentials(resident);
}

void WaitingScreenPresenter::setAuth(bool isAuth)
{
    view.setAuth(isAuth);
}
