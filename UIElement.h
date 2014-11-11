#ifndef UIELEMENT
#define UIELEMENT
#include <SDL.h>
#include <functional>

class UIElement
{
public:
	UIElement();
	void setPosition(uint8_t flags, int x_offset = 0, int y_offset = 0);
	virtual void onClick(SDL_Event event);
	virtual void registerOnClickHandler(std::function<void()> handler) { mHandler = handler; }
	virtual void draw(SDL_Renderer* renderer);
protected:
	SDL_Texture* mTexture;
	SDL_Surface* mTmpSurf;
	SDL_Rect mRect;
private:
	std::function<void()> mHandler;
};
#endif
