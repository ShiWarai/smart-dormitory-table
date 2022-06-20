#include <gui/containers/ObjectInList.hpp>
#include <gui/containers/ObjectsListView.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>

ObjectInList::ObjectInList()
{

}

void ObjectInList::initialize()
{
    ObjectInListBase::initialize();
}

void ObjectInList::reservationHandle()
{
    switch (state)
    {
    case ReservationState::NONE_RESERVATION:
        createReservationHandle();
        break;
    case ReservationState::MY_RESERVATION:
        printf("Try delete my reservation\r\n");
        break;
    case ReservationState::SOMEONES_RESERVATION:
        printf("You can't do nothing!\r\n");
        break;
    }
}

void ObjectInList::setParent(ObjectsListView* ptr1, MainScreenPresenter* ptr2)
{
    view = ptr1;
    presenter = ptr2;
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

    this->object = object;
}

void ObjectInList::createReservationHandle()
{
    Reservation newReservation;

    newReservation.objectId = object.id;
    newReservation.reason = "created by Console";
    newReservation.startReservation = "2022-06-19T21:02:05.458+03:00";
    newReservation.endReservation = "2022-06-20T22:02:05.458+03:00";

    presenter->requestCreateReservation(newReservation);
}

void ObjectInList::deleteReservationHandle()
{

}
