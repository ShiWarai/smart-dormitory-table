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
    virtual void objectsListUpdateItem(ObjectInList& item, int16_t itemIndex);

    void setObjectsList(std::vector<Object> list);
protected:
private:
    touchgfx::DrawableListItems<ObjectInList, 100> currentObjects;

    touchgfx::Callback<ObjectsListView, touchgfx::DrawableListItemsInterface*, int16_t, int16_t> updateItemCallback;
    void updateItemCallbackHandler(touchgfx::DrawableListItemsInterface* items, int16_t containerIndex, int16_t itemIndex);
};

#endif // OBJECTSLISTVIEW_HPP
