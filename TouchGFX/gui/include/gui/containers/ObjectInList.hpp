#ifndef OBJECTINLIST_HPP
#define OBJECTINLIST_HPP

#include <gui_generated/containers/ObjectInListBase.hpp>
#include "../../../../../Core/Inc/Object.h"

class ObjectInList : public ObjectInListBase
{
public:
    ObjectInList();
    virtual ~ObjectInList() {}

    virtual void initialize();

    void setObject(Object object);
protected:
};

#endif // OBJECTINLIST_HPP
