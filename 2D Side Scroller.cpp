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
#include "turret.h"
#include "cursor.h"



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

			   //***************** Create Menus - START *****************

			    // ****************** Menu - START****************

			    // create a SDL texture

				string menuPath = images_dir + "mainBack.png";

				SDL_Texture *main=IMG_LoadTexture(renderer, menuPath.c_str());


			    // create SDL Rectangle for the title graphic
			    SDL_Rect titlePos;


			    // set the X,Y,W, and H for the Rectangle
			    titlePos.x=0;
			    titlePos.y=0;

			    //Use Query to find w and h
				SDL_QueryTexture(main, NULL, NULL, &w, &h);
				titlePos.w = w;
				titlePos.h = h;
			    //********TITLE - END***********


			    // ********* ONE PLAYER - START******

			    string playNPath = images_dir + "playbuttonN.png";

				SDL_Texture *playN=IMG_LoadTexture(renderer, playNPath.c_str());


			    string playOPath = images_dir + "playbuttonO.png";

				SDL_Texture *playO=IMG_LoadTexture(renderer, playOPath.c_str());

				string playPPath = images_dir + "playbuttonP.png";

				SDL_Texture *playP=IMG_LoadTexture(renderer, playPPath.c_str());


			    // create SDL Rectangle for the title graphic
			    SDL_Rect Players1NPos;


			    // set the X,Y,W, and H for the Rectangle
			    Players1NPos.x=25;
			    Players1NPos.y=266;

			    //query w and h
			    SDL_QueryTexture(playN,NULL,NULL,&w,&h);
			    Players1NPos.w = w;
			    Players1NPos.h = h;

			    //********ONE PLAYER - END***********

			    string playANPath = images_dir + "playagainbuttonN.png";

				SDL_Texture *playAN=IMG_LoadTexture(renderer, playANPath.c_str());


				string playAOPath = images_dir + "playagainbuttonO.png";

				SDL_Texture *playAO=IMG_LoadTexture(renderer, playAOPath.c_str());

				string playAPPath = images_dir + "playagainbuttonP.png";

				SDL_Texture *playAP=IMG_LoadTexture(renderer, playAPPath.c_str());


				// create SDL Rectangle for the title graphic
				SDL_Rect Players1ANPos;
				SDL_Rect Players1AOPos;


				// set the X,Y,W, and H for the Rectangle
				Players1ANPos.x=25;
				Players1ANPos.y=266;

				Players1AOPos.x=25;
				Players1AOPos.y=266;

				//query w and h
				SDL_QueryTexture(playAN,NULL,NULL,&w,&h);
				Players1ANPos.w = w;
				Players1ANPos.h = h;

				SDL_QueryTexture(playAO,NULL,NULL,&w,&h);
				Players1AOPos.w = w;
				Players1AOPos.h = h;

			    //********PLAY AGAIN - END******

				 //*********Create win and lose Graphics - START ***********
				 string winPath = images_dir + "Win.png";

				 SDL_Texture* winLevel=IMG_LoadTexture(renderer, winPath.c_str());

				 string losePath = images_dir + "Lose.png";

				 SDL_Texture* loseLevel=IMG_LoadTexture(renderer, losePath.c_str());

				 // create SDL Rectangle for the title graphic
				 SDL_Rect winPos;


				 // set the X,Y,W, and H for the Rectangle
				 winPos.x = 0;
				 winPos.y = 0;

				 //query w and h
				 SDL_QueryTexture(winLevel, NULL, NULL, &w, &h);
				 winPos.w = w;
				 winPos.h = h;

				 //**********Win and Lose Text - START*********

				 string WinTextPath = images_dir + "winText.png";

				  SDL_Texture* winText=IMG_LoadTexture(renderer, WinTextPath.c_str());

				  // create SDL Rectangle for the title graphic
				  SDL_Rect winTextPos;


				  // set the X,Y,W, and H for the Rectangle
				  winTextPos.x=280;
				  winTextPos.y=100;

				  //query w and h
				  SDL_QueryTexture(winText, NULL, NULL, &w, &h);
				  winTextPos.w = w;
				  winTextPos.h = h;

				  string LoseTextPath = images_dir + "loseText.png";

				  SDL_Texture* loseText=IMG_LoadTexture(renderer, LoseTextPath.c_str());

				  // create SDL Rectangle for the title graphic
				  SDL_Rect loseTextPos;


				  // set the X,Y,W, and H for the Rectangle
				  loseTextPos.x=280;
				  loseTextPos.y=100;

				  //query w and h
				  SDL_QueryTexture(loseText, NULL, NULL, &w, &h);
				  loseTextPos.w = w;
				  loseTextPos.h = h;


			    //***************** Create Menus - END *****************

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

			//*****Secondary-SPIRITS**********
			Pickup spirits = Pickup(renderer, images_dir.c_str(), 3, 64.0f, 1002.0f);
			Pickup lights = Pickup(renderer, images_dir.c_str(), 4, 70.0f, 982.0f);


			//bool value to control the over sound effect and the buttons
			bool alreadyOver = false;

			//e handler
			SDL_Event e;

			//***** set up variables for the game states*****
			enum GameState{MENU,LEVEL,WIN,LOSE};

			bool quit = false, level = false, menu = false, win = false, lose = false, players1Over = false, players1Pressed = false;

			// set up the initial state
			GameState gameState = MENU;

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


		//********CREATE CURSOR BEGIN**********
		Cursor cursor(renderer, images_dir.c_str(), 300.0f, 50.0f);
		//********CREATE CURSOR FINISH*********

		//******Create Player**************
		Player player = Player(renderer, 0, images_dir.c_str(),audio_dir.c_str(), 250.0f, 75.0f);

		//********Create Enemy Turrets START**********
		//*********Enemy Turrets END***********
		Turret turret1 = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 0, 850.0f, 550.0f);
