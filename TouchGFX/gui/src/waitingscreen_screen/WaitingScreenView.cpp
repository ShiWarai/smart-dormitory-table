#include <gui/waitingscreen_screen/WaitingScreenView.hpp>

extern long last_rfid;
extern xSemaphoreHandle rfidSemaphore;

WaitingScreenView::WaitingScreenView()
{

}

void WaitingScreenView::setupScreen()
{
    WaitingScreenViewBase::setupScreen();
}

void WaitingScreenView::tearDownScreen()
{
    WaitingScreenViewBase::tearDownScreen();
}

bool WaitingScreenView::confirm_tag(long tag) {
	if (tag == 9226142)
		return true;
	else
		return false;
}

void WaitingScreenView::waitRFID() {
	printf("WAIT RFID!\r\n");

	//xSemaphoreTake(rfidSemaphore, portMAX_DELAY);
	//printf("DONE!");

	//Unicode::itoa(last_rfid, studentIdTextBuffer, STUDENTIDTEXT_SIZE, 10);
	//studentIdText.invalidate();
}
