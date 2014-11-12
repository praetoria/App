#include "Input.h"
#include "Defines.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <functional>
#include <string>

Input::Input(int size, int maxchars) : mMaxChars(maxchars),mRedraw(true), mFocus(false)
{
	mFont = TTF_OpenFont(WINFONT,size);
	if (mFont == nullptr) {	
		mFont = TTF_OpenFont(LINFONT,size);
	}
	mColor = {0xF0,0xF0,0xF0};
	mText = " ";
	
	// calculate width and height of the box
	std::string tempstring;
	while (tempstring.length()<maxchars) tempstring.push_back('H');
	SDL_Surface* temp = TTF_RenderText_Blended(mFont, tempstring.c_str(), (SDL_Color){0,0,0,0});
	mRect.w = temp->w;
	mRect.h = temp->h;
	SDL_FreeSurface(temp);
	mText = "";
}

bool Input::handleInput(SDL_Event event)
{
	if (!mFocus) return false;
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_BACKSPACE && mText.length() > 0 ) {
			mText.pop_back();
			mRedraw = true;
			mChangeHandler(mText);
			return true;
		} else if(event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
			SDL_SetClipboardText( mText.c_str() );
			return false;
		} else if ( event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL ) {
			mText += SDL_GetClipboardText();
			if (mText.length() > mMaxChars)
				mText.erase(mText.begin()+mMaxChars,mText.end());
			mRedraw = true;
			mChangeHandler(mText);
			return true;
		}
	} else if (event.type == SDL_TEXTINPUT) {
		char c = event.text.text[0];
		if (SDL_GetModState() & KMOD_CTRL) {
			if (c == 'c' || c == 'C' || c == 'v' || c == 'V')
				return false;
		}
		mText += event.text.text;
		if (mText.length() > mMaxChars)
			mText.erase(mText.begin()+mMaxChars,mText.end());
		mChangeHandler(mText);
		mRedraw = true;
		return true;
	}
	return false;
}

void Input::onClick(SDL_Event event)
{
	
	int x = event.button.x;
	int y = event.button.y;
	if (x > mRect.x && x - mRect.x < mRect.w) {
		if (y > mRect.y && y - mRect.y < mRect.h) {
			SDL_StartTextInput();
			mFocus = true;
			return;
		}
	}
	SDL_StopTextInput();
	mFocus = false;
}

void Input::draw(SDL_Renderer* renderer) {
	if (mRedraw || !mTexture) {
		std::string text(mText.c_str());
		if (text.length() == 0) text = " ";
		SDL_Surface* tmpSurf = TTF_RenderText_Blended(mFont, text.c_str(),mColor);
		mTexture = SDL_CreateTextureFromSurface(renderer, tmpSurf);
		mTextRect.w = tmpSurf->w;
		mTextRect.h = tmpSurf->h;
		mTextRect.x = mRect.x;
		mTextRect.y = mRect.y;
		SDL_FreeSurface(tmpSurf);
		mRedraw = false;
	}
	SDL_SetRenderDrawColor(renderer, 0,0,0,255);
	SDL_RenderFillRect(renderer, &mRect);
	SDL_SetRenderDrawColor(renderer, 0xF0,0xF0,0xF0,0xFF);
	if (mTexture)
		SDL_RenderCopy(renderer, mTexture, nullptr, &mTextRect);
}