//		Turret turret2 = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 0, 850.0f, 550.0f);
//		Turret turret3 = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 0, 850.0f, 550.0f);
//		Turret turret4 = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 0, 850.0f, 550.0f);
//		Turret turret5 = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 0, 850.0f, 550.0f);
//		Turret turret6 = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 0, 850.0f, 550.0f);
//		Turret turret7 = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 0, 850.0f, 550.0f);
//		Turret turret8 = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 0, 850.0f, 550.0f);
//		Turret turret9 = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 0, 850.0f, 550.0f);
//		Turret turret10 = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 0, 850.0f, 550.0f);
//
//		Turret SoulWarden = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 1, 0.0f, 0.0f);

		//********Create Enemy Chase START****************
		Chase chase1 = Chase(renderer, images_dir.c_str(), audio_dir.c_str(), 400.0f, 200.0f);
		//Chase chase2 = Chase(renderer, images_dir.c_str(), audio_dir.c_str(), 400.0f, 200.0f);
		//Chase chase3 = Chase(renderer, images_dir.c_str(), audio_dir.c_str(), 400.0f, 200.0f);
		//Chase chase4 = Chase(renderer, images_dir.c_str(), audio_dir.c_str(), 400.0f, 200.0f);
		//Chase chase5 = Chase(renderer, images_dir.c_str(), audio_dir.c_str(), 400.0f, 200.0f);
		//Chase chase6 = Chase(renderer, images_dir.c_str(), audio_dir.c_str(), 400.0f, 200.0f);
		//Chase chase7 = Chase(renderer, images_dir.c_str(), audio_dir.c_str(), 400.0f, 200.0f);
		//Chase chase8 = Chase(renderer, images_dir.c_str(), audio_dir.c_str(), 400.0f, 200.0f);
		//Chase chase9 = Chase(renderer, images_dir.c_str(), audio_dir.c_str(), 400.0f, 200.0f);
		//Chase chase10 = Chase(renderer, images_dir.c_str(), audio_dir.c_str(), 400.0f, 200.0f);
		//*********Create Enemy Chase END**************



    // The window is open: could enter program loop here (see SDL_PollEvent())
			while(!quit)
			{
				switch(gameState)
				{
					case MENU:
					{
						alreadyOver = false;
						menu = true;
						SDL_ShowCursor(0);

						//start loop
						while(menu)
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
								menu = false;
								break;
							}
							else if(e.type == SDL_KEYDOWN)
							{

							switch (e.key.keysym.sym)
							{
							case SDLK_q:
								quit = true;
								menu = false;
								break;
							case SDLK_ESCAPE:
								quit = true;
								menu = false;
								break;
							}//END SWITCH KEYDOWN
								break;
							}else if(e.type == SDL_MOUSEBUTTONDOWN)
							{
								switch(e.button.button)
										{
										case SDL_BUTTON_LEFT:
											if (players1Over)
											{
												players1Pressed = true;
												players1Over = false;

											}
										break;
										}
							}else if(e.type == SDL_MOUSEBUTTONUP)
							{
								switch(e.button.button)
										{
										case SDL_BUTTON_LEFT:
											if (players1Over)
											{
												//Play the Over sound - plays fine through levels, must pause/delay for QUIT
												//Mix_PlayChannel(-1, pressedSound, 0);
												menu = false;
												gameState = LEVEL;

											}
										break;
										}
							}else if(e.type == SDL_MOUSEMOTION)
							{
								cursor.MouseMotion(e);
							}

						}// POLL EVENT

						//Update
						//Update Cursor
						cursor.Update(deltaTime);


						//check for collision between cursor active state and buttons
						players1Over = SDL_HasIntersection(&cursor.cursorRect, &Players1NPos);

						//If the cursor is over a button, play the over sound
						if (players1Over)
						{
							if (alreadyOver == false)
							{
								//Mix_PlayChannel(-1, overSound, 0);
								alreadyOver = true;
							}
						}

						//if the cursor is not over ANY button, reset the already Over var
						if (!players1Over)
						{
							alreadyOver = false;
							players1Pressed = false;
						}



						// Start Drawing
						//Clear SDL renderer
						SDL_RenderClear(renderer);

						//Draw the menu image
						SDL_RenderCopy(renderer, main, NULL, &titlePos);

						//Draw One Player image
						if(players1Pressed)
						{
							SDL_RenderCopy(renderer, playP, NULL, &Players1NPos);
						}
						else if (players1Over)
						{
							SDL_RenderCopy(renderer, playO, NULL, &Players1NPos);
						}
						else
						{
							SDL_RenderCopy(renderer, playN, NULL, &Players1NPos);
						}

						//Draw the cursor image
						cursor.Draw(renderer);


						// SDL Render present
						SDL_RenderPresent(renderer);
					}
				}break;
					case LEVEL:
					{
						alreadyOver = false;
						level = true;
						SDL_ShowCursor(0);

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

						players1Pressed = false;

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
							case SDLK_ESCAPE:
								quit = true;
								level = false;
								break;

							case SDLK_UP:
								player.posRect.y -= 15;
								break;
							case SDLK_DOWN:
								player.posRect.y += 15;
								break;
							case SDLK_LEFT:
								player.posRect.x -= 15;
								break;
							case SDLK_RIGHT:
								player.posRect.x += 15;
								break;

							case SDLK_w:

								player.posRect.y -= 15;
								break;

							case SDLK_s:

								player.posRect.y += 15;
								break;

							case SDLK_d:
								player.posRect.x += 15;
								break;

							case SDLK_a:
								player.posRect.x -= 15;
								break;
							}//END SWITCH KEYDOWN
								break;

							}
							else if(e.type == SDL_MOUSEBUTTONDOWN)

							{
								if(player.playerMagic > 0)
								{
								player.OnMouseButton(e.button);
								player.Fire();
								}
							}else if(e.type == SDL_MOUSEMOTION)
							{
								cursor.MouseMotion(e);
								if(cursor.mouseX > player.posRect.x + player.posRect.w/2)
								{
									player.flip = false;
								}else if(cursor.mouseX < player.posRect.x + player.posRect.w/2)
								{
									player.flip = true;
								}
							}

						}// POLL EVENT

						//UPDATE SECTION
						//update player 1 tank
						player.Update(deltaTime, cursor.cursorRect);

						cursor.Update(deltaTime);


						//move background
						if ((player.posRect.x >= 1024 - player.posRect.w))
						{
							//Adjust position floats based on speed, direction and deltaTime
							X_pos -= (player.speed) * deltaTime;

							if (bkgdRect.x > -2048) {
								//Update bullet position with code to account for precision loss
								bkgdRect.x = (int)(X_pos + 0.5f);

								//move enemy
								//chase1.ChaseMoveX(-player.speed, deltaTime);
//											chase2.ChaseMoveX(-player.speed, deltaTime);
//											chase3.ChaseMoveX(-player.speed, deltaTime);
//											chase4.ChaseMoveX(-player.speed, deltaTime);
//											chase5.ChaseMoveX(-player.speed, deltaTime);
//											chase6.ChaseMoveX(-player.speed, deltaTime);
//											chase7.ChaseMoveX(-player.speed, deltaTime);
//											chase8.ChaseMoveX(-player.speed, deltaTime);
//											chase9.ChaseMoveX(-player.speed, deltaTime);
//											chase10.ChaseMoveX(-player.speed, deltaTime);

								turret1.MoveX(-player.speed, deltaTime);
//											turret2.MoveX(-player.speed, deltaTime);
//											turret3.MoveX(-player.speed, deltaTime);
//											turret4.MoveX(-player.speed, deltaTime);
//											turret5.MoveX(-player.speed, deltaTime);
//											turret6.MoveX(-player.speed, deltaTime);
//											turret7.MoveX(-player.speed, deltaTime);
//											turret8.MoveX(-player.speed, deltaTime);
//											turret9.MoveX(-player.speed, deltaTime);
//											turret10.MoveX(-player.speed, deltaTime);


								//key.MoveX(-player.speed, deltaTime);
								//health.MoveX(-player.speed, deltaTime);
								//magic.MoveX(-player.speed, deltaTime);

								//spirits.MoveX(-player.speed, deltaTime);
								//lights.MoveX(-player.speed, deltaTime);
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
								//chase1.ChaseMoveX(player.speed, deltaTime);
//											chase2.ChaseMoveX(player.speed, deltaTime);
//											chase3.ChaseMoveX(player.speed, deltaTime);
//											chase4.ChaseMoveX(player.speed, deltaTime);
//											chase5.ChaseMoveX(player.speed, deltaTime);
//											chase6.ChaseMoveX(player.speed, deltaTime);
//											chase7.ChaseMoveX(player.speed, deltaTime);
//											chase8.ChaseMoveX(player.speed, deltaTime);
//											chase9.ChaseMoveX(player.speed, deltaTime);
//											chase10.ChaseMoveX(player.speed, deltaTime);

								turret1.MoveX(player.speed, deltaTime);
//											turret2.MoveX(player.speed, deltaTime);
//											turret3.MoveX(player.speed, deltaTime);
//											turret4.MoveX(player.speed, deltaTime);
//											turret5.MoveX(player.speed, deltaTime);
//											turret6.MoveX(player.speed, deltaTime);
//											turret7.MoveX(player.speed, deltaTime);
//											turret8.MoveX(player.speed, deltaTime);
//											turret9.MoveX(player.speed, deltaTime);
//											turret10.MoveX(player.speed, deltaTime);

								//key.MoveX(player.speed, deltaTime);
								//health.MoveX(player.speed, deltaTime);
								//magic.MoveX(player.speed, deltaTime);

								//spirits.MoveX(player.speed, deltaTime);
								//lights.MoveX(player.speed, deltaTime);

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
								//chase1.ChaseMoveY(-player.speed, deltaTime);
//											chase2.ChaseMoveY(-player.speed, deltaTime);
//											chase3.ChaseMoveY(-player.speed, deltaTime);
//											chase4.ChaseMoveY(-player.speed, deltaTime);
//											chase5.ChaseMoveY(-player.speed, deltaTime);
//											chase6.ChaseMoveY(-player.speed, deltaTime);
//											chase7.ChaseMoveY(-player.speed, deltaTime);
//											chase8.ChaseMoveY(-player.speed, deltaTime);
//											chase9.ChaseMoveY(-player.speed, deltaTime);
//											chase10.ChaseMoveY(-player.speed, deltaTime);

								turret1.MoveY(-player.speed, deltaTime);
//											turret2.MoveY(-player.speed, deltaTime);
//											turret3.MoveY(-player.speed, deltaTime);
//											turret4.MoveY(-player.speed, deltaTime);
//											turret5.MoveY(-player.speed, deltaTime);
//											turret6.MoveY(-player.speed, deltaTime);
//											turret7.MoveY(-player.speed, deltaTime);
//											turret8.MoveY(-player.speed, deltaTime);
//											turret9.MoveY(-player.speed, deltaTime);
//											turret10.MoveY(-player.speed, deltaTime);

								//key.MoveY(-player.speed, deltaTime);
								//health.MoveY(-player.speed, deltaTime);
								//magic.MoveY(-player.speed, deltaTime);

								//spirits.MoveY(-player.speed, deltaTime);
								//lights.MoveY(-player.speed, deltaTime);
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
								//chase1.ChaseMoveY(player.speed, deltaTime);
//											chase2.ChaseMoveY(player.speed, deltaTime);
//											chase3.ChaseMoveY(player.speed, deltaTime);
//											chase4.ChaseMoveY(player.speed, deltaTime);
//											chase5.ChaseMoveY(player.speed, deltaTime);
//											chase6.ChaseMoveY(player.speed, deltaTime);
//											chase7.ChaseMoveY(player.speed, deltaTime);
//											chase8.ChaseMoveY(player.speed, deltaTime);
//											chase9.ChaseMoveY(player.speed, deltaTime);
//											chase10.ChaseMoveY(player.speed, deltaTime);

								turret1.MoveY(player.speed, deltaTime);
								//turret2.MoveY(player.speed, deltaTime);
								//turret3.MoveY(player.speed, deltaTime);
								//turret4.MoveY(player.speed, deltaTime);
								//turret5.MoveY(player.speed, deltaTime);
								//turret6.MoveY(player.speed, deltaTime);
								//turret7.MoveY(player.speed, deltaTime);
								//turret8.MoveY(player.speed, deltaTime);
								//turret9.MoveY(player.speed, deltaTime);
								//turret10.MoveY(player.speed, deltaTime);

								//key.MoveY(player.speed, deltaTime);
								//health.MoveY(player.speed, deltaTime);
								//magic.MoveY(player.speed, deltaTime);

								//spirits.MoveY(player.speed, deltaTime);
								//lights.MoveY(player.speed, deltaTime);
							}
							else
							{
								Y_pos = bkgdRect.y;
							}
						}

						//UDPATE ENEMIES*************
						//chase1.Update(deltaTime, player.posRect);

						turret1.Update(deltaTime, player.posRect);

						//check for hit from tanks
						//1
						/*if (SDL_HasIntersection(&player.posRect, &chase1.chaseRect))
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
						}		*/

						//check for hit from turret
										//1
										for (int i = 0; i < turret1.bulletList.size(); i++)
										{
											if (SDL_HasIntersection(&player.posRect, &turret1.bulletList[i].posRect))
											{
												turret1.bulletList[i].Reset();
												player.turretHit();
												//if(player.playerHealth <= 0)
												//{
												//	level = false;
												//	gameState = LOSE;
												//}
											}
										}

										//check if player hit turret
										for (int i = 0; i < player.bulletList.size(); i++)
										{
											//turret1
											if (SDL_HasIntersection(&turret1.baseRect, &player.bulletList[i].posRect))
											{
												//Mix_PlayChannel(-1, kingHit, 0);
												player.bulletList[i].Reset();
												turret1.RemoveHealth();
											}
										}

					//key
