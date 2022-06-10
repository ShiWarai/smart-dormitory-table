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
    printf("Test!\r\n");
    printf("%ld\r\n", presenter->getCurrentStudentId());
    profileView.setStudentId(presenter->getCurrentStudentId());
    //profileView.invalidate();
}
