#include "Text.h"
#include "Defines.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

Text::Text(std::string text, int size) : mText(text), mRedraw(true)
{
	mFont = TTF_OpenFont(WINFONT,size);
	if (mFont == nullptr) {	
		mFont = TTF_OpenFont(LINFONT,size);
	}
	// throw exception if font is nullptr
	mColor = {0xF0, 0xF0, 0xF0 };
	SDL_Surface* tempSurf = TTF_RenderText_Blended(mFont, mText.c_str(),mColor);
	mRect.h = tempSurf->h;
	mRect.w = tempSurf->w;
	SDL_FreeSurface(tempSurf);
}
void Text::setText(std::string text)
{
	mRedraw = true;
	mText = text;
}
void Text::draw(SDL_Renderer* renderer)
{
	if (mRedraw) {
		SDL_Surface* tmpSurf = TTF_RenderText_Blended(mFont, mText.c_str(),mColor);
		mRect.h = tmpSurf->h;
		mRect.w = tmpSurf->w;
		mTexture = SDL_CreateTextureFromSurface(renderer, tmpSurf);
		SDL_FreeSurface(tmpSurf);
		mRedraw = false;
	}
	SDL_RenderCopy(renderer, mTexture, nullptr, &mRect);
}

Text::~Text() {
	TTF_CloseFont(mFont);
}
