#include <gui/mainscreen_screen/MainScreenView.hpp>

MainScreenView::MainScreenView()
{
}

void MainScreenView::setupScreen()
{
    profileView.setParent(this, presenter);
    objectsListView.setParent(this, presenter);

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

void MainScreenView::updateObjectsList()
{
    presenter->requestObjects();
}

void MainScreenView::setResidentToProfile(Resident resident)
{
    profileView.setResident(resident);
}

void MainScreenView::setObjectsToObjectsList(std::vector<Object> list)
{
    objectsListView.setObjectsList(list);
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
    hideAllContainers();

    updateResident();

    profileView.setVisible(true);
    profileView.invalidate();
}

void MainScreenView::showObjectsListView() {
    hideAllContainers();

    updateObjectsList();
    
    objectsListView.setVisible(true);
    objectsListView.invalidate();
}

void MainScreenView::hideAllContainers()
{
    profileView.setVisible(false);
    objectsListView.setVisible(false);

    this->invalidate();
}
