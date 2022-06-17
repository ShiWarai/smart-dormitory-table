#ifndef OBJECTSLISTVIEW_HPP
#define OBJECTSLISTVIEW_HPP

#include <gui_generated/containers/ObjectsListViewBase.hpp>

class ObjectsListView : public ObjectsListViewBase
{
public:
    ObjectsListView();
    virtual ~ObjectsListView() {}

    virtual void initialize();
protected:
};

#endif // OBJECTSLISTVIEW_HPP
