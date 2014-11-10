#ifndef TEXTH
#define TEXTH
#include "UIElement.h"
#include "Defines.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Text : public UIElement
{
public:
	Text() = delete;
	Text(std::string text, int size = DEFAULT_TEXT_SIZE);
	void setText(std::string text);
	std::string getText() { return mText; }
	void draw(SDL_Renderer* renderer) override;
	~Text();
private:
	std::string mText;
	TTF_Font *mFont;
	SDL_Color mColor;
	bool mRedraw;
	int size;
};
#endif
