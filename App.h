#ifndef APPH
#define APPH
#include "UIElement.h"
#include "Text.h"
#include "Input.h"
#include <SDL2/SDL.h>
#include <string>
#include <list>
#include <memory>

class App
{
public:
	App(std::string title);
	void run();
	void quit();
	~App();
private:
	std::string mTitle;
	void init();
	void createElements();
	bool mRunning;
	bool mRedraw;
	void calculateKey(Text* output, Input *input);
	SDL_Window* mWindow;
	SDL_Surface* mScreen;
	SDL_Surface* mBackground;
	std::list<UIElement*> mElements;
	std::list<Input*> mInputElements;
};
#endif
