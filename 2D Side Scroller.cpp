#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <stdint.h>
#include <sstream>
#include <stdlib.h>
#include <time.h>
//#include "player.h"



using namespace std;

#if defined(__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <unistd.h>
//string var to hold the current working directory on __APPLE__
string currentWorkingDirectory(getcwd(NULL,0));

//create a string to link to the images folder on __APPLE__
string images_dir = currentWorkingDirectory + "/2DSideScroll/";

//create a string to link to the audio folder on __APPLE__
string audio_dir = currentWorkingDirectory + "/2DSideScroll/";
#endif

#if defined(_WIN32) || (_WIN64)
#include "SDL.h"
#undef main
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include <direct.h>
#define getcwd _getcwd

//string var to hold the current working directory on __APPLE__
string currentWorkingDirectory(getcwd(NULL,0));

//create a string to link to the images folder on __APPLE__
string images_dir = currentWorkingDirectory + "\\2DSideScroll\\";

//create a string to link to the audio folder on __APPLE__
string audio_dir = currentWorkingDirectory + "\\2DSideScroll\\";
#endif;

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

// code for frame rate independence
float deltaTime = 0.0;
int thisTime = 0;
int lastTime = 0;



int main(int argc, char* argv[]) {

	//**********Create the SDL Window-START**********
	//Start SDL2
	SDL_Init(SDL_INIT_EVERYTHING);

	//Create a SDL Window reference - pointer
	SDL_Window *window = NULL;

	//Create a SDL RenderTarget - pointer
	SDL_Renderer *renderer = NULL;

	//Create a SDL Window in the middle of the screen
	window = SDL_CreateWindow("Acquired Cross",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

	//Create an SDL RenderTarget
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//****Level*****
	SDL_Texture *Level=IMG_LoadTexture(renderer, (images_dir+"Level.png").c_str());

	SDL_Rect bkgdRect;

			bkgdRect.x = 0;
			bkgdRect.y = 0;

			bkgdRect.w = 2048;
			bkgdRect.h = 1536;

			float X_pos = 0.0f;
			float Y_pos = 0.0f;
	//****Level*****

	/*		//pickup hud
			SDL_Texture *InvBkgd = IMG_LoadTexture(renderer, (images_dir + "invBkgd.png").c_str());
			SDL_Rect PickupsbkgdRect;
			PickupsbkgdRect.x = 370;
			PickupsbkgdRect.y = 10;
			PickupsbkgdRect.w = 172;
			PickupsbkgdRect.h = 63;	*/

			//e handler
			SDL_Event e;

			//***** set up variables for the game states*****
			enum GameState{MENU,LEVEL,WIN,LOSE};

			bool quit = false, level = false;

			// set up the initial state
			GameState gameState = LEVEL;
    // The window is open: could enter program loop here (see SDL_PollEvent())
			while(!quit)
			{
				switch(gameState)
				{
					case MENU:
					{

					}break;
					case LEVEL:
					{
						level = true;
						//start loop
						while(level)
						{
							//Create deltaTime - for frame rate independence
							thisTime = SDL_GetTicks();
							deltaTime = (float)(thisTime - lastTime) / 1000;
							lastTime = thisTime;

							//Handle Events on Queue - Keypresses and such START*************
							while (SDL_PollEvent(&e) != 0)
							{
								//User requests quit
								if (e.type == SDL_QUIT)
								{
									quit = true;
									level = false;
									break;
								}
							}
						}

					}break;
					case WIN:
					{

					}break;
					case LOSE:
					{

					}break;
				}
			}

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}
