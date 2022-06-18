#include <gui/containers/ObjectsListView.hpp>

ObjectsListView::ObjectsListView()
{

}

void ObjectsListView::initialize()
{
    ObjectsListViewBase::initialize();
}

void ObjectsListView::setObjectsList(std::vector<Object> list)
{
    printf("GENERATE OBJECTS!\r\n");
    
    for (int i = 0; i < list.size(); i++)
        printf("Object: %s\r\n", list[i].name.c_str());
}
