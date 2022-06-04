#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

extern "C"{
	extern QueueHandle_t wifiTaskMessages;
}

uint8_t progress = 0;

Model::Model() : modelListener(0)
{
}

void Model::tick()
{
	if(xQueueReceive(wifiTaskMessages, &progress, 0) == pdTRUE)
		modelListener->setLoadingProgress(progress);
}