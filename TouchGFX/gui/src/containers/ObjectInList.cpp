#include <gui/containers/ObjectInList.hpp>

ObjectInList::ObjectInList()
{

}

void ObjectInList::initialize()
{
    ObjectInListBase::initialize();
}

void ObjectInList::setObject(Object object)
{
    printf("Name: %s\r\n", object.name.c_str());
    printf("Status: %ld\r\n", object.statusId);

    Unicode::fromUTF8((const uint8_t*)object.name.c_str(), objectNameBuffer, OBJECTNAME_SIZE);
    objectName.resizeToCurrentText();
    objectName.invalidate();

    Unicode::itoa(object.statusId, objectStatusBuffer, OBJECTSTATUS_SIZE, 10);
    objectStatus.resizeToCurrentText();
    objectStatus.invalidate();
}
