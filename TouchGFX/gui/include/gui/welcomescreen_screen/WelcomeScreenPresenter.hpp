#ifndef WELCOMESCREENPRESENTER_HPP
#define WELCOMESCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class WelcomeScreenView;

class WelcomeScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    WelcomeScreenPresenter(WelcomeScreenView& v);

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

    virtual ~WelcomeScreenPresenter() {};
    
    void setLoadingProgress(uint8_t value);

private:
    WelcomeScreenPresenter();

    WelcomeScreenView& view;
};

#endif // WELCOMESCREENPRESENTER_HPP
