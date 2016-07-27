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

	//****Level*****
	SDL_Texture *Level=IMG_LoadTexture(renderer, (images_dir+"Level.png").c_str());

	SDL_Rect bkgdRect;

			bkgdRect.x = 0;
			bkgdRect.y = 0;

			bkgdRect.w = 3072;
			bkgdRect.h = 2304;

			float X_pos = 0.0f;
			float Y_pos = 0.0f;
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
		Player player = Player(renderer, 0, images_dir.c_str(),audio_dir.c_str(), 150.0f, 500.0f );

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
									//ammo1.active = false;
									//bridge.active = false;
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
											player.OnMouseButton(e.button);
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
										//	guard1.guardMoveX(-player.speed, deltaTime);
										//	guard2.guardMoveX(-player.speed, deltaTime);
										//	guard3.guardMoveX(-player.speed, deltaTime);
										//	guard4.guardMoveX(-player.speed, deltaTime);
										//	guard5.guardMoveX(-player.speed, deltaTime);

										//	letter.TankMoveX(-player.speed, deltaTime);
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
										//	guard1.guardMoveX(player.speed, deltaTime);
										//	guard2.guardMoveX(player.speed, deltaTime);
										//	guard3.guardMoveX(player.speed, deltaTime);
										//	guard4.guardMoveX(player.speed, deltaTime);
										//	guard5.guardMoveX(player.speed, deltaTime);

										//	letter.TankMoveX(player.speed, deltaTime);

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
										//	guard1.guardMoveY(-player.speed, deltaTime);
										//	guard2.guardMoveY(-player.speed, deltaTime);
										//	guard3.guardMoveY(-player.speed, deltaTime);
										//	guard4.guardMoveY(-player.speed, deltaTime);
										//	guard5.guardMoveY(-player.speed, deltaTime);

										//	letter.TankMoveY(-player.speed, deltaTime);
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

											//move enemy tank
										//	guard1.guardMoveY(player.speed, deltaTime);
										//	guard2.guardMoveY(player.speed, deltaTime);
										//	guard3.guardMoveY(player.speed, deltaTime);
										//	guard4.guardMoveY(player.speed, deltaTime);
										//	guard5.guardMoveY(player.speed, deltaTime);

										//	letter.TankMoveY(player.speed, deltaTime);
										}
										else
										{
											Y_pos = bkgdRect.y;
										}
									}

									//update enemy tank
								//	guard1.Update(deltaTime, player.posRect);
								//	guard2.Update(deltaTime, player.posRect);
								//	guard3.Update(deltaTime, player.posRect);
								//	guard4.Update(deltaTime, player.posRect);
								//	guard5.Update(deltaTime, player.posRect);

									//check for hit from tanks
									//1
								/*	if (SDL_HasIntersection(&player.posRect, &guard1.guardRect))
									{
										player.guardHit();
										player.playerHealth--;
										if (player.playerHealth <= 0)
										{
											level1 = false;
											gameState = LOSE;
										}
										//break;
									}

									//2
									if (SDL_HasIntersection(&player.posRect, &guard2.guardRect))
									{
										player.guardHit();
										player.playerHealth--;
										if (player.playerHealth <= 0)
										{
											level1 = false;
											gameState = LOSE;
										}
										//break;
									}

									//3
									if (SDL_HasIntersection(&player.posRect, &guard3.guardRect))
									{
										player.guardHit();
										player.playerHealth--;
										if (player.playerHealth <= 0)
										{
											level1 = false;
											gameState = LOSE;
										}
										//break;
									}

									//4
									if (SDL_HasIntersection(&player.posRect, &guard4.guardRect))
									{
										player.guardHit();
										player.playerHealth--;
										if (player.playerHealth <= 0)
										{
											level1 = false;
											gameState = LOSE;
										}
										//break;
									}
									//5
									if (SDL_HasIntersection(&player.posRect, &guard5.guardRect))
									{
										player.guardHit();
										player.playerHealth--;
										if (player.playerHealth <= 0)
										{
											level1 = false;
											gameState = LOSE;
										}
										//break;
									}

									//check if player hit guards
									for (int i = 0; i < player.bulletList.size(); i++)
									{
										//guard
										//1
										if (SDL_HasIntersection(&guard1.guardRect, &player.bulletList[i].posRect))
										{
											Mix_PlayChannel(-1, guardHit, 0);
											player.bulletList[i].Reset();
											if (guard1.active == true)
											{
												guard1.RemoveHealth();
											}
										}
										//2
										if (SDL_HasIntersection(&guard2.guardRect, &player.bulletList[i].posRect))
										{
											Mix_PlayChannel(-1, guardHit, 0);
											player.bulletList[i].Reset();
											if (guard2.active == true)
											{
												guard2.RemoveHealth();
											}
										}
										//3
										if (SDL_HasIntersection(&guard3.guardRect, &player.bulletList[i].posRect))
										{
											Mix_PlayChannel(-1, guardHit, 0);
											player.bulletList[i].Reset();
											if (guard3.active == true)
											{
												guard3.RemoveHealth();
											}
										}
										//4
										if (SDL_HasIntersection(&guard4.guardRect, &player.bulletList[i].posRect))
										{
											Mix_PlayChannel(-1, guardHit, 0);
											player.bulletList[i].Reset();
											if (guard4.active == true)
											{
												guard4.RemoveHealth();
											}
										}
										//5
										if (SDL_HasIntersection(&guard5.guardRect, &player.bulletList[i].posRect))
										{
											Mix_PlayChannel(-1, guardHit, 0);
											player.bulletList[i].Reset();
											if (guard5.active == true)
											{
												guard5.RemoveHealth();
											}
										}
									}

									//letter
									if (SDL_HasIntersection(&player.posRect, &letter.pickupRect))
									{
										Mix_PlayChannel(-1, pickupSound, 0);
										letter.active = false;
										letter.pickupRect.x = -5000;
										letter.pickupRect.y = -5000;
										currentItem += 100 / 5;
										itemCount ++;
										if(itemCount >= 5)
										{
											bridge.active = true;
										}
									}

									//glove
									if (SDL_HasIntersection(&player.posRect, &glove.pickupRect))
									{
										Mix_PlayChannel(-1, pickupSound, 0);
										glove.active = false;
										glove.pickupRect.x = -5000;
										glove.pickupRect.y = -5000;
										currentItem += 100 / 5;
										itemCount++;
										if(itemCount >= 5)
										{
											bridge.active = true;
										}
									}

									//handkerchief
									if (SDL_HasIntersection(&player.posRect, &handkerchief.pickupRect))
									{
										Mix_PlayChannel(-1, pickupSound, 0);
										handkerchief.active = false;
										handkerchief.pickupRect.x = -5000;
										handkerchief.pickupRect.y = -5000;
										currentItem += 100 / 5;
										itemCount++;
										if(itemCount >= 5)
										{
											bridge.active = true;
										}
									}

									//rose
									if (SDL_HasIntersection(&player.posRect, &rose.pickupRect))
									{
										Mix_PlayChannel(-1, pickupSound, 0);
										rose.active = false;
										rose.pickupRect.x = -5000;
										rose.pickupRect.y = -5000;
										currentItem += 100 / 5;
										itemCount ++;
										if(itemCount >= 5)
										{
											bridge.active = true;
										}
									}
									//hat
									if (SDL_HasIntersection(&player.posRect, &hat.pickupRect))
									{
										Mix_PlayChannel(-1, pickupSound, 0);
										hat.active = false;
										hat.pickupRect.x = -5000;
										hat.pickupRect.y = -5000;
										currentItem += 100 / 5;
										itemCount ++;
										if(itemCount >= 5)
										{
											bridge.active = true;
										}
									}

									if (SDL_HasIntersection(&player.posRect, &bridge.pickupRect))
									{
										level1 = false;
										gameState = LEVEL2;
									}

									if (SDL_HasIntersection(&player.posRect, &ammo1.pickupRect))
									{
										Mix_PlayChannel(-1, pickupSound, 0);
										ammo1.active = false;
										rockCount = 6;
										throwRock = true;
									}

									if (rockCount == 6)
									{
										currentAmmo = 100;

									}

									if (rockCount == 5)
									{
										currentAmmo -= 100/6;

									}

									if (rockCount == 4)
									{
										currentAmmo -= 100/6;

									}

									if (rockCount == 3)
									{
										currentAmmo -= 100/6;

									}

									if (rockCount == 2)
									{
										currentAmmo -= 100;

									}

									if (rockCount == 1)
									{
										currentAmmo -= 100/6;

									}

									if (rockCount == 0)
									{
										currentAmmo -= 100/6;
										ammo1.active = true;

									}

									movingRect.w = currentItem / maxItem * 272;
									ammoMRect.w = currentAmmo / maxAmmo * 75;		*/


									//DRAW SECTION
									//Clear the SDL RenderTarget
									SDL_RenderClear(renderer);

									//Draw Background

									SDL_RenderCopy(renderer, Level, NULL, &bkgdRect);

									//draw pickupsbkgd
									SDL_RenderCopy(renderer, InvBkgd, NULL, &PickupsbkgdRect);

						/*			//Draw letter
									if (letter.active)
									{
										letter.Draw(renderer);
									}

									//glove
									if (glove.active)
									{
										glove.Draw(renderer);
									}

									//handkerchief
									if (handkerchief.active)
									{
										handkerchief.Draw(renderer);
									}
									//rose
									if (rose.active)
									{
										rose.Draw(renderer);
									}
									//hat
									if (hat.active)
									{
										hat.Draw(renderer);
									}
									//bridge
									if (bridge.active)
									{
										bridge.Draw(renderer);
									}
									//ammo pickup
									if (ammo1.active)
									{
										ammo1.Draw(renderer);
									}								*/
									//Draw player1 tank
									player.Draw(renderer);

									//guard1.Draw(renderer);
									//guard2.Draw(renderer);
									//guard3.Draw(renderer);
									//guard4.Draw(renderer);
									//guard5.Draw(renderer);

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
