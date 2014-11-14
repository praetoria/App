#include "UIElement.h"
#include "PosEnum.h"
#include "Defines.h"
#include <SDL.h>

UIElement::UIElement()
{
	// set width and height
}

void UIElement::setPosition(uint8_t flags, int x_offset, int y_offset) {
	mRect.x = SCREENW/2 - mRect.w/2 + x_offset;
	mRect.y = SCREENH/2 - mRect.h/2 + y_offset;

	if (flags & POS_TOP) {
		mRect.y = y_offset;
	} else if (flags & POS_BOT) {
		mRect.y = SCREENH - mRect.h - y_offset;
	}
	if (flags & POS_LEFT) {
		mRect.x = x_offset;
	} else if (flags & POS_RIGHT) {
		mRect.x = SCREENW - mRect.w - x_offset;
	}
	mTexture = nullptr;
}

void UIElement::onClick(SDL_Event event)
{
	if (mHandler) {
		int x = event.button.x;
		int y = event.button.y;
		if (x > mRect.x && x - mRect.x < mRect.w) {
			if (y > mRect.y && y - mRect.y < mRect.h) {
				mHandler();
			}
		}
	}
}

void UIElement::draw(SDL_Renderer* renderer)
{	
	if (renderer != nullptr) {
		if (mTexture == nullptr && mTmpSurf != nullptr) {
			mTexture = SDL_CreateTextureFromSurface(renderer, mTmpSurf);
			SDL_FreeSurface(mTmpSurf);
		}
		SDL_RenderCopy(renderer, mTexture, nullptr, &mRect);
	}
}