/*				if (SDL_HasIntersection(&player.posRect, &key.pickupRect))
					{
					//	Mix_PlayChannel(-1, pickupSound, 0);
						key.active = false;
						key.pickupRect.x = -5000;
						key.pickupRect.y = -5000;
						hasKey = true;
					}
				//health
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
				//magic
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

				}	*/


						//DRAW SECTION
						//Clear the SDL RenderTarget
						SDL_RenderClear(renderer);

						//Draw Background

						SDL_RenderCopy(renderer, Level, NULL, &bkgdRect);

						//spirits.Draw(renderer);

						//lights.Draw(renderer);

						//draw pickupsbkgd
						SDL_RenderCopy(renderer, InvBkgd, NULL, &PickupsbkgdRect);

						if(hasKey == true)
						{
							//SDL_RenderCopy(renderer, keyGUI, NULL, &keypos);
						}

						//Draw key
						if (key.active)
						{
							//key.Draw(renderer);
						}
						if (health.active)
						{
							//health.Draw(renderer);
						}
						if (magic.active)
						{
							//magic.Draw(renderer);
						}

						//Draw player1 tank
						player.Draw(renderer);

						turret1.Draw(renderer);

						//chase1.Draw(renderer);

						cursor.Draw(renderer);

						// SDL Render present
						SDL_RenderPresent(renderer);


						SDL_Delay(16);
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
