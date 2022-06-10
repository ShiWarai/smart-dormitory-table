#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdio.h>
#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>

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
protected:
    ModelListener* modelListener;
private:
    bool confirm_tag(long tag);

    long studentId;
};

#endif // MODEL_HPP
