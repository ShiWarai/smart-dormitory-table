#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>


extern "C"{
	extern QueueHandle_t wifiInitMessages;
	extern QueueHandle_t rfidMessages;
	extern QueueHandle_t wifiRequestMessages;
	extern QueueHandle_t wifiResponseMessages;
}

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
	if(xQueueReceive(wifiInitMessages, &wifiProgress, 0) == pdTRUE)
		modelListener->setLoadingProgress(wifiProgress);
	if (xQueueReceive(rfidMessages, &lastRfid, 0) == pdTRUE)
	{
		if (confirm_tag(lastRfid))
		{
			modelListener->setStudentId(lastRfid);

			// Saving all data
			this->currentStudentId = lastRfid;
		}
	}
	if (xQueueReceive(wifiResponseMessages, response_str, 0) == pdTRUE)
	{
		printf("RESPONSE:\r\n%s\r\n", response_str);

		Response response;
		HttpResponseParser::ParseResult res = parser.parse(response, response_str, response_str + strlen(response_str));

		if (res == HttpResponseParser::ParsingCompleted)
			responseHandler(response);
	}
}

long Model::getStudentId() {
	return this->currentStudentId;
}

void Model::requestResident(std::string currentStudentId) {
	
	sprintf(request_str, "GET /resident/%s HTTP/1.1\r\nHost: ridramecraft.ru:8080\r\nAuthorization:Basic %s\r\n\r\n",
			currentStudentId.c_str(), "MTIzNDU2NzoxMTEx");

	printf("REQUEST:\r\n%s\r\n", request_str);

	xQueueSend(wifiRequestMessages, request_str, 0);
	currentRequestType = GET_RESIDENT;
}

void Model::responseHandler(Response response)
{
	switch (currentRequestType)
	{
	case GET_RESIDENT:
		modelListener->setResident(residentFromJson(std::string(response.content.begin(), response.content.end())));
		break;
	default:
		printf("No such request\r\n");
		break;
	}

	currentRequestType = NONE;
}

Resident Model::residentFromJson(std::string resident_str)
{
	json resident_json = json::parse(resident_str);

	Resident resident;

	resident.FIO = (std::string) resident_json["surname"]
				+ (std::string) resident_json["name"]
				+ (std::string) resident_json.value("patronymic", "");

	resident.studentId = resident_json["studentId"];

	return resident;
}
