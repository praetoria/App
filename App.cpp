#include "Button.h"
#include "Text.h"
#include "App.h"
#include "PosEnum.h"
#include "Defines.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>
#include <functional>
#include <iostream>
#include <string>


void App::calculateKey(Text *output, Input *input)
{
	const char *in = input->getText().c_str();
	const char *in_end = in + strlen(in) - 1;
	unsigned int out = 0;
	asm(	"xor %%ecx,%%ecx;"\
		"cld;"\
		"loop: xor %%eax,%%eax;"
		"lodsb;"\
		"xor %%edx, %%edx;"\
		"movl $666, %%ebx;"\
		"imul %%ebx;"\
		"add %%eax,%%ecx;"\
		"cmp %%edi,%%esi;"\
		"jle loop"\
		: "=c" (out) : "S" (in), "D" (in_end) : "%eax","%ebx","%edx");
	output->setText("Your key is: " + std::to_string(out));	
	mRedraw = true;
}

App::App(std::string title) : mRunning(false), mTitle(title)
{
	this->init();
} 

void App::init()
{
	// Init SDL
	if (SDL_Init( SDL_INIT_EVERYTHING ) < 0) {
		// print error
	} else {
		// Init TTF
		if (TTF_Init() < 0) {
			// print error
			return;
		}
		// Create primary window
		mWindow = SDL_CreateWindow(mTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
		if (mWindow == nullptr) {
			// print error
			SDL_Quit();
			return;
		}
		// Get the screen from the window
		mScreen = SDL_GetWindowSurface(mWindow);
		if (mScreen == nullptr) {
			// print error
			SDL_DestroyWindow(mWindow);
			SDL_Quit();
			return;
		}

		// Load background
		SDL_RWops *rw = SDL_RWFromMem(BG_START,BG_SIZE);
		mBackground = SDL_LoadBMP_RW(rw, 1);
		if (mBackground == nullptr) {
			std::cout << SDL_GetError() << std::endl;
			SDL_DestroyWindow(mWindow);
			SDL_Quit();
			return;
		}
		// Blit it on the screen
		
		createElements();

	}
	
}

void App::createElements()
{
	// Exit button
	Button* exit = new Button(mScreen,std::string("Exit"));
	exit->registerOnClickHandler([this](){ this->quit(); });
	exit->setPosition(POS_BOT | POS_RIGHT,120,30);
	mElements.push_back(exit);
	// Welcome text
	Text* welcome = new Text(mScreen,std::string("Challenge 1 Key Generator"), 30);
	welcome->setPosition(POS_TOP, 0,50);
	mElements.push_back(welcome);
	// Output text
	Text* output = new Text(mScreen, std::string("Your key is: "),25);
	output->setPosition(POS_LEFT);
	mElements.push_back(output);
	// Generate input
	Input* input = new Input(mScreen);
	input->setPosition(POS_TOP | POS_LEFT,0,100);
	mInputElements.push_back(input);
	// "Generate" button
	Button* generate = new Button(mScreen, std::string("Generate"));
	generate->registerOnClickHandler([this, output, input]{this->calculateKey(output,input);});
	generate->setPosition(POS_BOT,-50,30);
	mElements.push_back(generate);
	// copy to clipboard button
	Button* clipcopy = new Button(mScreen, std::string("Copy"));
	clipcopy->registerOnClickHandler([output]{ SDL_SetClipboardText(output->getText().c_str() + 13); });
	clipcopy->setPosition(POS_LEFT | POS_BOT, 15, 30);
	mElements.push_back(clipcopy);
	

}

void App::run()
{
	
	SDL_Rect stretchRect = {0,0,mScreen->w,mScreen->h};
	// Capture events here
	SDL_Event event;
	mRunning = true;
	mRedraw = true;
	while (mRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN || event.type == SDL_TEXTINPUT) {
				for (auto i : mInputElements)
				mRedraw = mRedraw || i->handleInput(event);
			}
			if (event.type == SDL_QUIT) mRunning = false;
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
			{
				for (auto b : mElements) b->onClick(event);
				for (auto i : mInputElements) i->onClick(event);
			}
		}
		if (mRedraw) {
			SDL_BlitScaled(mBackground,nullptr,mScreen,&stretchRect);
			for (auto b : mElements) b->draw();
			for (auto i : mInputElements) i->draw();
			SDL_UpdateWindowSurface(mWindow);
			mRedraw = false;
		}
		SDL_Delay(50);
	}
}

void App::quit()
{
	mRunning = false;
}

App::~App() {
	// free memory of buttons
	for (auto b : mElements) free(b);
	for (auto i : mInputElements) free(i);
	// Free surfaces
	SDL_FreeSurface(mBackground);
	SDL_DestroyWindow(mWindow);
	// Quit SDL
	SDL_Quit();
}
