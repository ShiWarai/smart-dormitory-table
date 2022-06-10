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
    profileView.setResident(presenter->getResident(presenter->getCurrentStudentId()));
}
