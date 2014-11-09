#include "Input.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <functional>
#include <string>

Input::Input(SDL_Surface* screen, int size) : UIElement(screen), mFocus(false)
{
	mFont = TTF_OpenFont("C:\\Windows\\fonts\\Arial.ttf",size);
	if (mFont == nullptr) {	
		mFont = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf",size);
	}
	mColor = {0xF0,0xF0,0xF0};
	mText = " ";
}

bool Input::handleInput(SDL_Event event)
{
	if (!mFocus) return false;
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_BACKSPACE && mText.length() > 0 ) {
			mText.pop_back();
			return true;
		} else if(event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
			SDL_SetClipboardText( mText.c_str() );
			return false;
		} else if ( event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL ) {
			mText += SDL_GetClipboardText();
			return true;
		}
	} else if (event.type == SDL_TEXTINPUT) {
		char c = event.text.text[0];
		if (SDL_GetModState() & KMOD_CTRL) {
			if (c == 'c' || c == 'C' || c == 'v' || c == 'V')
				return false;
		}
		if (mText == " ")
			mText = event.text.text;
		else
			mText += event.text.text;
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

void Input::draw() {
	std::string text = mText;
	if (text.length() == 0) text = " ";
	SDL_Color bg = {0,0,0};
	mSurface = TTF_RenderText_Shaded(mFont, text.c_str(),mColor,bg);
	mRect.h = mSurface->h;
	mRect.w = mSurface->w;
	SDL_BlitSurface(mSurface, nullptr, mScreen, &mRect);
}
