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
}

void ObjectsListView::setParent(MainScreenView* ptr1, MainScreenPresenter* ptr2)
{
    view = ptr1;
    presenter = ptr2;
}

void ObjectsListView::setObjectsList(std::vector<Object> list)
{  
    for (size_t i = 0; i < list.size(); i++)
    {
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
    inputController.selectedInput = INPUTS::END_DATETIME;

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
    reservation.endReservation = std::string(inputController.inputBuffer) + ":00.000+03:00";
    reservation.reason = "";

    presenter->requestCreateReservation(reservation);
}

void ObjectsListView::hideCancelKeyboardCallback()
{
    this->reservation = Reservation();
}

