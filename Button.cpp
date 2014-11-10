#include "Button.h"
#include "Defines.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

Button::Button(std::string text, int size)
{
	mFont = TTF_OpenFont(WINFONT,size);
	if (mFont == nullptr) {	
		mFont = TTF_OpenFont(LINFONT,size);
	}
	// throw exception if font == nullptr

	SDL_Color fg = { 0, 0, 0};
	SDL_Color bg = { 0xAA, 0xAA, 0xAA};
	mTmpSurf = TTF_RenderText_Shaded(mFont,text.c_str(),fg,bg);
	mRect.h = mTmpSurf->h;
	mRect.w = mTmpSurf->w;
}


Button::~Button()
{
	TTF_CloseFont(mFont);
}
