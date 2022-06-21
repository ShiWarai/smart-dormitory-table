#ifndef MAINSCREENPRESENTER_HPP
#define MAINSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include "../../../../../Core/Inc/Object.h"
#include "../../../../../Core/Inc/Reservation.h"

#include <vector>

using namespace touchgfx;

class MainScreenView;

class MainScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    MainScreenPresenter(MainScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~MainScreenPresenter() {};

    long getCurrentStudentId();
    void returnToWaitingView();
    void requestResident(long currentStudentId);
    void requestUpdateResident(Resident resident);
    void requestObjects();
    void requestCreateReservation(Reservation reservation);
    void requestGetTime();
    void setResidentToProfile(Resident resident);
    void setObjectsToObjectsList(std::vector<Object> list);
    void setDatetimeToReservation(std::string datetime);
private:
    MainScreenPresenter();

    MainScreenView& view;
};

#endif // MAINSCREENPRESENTER_HPP
