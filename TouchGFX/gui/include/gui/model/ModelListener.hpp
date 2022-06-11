#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

    virtual void setLoadingProgress(uint8_t value) {}
    virtual void setStudentId(long currentStudentId) {}
    virtual void setResident(Resident resident) {};
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
