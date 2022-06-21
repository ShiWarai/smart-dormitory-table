#include <gui/mainscreen_screen/MainScreenView.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>

MainScreenPresenter::MainScreenPresenter(MainScreenView& v)
    : view(v)
{

}

void MainScreenPresenter::activate()
{

}

void MainScreenPresenter::deactivate()
{

}

void MainScreenPresenter::returnToWaitingView() {
    view.goBack();
}

long MainScreenPresenter::getCurrentStudentId() {
    return model->getStudentId();
}

void MainScreenPresenter::requestResident(long currentStudentId)
{
    model->requestResident(std::to_string(currentStudentId));
}

void MainScreenPresenter::requestUpdateResident(Resident resident)
{
    model->requestUpdateResident(resident);
}

void MainScreenPresenter::requestObjects()
{
    model->requestObjects();
}

void MainScreenPresenter::requestCreateReservation(Reservation reservation)
{
    model->requestCreateReservation(reservation);
}

void MainScreenPresenter::requestGetTime()
{
    model->requestCurrentTime();
}

void MainScreenPresenter::setResidentToProfile(Resident resident)
{
    view.setResidentToProfile(resident);
}

void MainScreenPresenter::setObjectsToObjectsList(std::vector<Object> list)
{
    view.setObjectsToObjectsList(list);
}

void MainScreenPresenter::setDatetimeToReservation(std::string datetime)
{
    view.setDatetimeToReservation(datetime);
}
