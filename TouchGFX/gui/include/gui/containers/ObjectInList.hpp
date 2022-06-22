#ifndef OBJECTINLIST_HPP
#define OBJECTINLIST_HPP

#include <gui_generated/containers/ObjectInListBase.hpp>
#include "../../../../../Core/Inc/Object.h"
#include "../../../../../Core/Inc/Reservation.h"
#include <touchgfx/Color.hpp>

class ObjectsListView;
class MainScreenPresenter;

enum ReservationState {
    AVAILABLE_RESERVATION,
    MY_RESERVATION,
    NOTAVAILABLE_RESERVATION
};

class ObjectInList : public ObjectInListBase
{
public:
    ObjectInList();
    virtual ~ObjectInList() {}

    virtual void initialize();
    virtual void reservationHandle();
    
    void setParent(ObjectsListView* ptr1, MainScreenPresenter* ptr2);
    void setObject(Object object);
    void createReservationHandle();
    void deleteReservationHandle();
private:
    Object object;
    ReservationState state;

    void setColorToReservationButton(touchgfx::colortype base, touchgfx::colortype touched);

    ObjectsListView* view;
    MainScreenPresenter* presenter;
};

#endif // OBJECTINLIST_HPP
