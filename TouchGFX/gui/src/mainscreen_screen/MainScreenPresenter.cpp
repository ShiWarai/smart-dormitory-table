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

void MainScreenPresenter::setResidentToProfile(Resident resident)
{
    view.setResidentToProfile(resident);
}
