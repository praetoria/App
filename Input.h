#ifndef INPUTH
#define INPUTH
#include "UIElement.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <functional>
#include <string>

class Input : public UIElement
{
public:
	Input(SDL_Surface* screen);
	void registerOnClickHandler(std::function<void()> handler) {}
	bool handleInput(SDL_Event event);
	void onClick(SDL_Event event) override;
	void draw() override;
	std::string getText() { return mText; }
private:
	bool mFocus;
	TTF_Font* mFont;
	SDL_Color mColor;
	std::string mText;
};
#endif	
