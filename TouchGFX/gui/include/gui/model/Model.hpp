#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdio.h>

extern "C"
{
#include "esp8266.h"
}

class ModelListener;

class Model
{
public:
    Model();


    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
    void connectionInit();
protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
