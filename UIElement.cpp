#include "UIElement.h"
#include "PosEnum.h"
#include <SDL.h>

UIElement::UIElement(SDL_Surface* screen) : mScreen(screen)
{
}

void UIElement::setPosition(uint8_t flags, int x_offset, int y_offset) {
	if (mScreen != nullptr) {
		mRect.x = mScreen->w/2 - mRect.w/2 + x_offset;
		mRect.y = mScreen->h/2 - mRect.h/2 + y_offset;

		if (flags & POS_TOP) {
			mRect.y = y_offset;
		} else if (flags & POS_BOT) {
			mRect.y = mScreen->h - mRect.h - y_offset;
		}
		if (flags & POS_LEFT) {
			mRect.x = x_offset;
		} else if (flags & POS_RIGHT) {
			mRect.x = mScreen->w - mRect.w - x_offset;
		}
	}
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

void UIElement::draw()
{	
	if (mScreen != nullptr && mSurface != nullptr)
		SDL_BlitSurface(mSurface, nullptr, mScreen, &mRect);
}
