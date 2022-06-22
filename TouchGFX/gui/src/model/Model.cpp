#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "../../../../../Core/Inc/base64.h"

#define SELF_ROOM 167


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

void Model::requestUpdateResident(Resident resident)
{
	printf("Resident: %s\r\n", resident.studentId.c_str());

	std::string resident_json = jsonFromResident(resident);
	sprintf(request_str, "PUT /resident/%s HTTP/1.1\r\nHost: ridramecraft.ru:8080\r\nAuthorization:Basic %s\r\n"
		"Content-Type: application/json\r\nContent-Length: %u\r\n\r\n%s\r\n",
		resident.studentId.c_str(), encoded_credits.c_str(), resident_json.size(), resident_json.c_str());

	xQueueSend(wifiRequestMessages, request_str, 0);
	currentRequestType = RequestType::UPDATE_RESIDENT;
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
	sprintf(request_str, "GET /tablet/object/by?room=%d HTTP/1.1\r\nHost: ridramecraft.ru:8080\r\nAuthorization:Basic %s\r\n\r\n",
			SELF_ROOM, encoded_credits.c_str());

	xQueueSend(wifiRequestMessages, request_str, 0);
	currentRequestType = RequestType::GET_OBJECTS;
}

void Model::requestCurrentTime()
{
	sprintf(request_str, "GET /api/timezone/Europe/Moscow HTTP/1.1\r\nHost: worldtimeapi.org:80\r\n\r\n");

	xQueueSend(wifiRequestMessages, request_str, 0);
	currentRequestType = RequestType::GET_TIME;
}

void Model::requestDeleteReservation(Reservation reservation)
{
	sprintf(request_str, "DELETE /reservation/%ld HTTP/1.1\r\nHost: ridramecraft.ru:8080\r\nAuthorization:Basic %s\r\n\r\n",
		reservation.id, encoded_credits.c_str());

	xQueueSend(wifiRequestMessages, request_str, 0);
	currentRequestType = RequestType::DELETE_RESERVATION;
}

void Model::responseHandler(Response __response)
{
	bool isFinalResponse = true;
	std::string response = std::string(__response.content.begin(), __response.content.end());

	switch (currentRequestType)
	{
	case RequestType::GET_RESIDENT:
		if (__response.statusCode == 200)
		{
			printf("GET USER!\r\n");
			modelListener->setResidentToProfile(residentFromJson(response));
		}
		else
		{
			printf("NO USER!\r\n");
			printf("Something wrong with response: %s\r\n", response.c_str());
		}
		break;
	case RequestType::UPDATE_RESIDENT:
		if (__response.statusCode == 200)
		{
			printf("RESIDENT IS UPDATED!\r\n");

			modelListener->returnToWaitingView();
		}
		else
		{
			printf("CANT UPDATE!\r\n");
		}
		break;
	case RequestType::GET_OBJECTS:
		if (__response.statusCode == 200)
		{
			printf("GET OBJECT!\r\n");
			modelListener->setObjectsToObjectsList(objectsFromJson(response));
		}
		else
		{
			printf("NO OBJECT!\r\n");
			modelListener->setObjectsToObjectsList({});
		}
		break;
	case RequestType::CREATE_RESERVATION:
		if (__response.statusCode == 200)
		{
			printf("RESERVATION CREATED!\r\n");
			isFinalResponse = false;
			requestObjects();
		}
		else
		{
			printf("CANT CREATE!\r\n");
		}
		break;
	case RequestType::DELETE_RESERVATION:
		if (__response.statusCode == 200)
		{
			printf("RESERVATION DELETED!\r\n");
			isFinalResponse = false;
			requestObjects();
		}
		else
		{
			printf("CANT DELETE!\r\n");
		}
		break;
	case RequestType::GET_TIME:
		if (__response.statusCode == 200)
		{
			printf("GOT TIME!\r\n");
			modelListener->setDatetimeToReservation(datetimeFromJson(response));
		}
		else
		{
			printf("NO TIME!\r\n");
		}
		break;
	case RequestType::AUTH:
		if (__response.statusCode == 200)
		{
			printf("GET USER!\r\n");
			currentUser = residentFromJson(response);
			modelListener->setAuth(true);
		}
		else
		{
			printf("NO USER!\r\n");
			modelListener->setAuth(false);
		}
		break;
	default:
		printf("NO SUCH REQUEST!\r\n");
		break;
	}

	if(isFinalResponse)
		currentRequestType = NONE;
}

Resident Model::residentFromJson(std::string resident_str)
{
	json resident_json = json::parse(resident_str);

	Resident resident;

	resident.surname = resident_json["surname"];
	resident.name = resident_json["name"];
	resident.patronymic = resident_json.value("patronymic", "");
	resident.studentId = resident_json["studentId"];
	resident.birthdate = resident_json["birthdate"];
	resident.pinCode = "****";
	resident.room = resident_json.value("roomNumber", 0);
	resident.role = resident_json["role"];

	return resident;
}

std::string Model::jsonFromResident(Resident resident)
{
	json resident_json =
	{
		{"surname", resident.surname},
		{"name", resident.name},
		{"patronymic", resident.patronymic},
		{"birthdate", resident.birthdate},
		{"studentId", resident.studentId},
		{"pinCode", resident.pinCode},
		{"roomNumber", resident.room},
		{"role", resident.role}
	};

	return resident_json.dump();
}

std::vector<Object> Model::objectsFromJson(std::string objects_str)
{
	json objects_json = json::parse(objects_str);

	std::vector<Object> objects;

	for (size_t i = 0; i < objects_json.size(); i++)
	{
		Object object;

		object.id = objects_json[i]["object"]["id"];
		object.name = objects_json[i]["object"]["name"];
		object.status_id = objects_json[i]["object"]["statusId"];
		object.type_id = objects_json[i]["object"]["typeId"];

		object.available = objects_json[i]["canBeReserved"];
		for(size_t j = 0; j < objects_json[i]["residentActiveReservations"].size(); j++)
			object.user_reservations.push_back(objects_json[i]["residentActiveReservations"][j]);

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

std::string Model::datetimeFromJson(std::string time_str)
{
	json time_json = json::parse(time_str);

	return (std::string) time_json["datetime"];
}
