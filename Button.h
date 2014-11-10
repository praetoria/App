#ifndef BUTTONH
#define BUTTONH
#include "UIElement.h"
#include "Defines.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>


class Button : public UIElement
{
public:
	Button(std::string text, int size = DEFAULT_BUTTON_SIZE);
	~Button();
private:
	TTF_Font* mFont;
};
#endif
