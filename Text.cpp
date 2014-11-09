#include "Text.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

Text::Text(SDL_Surface* screen, std::string text, int size) : UIElement(screen), mText(text)
{
	mFont = TTF_OpenFont("C:\\Windows\\fonts\\Arial.ttf",size);
	if (mFont == nullptr) {	
		mFont = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf",size);
	}
	// throw exception if font is nullptr
	mColor = {0xF0, 0xF0, 0xF0 };
	mSurface = TTF_RenderText_Blended(mFont, mText.c_str(),mColor);
	mRect.h = mSurface->h;
	mRect.w = mSurface->w;
}
void Text::setText(std::string text)
{
	mText = text;
}
void Text::draw()
{
	if (mSurface != nullptr) SDL_FreeSurface(mSurface);
	mSurface = TTF_RenderText_Blended(mFont, mText.c_str(),mColor);
	mRect.h = mSurface->h;
	mRect.w = mSurface->w;
	SDL_BlitSurface(mSurface,nullptr,mScreen,&mRect);
}

Text::~Text() {
	SDL_FreeSurface(mSurface);
}
