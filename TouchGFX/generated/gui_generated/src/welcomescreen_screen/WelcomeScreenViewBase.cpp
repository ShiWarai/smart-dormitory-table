/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/welcomescreen_screen/WelcomeScreenViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

WelcomeScreenViewBase::WelcomeScreenViewBase()
{

    __background.setPosition(0, 0, 480, 272);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    welcomeBackground.setBitmap(touchgfx::Bitmap(BITMAP_BLUE_BACKGROUNDS_MAIN_BG_TEXTURE_480X272PX_ID));
    welcomeBackground.setPosition(0, 0, 480, 272);
    welcomeBackground.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);

    welcomeText.setXY(52, 87);
    welcomeText.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    welcomeText.setLinespacing(0);
    welcomeText.setTypedText(touchgfx::TypedText(T___SINGLEUSE_C02T));

    initialProgress.setXY(148, 175);
    initialProgress.setProgressIndicatorPosition(2, 2, 180, 16);
    initialProgress.setRange(0, 100);
    initialProgress.setDirection(touchgfx::AbstractDirectionProgress::RIGHT);
    initialProgress.setBackground(touchgfx::Bitmap(BITMAP_BLUE_PROGRESSINDICATORS_BG_MEDIUM_PROGRESS_INDICATOR_BG_SQUARE_0_DEGREES_ID));
    initialProgress.setColor(touchgfx::Color::getColorFromRGB(0, 151, 255));
    initialProgress.setValue(0);

    add(__background);
    add(welcomeBackground);
    add(welcomeText);
    add(initialProgress);
}

void WelcomeScreenViewBase::setupScreen()
{

}

//Called when the screen transition ends
void WelcomeScreenViewBase::afterTransition()
{
    //connectionInit
    //When screen transition ends call virtual function
    //Call connectionInit
    connectionInit();

    //changingScreen
    //When connectionInit completed change screen to MainScreen
    //Go to MainScreen with no screen transition
    application().gotoMainScreenScreenNoTransition();
}
