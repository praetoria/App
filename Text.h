#ifndef TEXTH
#define TEXTH
#include "UIElement.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Text : public UIElement
{
public:
	Text() = delete;
	Text(SDL_Surface* screen, std::string text, int size);
	void setText(std::string text);
	std::string getText() { return mText; }
	void draw() override;
	~Text();
private:
	std::string mText;
	TTF_Font *mFont;
	SDL_Color mColor;
	int size;
};
#endif
