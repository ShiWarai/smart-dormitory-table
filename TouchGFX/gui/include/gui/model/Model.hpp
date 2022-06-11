#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdio.h>
#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>
#include <vector>

#include <string>
#include "../../../../../Core/Inc/Resident.h"
#include "../../../../../Core/Inc/http/httpresponseparser.h"
#include "../../../../../Core/Inc/json/json.hpp"

using namespace httpparser;
using json = nlohmann::json;

class ModelListener;

enum RequestType {
    NONE,
    GET_RESIDENT,
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
protected:
    ModelListener* modelListener;
private:
    void responseHandler(Response response);
    bool confirm_tag(long tag);
    Resident residentFromJson(std::string resident_str);

    char request_str[1028];
    char response_str[8128];

    RequestType currentRequestType = NONE;
    uint8_t wifiProgress = 0;

    long lastRfid = 0;
    long currentStudentId;
};

#endif // MODEL_HPP
