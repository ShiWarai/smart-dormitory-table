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

long MainScreenPresenter::getCurrentStudentId() {
    return model->getStudentId();
}

void MainScreenPresenter::requestResident(long currentStudentId)
{
    model->requestResident(std::to_string(currentStudentId));
}

void MainScreenPresenter::requestObjects()
{
    model->requestObjects();
}

void MainScreenPresenter::requestCreateReservation(Reservation reservation)
{
    model->requestCreateReservation(reservation);
}

void MainScreenPresenter::setResidentToProfile(Resident resident)
{
    view.setResidentToProfile(resident);
}

void MainScreenPresenter::setObjectsToObjectsList(std::vector<Object> list)
{
    view.setObjectsToObjectsList(list);
}
