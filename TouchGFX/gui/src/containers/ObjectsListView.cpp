#include <gui/containers/ObjectsListView.hpp>
#include <gui/mainscreen_screen/MainScreenView.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>


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

void ObjectsListView::setParent(MainScreenView* ptr1, MainScreenPresenter* ptr2)
{
    view = ptr1;
    presenter = ptr2;
}

void ObjectsListView::setObjectsList(std::vector<Object> list)
{
    printf("Fill objects list...\r\n");
    
    for (size_t i = 0; i < list.size(); i++)
    {
        printf("Object: %s\r\n", list[i].name.c_str());
        currentObjects[i].initialize();
        currentObjects[i].setObject(list[i]);
        currentObjects[i].setParent(this, presenter);
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

void ObjectsListView::setDatetime(std::string time)
{
    printf("DATE: %s\r\n", time.c_str());
    reservation.startReservation = time;

    sprintf(inputController.inputBuffer, time.substr(0, 16).c_str());
    inputController.selectedInput = INPUTS::DATETIME;

    view->showKeyboard(&inputController, (ScreenKeyboardParent*)this);
}

void ObjectsListView::setReservation(Reservation base_reservation)
{
    this->reservation = base_reservation;
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

void ObjectsListView::hideOkKeyboardCallback()
{
    printf("OK!\r\n");

    reservation.endReservation = std::string(inputController.inputBuffer) + ":00.000+03:00";
    reservation.reason = "created by Console";

    presenter->requestCreateReservation(reservation);
}

void ObjectsListView::hideCancelKeyboardCallback()
{
    printf("CANCEL!\r\n");

    this->reservation = Reservation();
}

