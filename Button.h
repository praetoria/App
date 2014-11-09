#ifndef BUTTONH
#define BUTTONH
#include "UIElement.h"
#include <SDL.h>
#include <string>


class Button : public UIElement
{
public:
	Button(SDL_Surface* screen, std::string text);
	~Button();
};
#endif
