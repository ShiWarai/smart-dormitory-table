#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "../../../../../Core/Inc/base64.h"


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
			modelListener->setStudentIdToView(lastRfid);

			// Saving all data
			this->currentStudentId = lastRfid;
		}
	}
	if (xQueueReceive(wifiResponseMessages, response_str, 0) == pdTRUE)
	{
		HttpResponseParser parser;
		Response response;

		HttpResponseParser::ParseResult res = parser.parse(response, response_str, response_str + strlen(response_str));

		if (res == HttpResponseParser::ParsingCompleted)
			responseHandler(response);
	}
}

long Model::getStudentId() {
	return this->currentStudentId;
}

void Model::setCredentials(Resident user)
{
	this->currentUser = user;

	// Check credentials
	std::string credits = this->currentUser.studentId + ":" + this->currentUser.pinCode;

	printf("Credits: %s\r\n", credits.c_str());
	
	this->encoded_credits = macaron::Base64::Encode(credits);

	sprintf(request_str, "GET /resident/%s HTTP/1.1\r\nHost: ridramecraft.ru:8080\r\nAuthorization:Basic %s\r\n\r\n",
		this->currentUser.studentId.c_str(), encoded_credits.c_str());

	xQueueSend(wifiRequestMessages, request_str, 0);
	currentRequestType = RequestType::AUTH;
}

void Model::requestResident(std::string currentStudentId) 
{	
	sprintf(request_str, "GET /resident/%s HTTP/1.1\r\nHost: ridramecraft.ru:8080\r\nAuthorization:Basic %s\r\n\r\n",
			currentStudentId.c_str(), encoded_credits.c_str());

	xQueueSend(wifiRequestMessages, request_str, 0);
	currentRequestType = RequestType::GET_RESIDENT;
}

void Model::requestCreateReservation(Reservation reservation)
{
	printf("Reservation Object id: %ld\r\n", reservation.objectId);

	std::string reservation_json = jsonFromReservation(reservation);
	sprintf(request_str, "POST /reservation/ HTTP/1.1\r\nHost: ridramecraft.ru:8080\r\nAuthorization:Basic %s\r\n"
						 "Content-Type: application/json\r\nContent-Length: %u\r\n\r\n%s\r\n",
						 encoded_credits.c_str(), reservation_json.size(), reservation_json.c_str());

	xQueueSend(wifiRequestMessages, request_str, 0);
	currentRequestType = RequestType::CREATE_RESERVATION;
}

void Model::requestObjects()
{
	sprintf(request_str, "GET /object/all HTTP/1.1\r\nHost: ridramecraft.ru:8080\r\nAuthorization:Basic %s\r\n\r\n",
			encoded_credits.c_str());

	xQueueSend(wifiRequestMessages, request_str, 0);
	currentRequestType = RequestType::GET_OBJECTS;
}

void Model::responseHandler(Response response)
{
	switch (currentRequestType)
	{
	case RequestType::GET_RESIDENT:
		if (response.statusCode == 200)
		{
			printf("GET USER!\r\n");
			modelListener->setResidentToProfile(residentFromJson(std::string(response.content.begin(), response.content.end())));
		}
		else
		{
			printf("NO USER!\r\n");
			printf("Something wrong with response: %s\r\n", std::string(response.content.begin(), response.content.end()).c_str());
		}
		break;
	case RequestType::GET_OBJECTS:
		if (response.statusCode == 200)
		{
			printf("GET OBJECT!\r\n");
			modelListener->setObjectsToObjectsList(objectsFromJson(std::string(response.content.begin(), response.content.end())));
		}
		else
		{
			printf("NO OBJECT!\r\n");
			modelListener->setObjectsToObjectsList({});
		}
		break;
	case RequestType::CREATE_RESERVATION:
		if (response.statusCode == 200)
		{
			printf("RESERVATION CREATED!\r\n");
			//modelListener->setObjectsToObjectsList(objectsFromJson(std::string(response.content.begin(), response.content.end())));
		}
		else
		{
			printf("CANT CREATE!\r\n");
		}
		break;
	case RequestType::AUTH:
		if (response.statusCode == 200)
		{
			printf("GET USER!\r\n");
			currentUser = residentFromJson(std::string(response.content.begin(), response.content.end()));
			modelListener->setAuth(true);
		}
		else
		{
			printf("NO USER!\r\n");
			printf("Something wrong with response: %s\r\n", std::string(response.content.begin(), response.content.end()).c_str());
			modelListener->setAuth(false);
		}
		break;
	default:
		printf("NO SUCH REQUEST!\r\n");
		break;
	}

	currentRequestType = NONE;
}

Resident Model::residentFromJson(std::string resident_str)
{
	json resident_json = json::parse(resident_str);

	Resident resident;

	resident.FIO = (std::string)resident_json["surname"]
					+ " " + (std::string)resident_json["name"]
					+ " " + (std::string)resident_json.value("patronymic", "");

	resident.studentId = resident_json["studentId"];

	resident.birthdate = resident_json["birthdate"];

	resident.pinCode = "****";

	resident.room = resident_json.value("roomNumber", 0);

	resident.role = resident_json["role"];

	return resident;
}

std::vector<Object> Model::objectsFromJson(std::string objects_str)
{
	json objects_json = json::parse(objects_str);

	std::vector<Object> objects;

	for (size_t i = 0; i < objects_json.size(); i++)
	{
		Object object;

		object.id = objects_json[i]["id"];
		object.name = objects_json[i]["name"];
		object.statusId = objects_json[i]["statusId"];
		object.typeId = objects_json[i]["typeId"];

		objects.push_back(object);
	}

	return objects;
}

std::string Model::jsonFromReservation(Reservation reservation)
{
	json reservation_json =
	{
		{"objectId", reservation.objectId},
		{"reason", reservation.reason},
		{"startReservation", reservation.startReservation},
		{"endReservation", reservation.endReservation}
	};

	return reservation_json.dump();
}