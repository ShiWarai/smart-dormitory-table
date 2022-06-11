#include <gui/mainscreen_screen/MainScreenView.hpp>

MainScreenView::MainScreenView()
{
    profileView.setPtr(this, presenter);
}

void MainScreenView::setupScreen()
{
    MainScreenViewBase::setupScreen();
}

void MainScreenView::tearDownScreen()
{
    MainScreenViewBase::tearDownScreen();
}

void MainScreenView::updateStudentId() {
    profileView.setStudentId(presenter->getCurrentStudentId());
}

void MainScreenView::updateResident()
{
	presenter->requestResident(presenter->getCurrentStudentId());
}

void MainScreenView::setResident(Resident resident)
{
    // Change mode
    profileView.setResident(resident);
}
