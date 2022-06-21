#ifndef OBJECTSLISTVIEW_HPP
#define OBJECTSLISTVIEW_HPP

#include <gui_generated/containers/ObjectsListViewBase.hpp>
#include "../../../../../Core/Inc/Object.h"
#include "../../../../../Core/Inc/ScreenKeyboardParent.hpp"

#include <vector>

class MainScreenView;
class MainScreenPresenter;

class ObjectsListView : public ObjectsListViewBase, public virtual ScreenKeyboardParent
{
public:
    ObjectsListView();
    virtual ~ObjectsListView() {}

    virtual void initialize();
    virtual void objectsListUpdateItem(ObjectInList& item, int16_t itemIndex);

    void setParent(MainScreenView* ptr1, MainScreenPresenter* ptr2);
    void setObjectsList(std::vector<Object> list);
    void setDatetime(std::string time);
    void setReservation(Reservation base_reservation);
    void hideOkKeyboardCallback();
    void hideCancelKeyboardCallback();
protected:
private:
    touchgfx::DrawableListItems<ObjectInList, 100> currentObjects;
    Reservation reservation;

    touchgfx::Callback<ObjectsListView, touchgfx::DrawableListItemsInterface*, int16_t, int16_t> updateItemCallback;
    void updateItemCallbackHandler(touchgfx::DrawableListItemsInterface* items, int16_t containerIndex, int16_t itemIndex);

    MainScreenView* view;
    MainScreenPresenter* presenter;
    InputsController inputController;
};

#endif // OBJECTSLISTVIEW_HPP
