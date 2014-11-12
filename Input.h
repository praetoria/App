#ifndef INPUTH
#define INPUTH
#include "UIElement.h"
#include "Defines.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <functional>
#include <string>

class Input : public UIElement
{
public:
	Input(int size = DEFAULT_TEXT_SIZE, int maxsize = DEFAULT_INPUT_WIDTH);
	void registerOnClickHandler(std::function<void()> handler) {}
	void registerOnChangeHandler(std::function<void(std::string)> handler) { mChangeHandler = handler; }
	bool handleInput(SDL_Event event);
	void onClick(SDL_Event event);
	void draw(SDL_Renderer* renderer);
	std::string getText() { return mText; }
private:
	std::function<void(std::string)> mChangeHandler;
	bool mFocus;
	bool mRedraw;
	int mMaxChars;
	SDL_Rect mTextRect;
	TTF_Font* mFont;
	SDL_Color mColor;
	std::string mText;
};
#endif	
