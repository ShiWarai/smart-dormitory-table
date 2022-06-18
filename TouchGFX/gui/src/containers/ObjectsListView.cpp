#include <gui/containers/ObjectsListView.hpp>

ObjectsListView::ObjectsListView() : updateItemCallback(this, &ObjectsListView::updateItemCallbackHandler)
{

}

void ObjectsListView::initialize()
{
    ObjectsListViewBase::initialize();
}

void ObjectsListView::objectsListUpdateItem(ObjectInList& item, int16_t itemIndex)
{
    //printf("UPDATE LIST: %d\r\n", itemIndex);
}

void ObjectsListView::setObjectsList(std::vector<Object> list)
{
    printf("Fill objects list...\r\n");
    
    for (size_t i = 0; i < list.size(); i++)
    {
        printf("Object: %s\r\n", list[i].name.c_str());
        currentObjects[i].initialize();
        currentObjects[i].setObject(list[i]);
        currentObjects[i].invalidate();
    }
    
    objectsList.setNumberOfItems(list.size());
    objectsList.setDrawables(currentObjects, updateItemCallback);

    objectsList.setVisible(true);
    loadingTitle.setVisible(false);
    objectsList.invalidate();
    objectsList.invalidateContent();
    loadingTitle.invalidate();
}

void ObjectsListView::updateItemCallbackHandler(touchgfx::DrawableListItemsInterface* items, int16_t containerIndex, int16_t itemIndex)
{
    if (items == &currentObjects)
    {
        touchgfx::Drawable* d = items->getDrawable(containerIndex);
        ObjectInList* cc = (ObjectInList*)d;
        objectsListUpdateItem(*cc, itemIndex);
    }
}
