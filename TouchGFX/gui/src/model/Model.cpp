#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

extern "C"{
	extern QueueHandle_t wifiTaskMessages;
	extern QueueHandle_t rfidMessages;
}

uint8_t wifiProgress = 0;
long lastRfid = 0;


Model::Model() : modelListener(0)
{

}

bool Model::confirm_tag(long tag) {
	if (tag == 9226142)
		return true;
	else
		return false;
}

void Model::tick()
{
	if(xQueueReceive(wifiTaskMessages, &wifiProgress, 0) == pdTRUE)
		modelListener->setLoadingProgress(wifiProgress);
	if (xQueueReceive(rfidMessages, &lastRfid, 0) == pdTRUE)
	{
		if (confirm_tag(lastRfid))
		{
			modelListener->setStudentId(lastRfid);

			// Saving all data
			this->studentId = lastRfid;
		}
	}
}

long Model::getStudentId() {
	return this->studentId;
}
