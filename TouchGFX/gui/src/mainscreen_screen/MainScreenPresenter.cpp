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

Resident MainScreenPresenter::getResident(long studentId)
{
    return model->getResident(std::to_string(studentId));
}