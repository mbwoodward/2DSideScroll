#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <stdint.h>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include "player.h"
#include "chase.h"
#include "pickup.h"



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

int w, h;

int main(int argc, char* argv[]) {

	//**********Create the SDL Window-START**********
	//Start SDL2
	SDL_Init(SDL_INIT_EVERYTHING);

	//Create a SDL Window reference - pointer
	SDL_Window *window = NULL;

	//Create a SDL RenderTarget - pointer
	SDL_Renderer *renderer = NULL;

	//Create a SDL Window in the middle of the screen
	window = SDL_CreateWindow("The Final Task",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

	//Create an SDL RenderTarget
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


	SDL_Texture *keyGUI = IMG_LoadTexture(renderer, (images_dir + "key.png").c_str());
			SDL_Rect keypos;
			keypos.x = 46.5;
			keypos.y = 112;
			keypos.w = 25;
			keypos.h = 48;

	//****Level*****
	SDL_Texture *Level=IMG_LoadTexture(renderer, (images_dir+"Level.png").c_str());

	SDL_Rect bkgdRect;

			bkgdRect.x = 0;
			bkgdRect.y = -768;

			bkgdRect.w = 3072;
			bkgdRect.h = 2304;

			float X_pos = 0.0f;
			float Y_pos = -768.0f;
	//****Level*****

			//pickup hud
			SDL_Texture *InvBkgd = IMG_LoadTexture(renderer, (images_dir + "invbkgd.png").c_str());
			SDL_Rect PickupsbkgdRect;
			PickupsbkgdRect.x = 5;
			PickupsbkgdRect.y = 5;
			PickupsbkgdRect.w = 259;
			PickupsbkgdRect.h = 161;

			//key info
			bool hasKey = false;

			//Create pickups**
			Pickup key = Pickup(renderer, images_dir.c_str(), 0, 400.0f, 500.0f);
			Pickup health = Pickup(renderer, images_dir.c_str(), 1, 200.0f, 500.0f);
			Pickup magic = Pickup(renderer, images_dir.c_str(), 2, 600.0f, 500.0f);

			//bool value to control the over sound effect and the buttons
			bool alreadyOver = false;

			//e handler
			SDL_Event e;

			//***** set up variables for the game states*****
			enum GameState{MENU,LEVEL,WIN,LOSE};

			bool quit = false, level = false;

			// set up the initial state
			GameState gameState = LEVEL;

	//////AUDIO And STUFF////////
	//Open Audio Channel
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

		//Load a MUSIC file

		//Mix_Music *bgm = Mix_LoadMUS((audio_dir + "music.mp3").c_str());

		//if (bgm == NULL) {
			// In the case that the window could not be made...
		//	printf("Could not create music: %s\n", SDL_GetError());
		//	return 1;
		//}

		//if the MUSIC file is not playing - play it
		//if (!Mix_PlayingMusic())
		//	Mix_PlayMusic(bgm, -1);

		//Set up a Sound Effect CHUNK for the button over state
		Mix_Chunk *overSound = Mix_LoadWAV((audio_dir + "over.wav").c_str());

		//Set up a Sound Effect CHUNK for the button pressed state
		Mix_Chunk *pressedSound = Mix_LoadWAV((audio_dir + "pressed.wav").c_str());

		Mix_Chunk *pickupSound = Mix_LoadWAV((audio_dir + "itemPickup.wav").c_str());

		Mix_Chunk *guardHit = Mix_LoadWAV((audio_dir + "guardhit.wav").c_str());

		Mix_Chunk *kingHit = Mix_LoadWAV((audio_dir + "kinghit.wav").c_str());


		//******Create Player START**************
		Player player = Player(renderer, 0, images_dir.c_str(),audio_dir.c_str(), 250.0f, 75.0f );

		Chase chase1 = Chase(renderer, images_dir.c_str(), audio_dir.c_str(), 400.0f, 200.0f);

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
									//alreadyOver = false;
									level = true;

								/*	if (Mix_PlayingMusic())
									{
										Mix_FadeOutMusic(2000);
										Mix_FreeMusic(bgm);
									}

									bgm = Mix_LoadMUS((audio_dir + "closingin.mp3").c_str());

									if (bgm == NULL) {
										 //In the case that the window could not be made...
										printf("Could not create music: %s\n", SDL_GetError());
										return 1;
									}

									//if the MUSIC file is not playing - play it
									if (!Mix_PlayingMusic())
										Mix_PlayMusic(bgm, -1);	*/

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
										else if(e.type == SDL_KEYDOWN)
										{

										switch (e.key.keysym.sym)
										{
										case SDLK_q:
											quit = true;
											level = false;
											break;

										case SDLK_w:

											player.posRect.y -= 10;
											break;

										case SDLK_s:

											player.posRect.y += 10;
											break;

										case SDLK_d:
											player.flip = false;
											player.posRect.x += 10;
											break;

										case SDLK_a:
											player.flip = true;
											player.posRect.x -= 10;
											break;
										}//END SWITCH KEYDOWN
											break;

										}else if(e.type == SDL_MOUSEBUTTONDOWN)
										{
											if(player.playerMagic > 0)
											{
											player.OnMouseButton(e.button);
											player.Fire();
											}
										}else if(e.type == SDL_MOUSEMOTION)
										{

										}

									}// POLL EVENT

									//UPDATE SECTION
									//update player 1 tank
									player.Update(deltaTime);



									//move background
									if ((player.posRect.x >= 1024 - player.posRect.w))
									{
										//Adjust position floats based on speed, direction and deltaTime
										X_pos -= (player.speed) * deltaTime;

										if (bkgdRect.x > -2048) {
											//Update bullet position with code to account for precision loss
											bkgdRect.x = (int)(X_pos + 0.5f);

											//move enemy
											chase1.ChaseMoveX(-player.speed, deltaTime);

											key.MoveX(-player.speed, deltaTime);
											health.MoveX(-player.speed, deltaTime);
											magic.MoveX(-player.speed, deltaTime);
										}
										else
										{
											X_pos = bkgdRect.x;
										}
									}
									if ((player.posRect.x <= 0))
									{
										X_pos += (player.speed) * deltaTime;

										if (bkgdRect.x < 0) {
											//Update bullet position with code to account for precision loss
											bkgdRect.x = (int)(X_pos + 0.5f);

											//move enemy tank
											chase1.ChaseMoveX(player.speed, deltaTime);

											key.MoveX(player.speed, deltaTime);
											health.MoveX(player.speed, deltaTime);
											magic.MoveX(player.speed, deltaTime);

										}
										else
										{
											X_pos = bkgdRect.x;
										}
									}

									if ((player.posRect.y >= 768 - player.posRect.h))
									{
										//Adjust position floats based on speed, direction and deltaTime
										Y_pos -= (player.speed) * deltaTime;

										if (bkgdRect.y > -1536) {
											//Update bullet position with code to account for precision loss
											bkgdRect.y = (int)(Y_pos + 0.5f);

											//move enemy tank
											chase1.ChaseMoveY(-player.speed, deltaTime);

											key.MoveY(-player.speed, deltaTime);
											health.MoveY(-player.speed, deltaTime);
											magic.MoveY(-player.speed, deltaTime);
								}
										else
										{
											Y_pos = bkgdRect.y;
										}
									}
									if ((player.posRect.y <= 0))
									{
										Y_pos += (player.speed) * deltaTime;

										if (bkgdRect.y < 0) {
											//Update bullet position with code to account for precision loss
											bkgdRect.y = (int)(Y_pos + 0.5f);

											//move enemy chase
											chase1.ChaseMoveY(player.speed, deltaTime);

											key.MoveY(player.speed, deltaTime);
											health.MoveY(player.speed, deltaTime);
											magic.MoveY(player.speed, deltaTime);
										}
										else
										{
											Y_pos = bkgdRect.y;
										}
									}

									//UDPATE ENEMIES*************
									//chase1.Update(deltaTime, player.posRect);

									//check for hit from tanks
									//1
									if (SDL_HasIntersection(&player.posRect, &chase1.chaseRect))
									{
										player.chaseHit();
										//if (player.playerHealth <= 0)
										//{
										//	level = false;
										//	gameState = LOSE;
										//}
										//break;
									}

									//check if player hit guards
									for (int i = 0; i < player.bulletList.size(); i++)
									{
										//chase
										//1
										if (SDL_HasIntersection(&chase1.chaseRect, &player.bulletList[i].posRect))
										{
											Mix_PlayChannel(-1, guardHit, 0);
											player.bulletList[i].Reset();
											if(chase1.active == true)
											{
												chase1.RemoveHealth();
											}
										}
									}

									//key
								if (SDL_HasIntersection(&player.posRect, &key.pickupRect))
									{
									//	Mix_PlayChannel(-1, pickupSound, 0);
										key.active = false;
										key.pickupRect.x = -5000;
										key.pickupRect.y = -5000;
										hasKey = true;
									}
								//key
							if (SDL_HasIntersection(&player.posRect, &key.pickupRect))
								{
								//	Mix_PlayChannel(-1, pickupSound, 0);
									key.active = false;
									key.pickupRect.x = -5000;
									key.pickupRect.y = -5000;
									hasKey = true;
								}
							//key
						if (SDL_HasIntersection(&player.posRect, &health.pickupRect))
							{
							//	Mix_PlayChannel(-1, pickupSound, 0);
								health.active = false;
								health.pickupRect.x = -5000;
								health.pickupRect.y = -5000;
								player.playerHealth += 25;
								if(player.playerHealth >= 100)
								{
									player.playerHealth = 100;
								}
								player.healthR.w = player.playerHealth/player.maxHealth * 147;

							}
						if (SDL_HasIntersection(&player.posRect, &magic.pickupRect))
							{
							//	Mix_PlayChannel(-1, pickupSound, 0);
								magic.active = false;
								magic.pickupRect.x = -5000;
								magic.pickupRect.y = -5000;
								player.playerMagic += 25;
								if(player.playerMagic >= 100)
								{
									player.playerMagic = 100;
								}
								player.magicR.w = player.playerMagic/player.maxMagic * 147;

							}


									//DRAW SECTION
									//Clear the SDL RenderTarget
									SDL_RenderClear(renderer);

									//Draw Background

									SDL_RenderCopy(renderer, Level, NULL, &bkgdRect);

									//draw pickupsbkgd
									SDL_RenderCopy(renderer, InvBkgd, NULL, &PickupsbkgdRect);

									if(hasKey == true)
									{
										SDL_RenderCopy(renderer, keyGUI, NULL, &keypos);
									}

									//Draw key
									if (key.active)
									{
										key.Draw(renderer);
									}
									if (health.active)
									{
										health.Draw(renderer);
									}
									if (magic.active)
									{
										magic.Draw(renderer);
									}

									//Draw player1 tank
									player.Draw(renderer);

									chase1.Draw(renderer);

									// SDL Render present
									SDL_RenderPresent(renderer);
								}//END LEVEL LOOP
						}//END CASE LEVEL

									break;
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
