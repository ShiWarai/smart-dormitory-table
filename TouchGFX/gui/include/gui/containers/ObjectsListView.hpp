#ifndef OBJECTSLISTVIEW_HPP
#define OBJECTSLISTVIEW_HPP

#include <gui_generated/containers/ObjectsListViewBase.hpp>
#include "../../../../../Core/Inc/Object.h"

#include <vector>

class ObjectsListView : public ObjectsListViewBase
{
public:
    ObjectsListView();
    virtual ~ObjectsListView() {}

    virtual void initialize();

    void setObjectsList(std::vector<Object> list);
protected:
};

#endif // OBJECTSLISTVIEW_HPP
