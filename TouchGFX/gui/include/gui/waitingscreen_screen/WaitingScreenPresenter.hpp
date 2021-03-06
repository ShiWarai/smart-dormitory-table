#ifndef WAITINGSCREENPRESENTER_HPP
#define WAITINGSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class WaitingScreenView;

class WaitingScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    WaitingScreenPresenter(WaitingScreenView& v);

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

    virtual ~WaitingScreenPresenter() {};

    void setStudentIdToView(long currentStudentId);
    void setCredentialsToModel(long studentId, std::string pinCode);
    void setAuth(bool isAuth);
private:
    WaitingScreenPresenter();

    WaitingScreenView& view;
};

#endif // WAITINGSCREENPRESENTER_HPP
