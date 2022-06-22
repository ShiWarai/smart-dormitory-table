#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdio.h>
#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>
#include <vector>
#include <string>

#include "../../../../../Core/Inc/Resident.h"
#include "../../../../../Core/Inc/Object.h"
#include "../../../../../Core/Inc/Reservation.h"

#include "../../../../../Core/Inc/http/httpresponseparser.h"
#include "../../../../../Core/Inc/json/json.hpp"

using namespace httpparser;
using json = nlohmann::json;

class ModelListener;

enum RequestType {
    NONE,
    AUTH,
    GET_RESIDENT,
    UPDATE_RESIDENT,
    GET_OBJECTS,
    CREATE_RESERVATION,
    DELETE_RESERVATION,
    GET_TIME,
    TEST
};

class Model
{
public:
    Model();
    void tick();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    long getStudentId();
    void requestResident(std::string currentStudentId);
    void requestUpdateResident(Resident resident);
    void requestCreateReservation(Reservation reservation);
    void requestObjects();
    void requestCurrentTime();
    void requestDeleteReservation(Reservation reservation);
    void setCredentials(Resident user);
protected:
    ModelListener* modelListener;
private:
    void responseHandler(Response __response);
    bool confirm_tag(long tag);
    Resident residentFromJson(std::string resident_str);
    std::string jsonFromResident(Resident resident);
    std::vector<Object> objectsFromJson(std::string objects_str);
    std::string datetimeFromJson(std::string time_str);
    std::string jsonFromReservation(Reservation reservation);

    char request_str[1028];
    char response_str[8128];

    RequestType currentRequestType = RequestType::NONE;
    uint8_t wifiProgress = 0;

    long lastRfid = 0;
    long currentStudentId;
    Resident currentUser;
    std::string encoded_credits;
};

#endif // MODEL_HPP
