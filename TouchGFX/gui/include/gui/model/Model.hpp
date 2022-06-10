#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdio.h>
#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>

#include "../../../simulator/msvs/Resident.h"
#include <string>

class ModelListener;

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
    Resident getResident(std::string studentId);
protected:
    ModelListener* modelListener;
private:
    bool confirm_tag(long tag);

    long studentId;
};

#endif // MODEL_HPP
