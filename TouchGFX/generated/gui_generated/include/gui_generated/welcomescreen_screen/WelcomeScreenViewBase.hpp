/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef WELCOMESCREENVIEWBASE_HPP
#define WELCOMESCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/welcomescreen_screen/WelcomeScreenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/ScalableImage.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/containers/progress_indicators/BoxProgress.hpp>

class WelcomeScreenViewBase : public touchgfx::View<WelcomeScreenPresenter>
{
public:
    WelcomeScreenViewBase();
    virtual ~WelcomeScreenViewBase() {}
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::ScalableImage welcomeBackground;
    touchgfx::TextArea welcomeText;
    touchgfx::BoxProgress initialProgress;
    touchgfx::TextArea wifiDoneTitle;
    touchgfx::TextArea createdBy;

private:

};

#endif // WELCOMESCREENVIEWBASE_HPP
