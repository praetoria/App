#ifndef BUTTONH
#define BUTTONH
#include "UIElement.h"
#include "Defines.h"
#include <SDL.h>
#include <string>


class Button : public UIElement
{
public:
	Button(SDL_Surface* screen, std::string text, int size = DEFAULT_BUTTON_SIZE);
	~Button();
};
#endif
