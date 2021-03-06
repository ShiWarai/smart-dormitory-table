/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef OBJECTINLISTBASE_HPP
#define OBJECTINLISTBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/containers/buttons/Buttons.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/canvas/Line.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/mixins/ClickListener.hpp>

class ObjectInListBase : public touchgfx::Container
{
public:
    ObjectInListBase();
    virtual ~ObjectInListBase() {}
    virtual void initialize();

    /*
     * Virtual Action Handlers
     */
    virtual void reservationHandle()
    {
        // Override and implement this function in ObjectInList
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::ClickListener< touchgfx::IconButtonStyle< touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  >  > reservationButton;
    touchgfx::TextAreaWithOneWildcard objectName;
    touchgfx::Line line1;
    touchgfx::PainterRGB565 line1Painter;
    touchgfx::TextAreaWithOneWildcard objectStatus;
    touchgfx::Line line2;
    touchgfx::PainterRGB565 line2Painter;

    /*
     * Wildcard Buffers
     */
    static const uint16_t OBJECTNAME_SIZE = 28;
    touchgfx::Unicode::UnicodeChar objectNameBuffer[OBJECTNAME_SIZE];
    static const uint16_t OBJECTSTATUS_SIZE = 3;
    touchgfx::Unicode::UnicodeChar objectStatusBuffer[OBJECTSTATUS_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<ObjectInListBase, const touchgfx::AbstractButtonContainer&> flexButtonCallback;

    /*
     * Callback Handler Declarations
     */
    void flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src);

};

#endif // OBJECTINLISTBASE_HPP
