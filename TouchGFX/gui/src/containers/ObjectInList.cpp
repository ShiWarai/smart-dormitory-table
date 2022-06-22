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
    case ReservationState::AVAILABLE_RESERVATION:
        createReservationHandle();
        break;
    case ReservationState::MY_RESERVATION:
        deleteReservationHandle();
        break;
    case ReservationState::NOTAVAILABLE_RESERVATION:
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
    this->object = object;

    printf("Name: %s\r\n", object.name.c_str());
    printf("Status: %ld\r\n", object.status_id);
    printf("Can be reserved: %d\r\n", object.available);

    for(int i = 0; i < object.user_reservations.size(); i++)
        printf("User\'s reservation: %ld\r\n", object.user_reservations[i]);

    Unicode::fromUTF8((const uint8_t*)object.name.c_str(), objectNameBuffer, OBJECTNAME_SIZE);
    objectName.resizeToCurrentText();
    objectName.invalidate();

    Unicode::itoa(object.status_id, objectStatusBuffer, OBJECTSTATUS_SIZE, 10);
    objectStatus.resizeToCurrentText();
    objectStatus.invalidate();

    if (object.available)
    {
        state = ReservationState::AVAILABLE_RESERVATION;
        setColorToReservationButton(touchgfx::Color::getColorFromRGB(0, 106, 255),
                                    touchgfx::Color::getColorFromRGB(13, 41, 117));
    }
    else if (object.user_reservations.size() > 0)
    {
        state = ReservationState::MY_RESERVATION;
        setColorToReservationButton(touchgfx::Color::getColorFromRGB(178, 34, 34),
                                    touchgfx::Color::getColorFromRGB(139, 0, 0));
    }
    else
    {
        state = ReservationState::NOTAVAILABLE_RESERVATION;
        setColorToReservationButton(touchgfx::Color::getColorFromRGB(255, 165, 0),
                                    touchgfx::Color::getColorFromRGB(255, 140, 0));
    }
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
    // Delete last reservation
    Reservation old_reservation;

    old_reservation.id = object.user_reservations[object.user_reservations.size() - 1];

    presenter->requestDeleteReservation(old_reservation);
}

void ObjectInList::setColorToReservationButton(touchgfx::colortype base, touchgfx::colortype touched)
{
    reservationButton.setBoxWithBorderColors(base, touched, touchgfx::Color::getColorFromRGB(0, 0, 0), touchgfx::Color::getColorFromRGB(0, 0, 0));
    reservationButton.invalidate();
}
