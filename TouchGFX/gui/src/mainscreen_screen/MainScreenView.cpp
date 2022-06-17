#include <gui/mainscreen_screen/MainScreenView.hpp>

MainScreenView::MainScreenView()
{
    profileView.setParent(this, presenter);
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
    Unicode::itoa(presenter->getCurrentStudentId(), studentTitleBuffer, STUDENTTITLE_SIZE, 10);
    studentTitle.invalidate();
}

void MainScreenView::updateResident()
{
	presenter->requestResident(presenter->getCurrentStudentId());
}

void MainScreenView::setResidentToProfile(Resident resident)
{
    // Change mode
    profileView.setResident(resident);
}

void MainScreenView::goBack() {
    if(profileView.isVisible())
        application().gotoWaitingScreenScreenNoTransition();
    else if (objectsListView.isVisible())
    {
        objectsListView.setVisible(false);
        objectsListView.invalidate();
        showProfileView();
    }
}

void MainScreenView::showProfileView() {
    printf("showProfile!\r\n");

    hideAllContainers();

    updateResident();
    profileView.setVisible(true);
    profileView.initialize();
}

void MainScreenView::showObjectsListView() {
    printf("showObjectsList!\r\n");

    hideAllContainers();
    
    objectsListView.setVisible(true);
    objectsListView.invalidate();
}

void MainScreenView::hideAllContainers()
{
    profileView.setVisible(false);
    objectsListView.setVisible(false);
}