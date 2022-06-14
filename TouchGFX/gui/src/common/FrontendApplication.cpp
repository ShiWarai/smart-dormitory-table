#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/transitions/Transition.hpp>

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : FrontendApplicationBase(m, heap)
{

}

void FrontendApplication::gotoScreen(SCREENS targetScreen)
{
	switch (targetScreen)
	{
	case WELCOME_SCREEN:
		gotoWelcomeScreenScreenNoTransition();
		break;
	case WAITING_SCREEN:
		gotoWaitingScreenScreenNoTransition();
		break;
	case MAIN_SCREEN:
		gotoMainScreenScreenSlideTransitionWest();
		break;
	default:
		break;
	}

	pendingScreenTransitionCallback = &transitionCallback;
}
