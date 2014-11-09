#include "Button.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

Button::Button(SDL_Surface* screen, std::string text) : UIElement(screen)
{
	TTF_Font* font = TTF_OpenFont("C:\\Windows\\fonts\\Arial.ttf",40);
	if (font == nullptr) {	
		font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf",40);
	}
	// throw exception if font == nullptr

	SDL_Color fg = { 0, 0, 0};
	SDL_Color bg = { 0xAA, 0xAA, 0xAA};
	mSurface = TTF_RenderText_Shaded(font,text.c_str(),fg,bg);
	mRect.h = mSurface->h;
	mRect.w = mSurface->w;
}


Button::~Button()
{
	SDL_FreeSurface(mSurface);
}
