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
	void calculateKey(Text* output, std::string text);
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	SDL_Texture* mBackground;
	std::list<UIElement*> mElements;
	std::list<Input*> mInputElements;
};
#endif
