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
    Reservation new_reservation;

    new_reservation.objectId = object.id;

    view->setReservation(new_reservation);
    presenter->requestGetTime();
}

void ObjectInList::deleteReservationHandle()
{

}