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
#endif

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

// code for frame rate independence
float deltaTime = 0.0;
int thisTime = 0;
int lastTime = 0;

int w, h;

// The velocity of the player
int pVelX = 0;
int pVelY = 0;

bool keyup = false, keydown = false, keyleft = false, keyright = false;

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
			keypos.x = 46;
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
			    Players1NPos.x=600;
			    Players1NPos.y=768/2;

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

				//query w and h
				SDL_QueryTexture(playAN,NULL,NULL,&w,&h);
				Players1ANPos.w = w;
				Players1ANPos.h = h;

				SDL_QueryTexture(playAO,NULL,NULL,&w,&h);
				Players1AOPos.w = w;
				Players1AOPos.h = h;

				// set the X,Y,W, and H for the Rectangle
				Players1ANPos.x=1024/2-Players1ANPos.w/2;
				Players1ANPos.y=675;

				Players1AOPos.x=1024/2-Players1AOPos.w/2;
				Players1AOPos.y=667;



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

				  //query w and h
				  SDL_QueryTexture(winText, NULL, NULL, &w, &h);
				  winTextPos.w = w;
				  winTextPos.h = h;

				  // set the X,Y,W, and H for the Rectangle
				  winTextPos.x=1024/2-winTextPos.w/2;
				  winTextPos.y=100;

				  string LoseTextPath = images_dir + "loseText.png";

				  SDL_Texture* loseText=IMG_LoadTexture(renderer, LoseTextPath.c_str());

				  // create SDL Rectangle for the title graphic
				  SDL_Rect loseTextPos;


				  //query w and h
				  SDL_QueryTexture(loseText, NULL, NULL, &w, &h);
				  loseTextPos.w = w;
				  loseTextPos.h = h;

				  // set the X,Y,W, and H for the Rectangle
				  loseTextPos.x=1024/2-loseTextPos.w/2;
				  loseTextPos.y=100;


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
			bool hasCerberus = false;
			bool capture = false;
			bool escape = false;
			bool needHealth = false, needMagic = false;
			bool wardenDead = false;

			//Create pickups**
			Pickup key = Pickup(renderer, images_dir.c_str(), 0, 1950.0f, 615.0f);
			Pickup health1 = Pickup(renderer, images_dir.c_str(), 1, 200.0f, 500.0f);
			Pickup magic1 = Pickup(renderer, images_dir.c_str(), 2, 600.0f, 500.0f);
			Pickup health2 = Pickup(renderer, images_dir.c_str(), 1, 1300.0f, 450.0f);
			Pickup magic2 = Pickup(renderer, images_dir.c_str(), 2, 1500.0f, 950.0f);
			Pickup health3 = Pickup(renderer, images_dir.c_str(), 1, 2250.0f, 500.0f);
			Pickup magic3 = Pickup(renderer, images_dir.c_str(), 2, 2500.0f, 600.0f);
			Pickup health4 = Pickup(renderer, images_dir.c_str(), 1, 2300.0f, 850.0f);
			Pickup magic4 = Pickup(renderer, images_dir.c_str(), 2, 500.0f, -550.0f);
			Pickup health5 = Pickup(renderer, images_dir.c_str(), 1, 150.0f, -250.0f);
			Pickup magic5 = Pickup(renderer, images_dir.c_str(), 2, 350.0f, 1000.0f);

			//*****Secondary-SPIRITS**********
			Pickup spirits = Pickup(renderer, images_dir.c_str(), 3, 64.0f, 1002.0f);
			Pickup lights = Pickup(renderer, images_dir.c_str(), 4, 70.0f, 982.0f);

			//cage
			Pickup cage = Pickup(renderer, images_dir.c_str(), 5, 3003.0f, 92.0f);
			Pickup exit = Pickup(renderer, images_dir.c_str(), 6, 150.0f, 25.0f);

			Pickup cText = Pickup(renderer, images_dir.c_str(), 7, 512.0f-(409/2), 384.0f-(266/2));
			Pickup eText = Pickup(renderer, images_dir.c_str(), 8, 512.0f-(304/2), 384.0f-(162/2));



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
		//Mix_Chunk *overSound = Mix_LoadWAV((audio_dir + "over.wav").c_str());

		//Set up a Sound Effect CHUNK for the button pressed state
		//Mix_Chunk *pressedSound = Mix_LoadWAV((audio_dir + "pressed.wav").c_str());

		//Mix_Chunk *pickupSound = Mix_LoadWAV((audio_dir + "itemPickup.wav").c_str());

		//Mix_Chunk *guardHit = Mix_LoadWAV((audio_dir + "guardhit.wav").c_str());

		//Mix_Chunk *kingHit = Mix_LoadWAV((audio_dir + "kinghit.wav").c_str());


		//********CREATE CURSOR BEGIN**********
		Cursor cursor(renderer, images_dir.c_str(), 300.0f, 50.0f);
		//********CREATE CURSOR FINISH*********

		//******Create Player**************
		Player player = Player(renderer, 0, images_dir.c_str(),audio_dir.c_str(), 250.0f, 75.0f);

		//********Create Enemy Turrets START**********
		//*********Enemy Turrets END***********
		Turret turret1 = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 0, 650.0f, 400.0f);
		Turret turret2 = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 0, 850.0f, -650.0f);
		Turret turret3 = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 0, 800.0f, 875.0f);
		Turret turret4 = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 0, 1950.0f, -660.0f);
		Turret turret5 = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 0, 1200.0f, 1075.0f);
		Turret turret6 = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 0, 2450.0f, -300.0f);
		Turret turret7 = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 0, 2400.0f, 325.0f);
		Turret turret8 = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 0, 2850.0f, 600.0f);
		Turret turret9 = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 0, 2150.0f, 975.0f);

		Turret SoulWarden = Turret(renderer, images_dir.c_str(), audio_dir.c_str(), 1, 1875.0f, 550.0f);

		//********Create Enemy Chase START****************
		Chase chase1 = Chase(renderer, images_dir.c_str(), audio_dir.c_str(), 450.0f, -550.0f);
		Chase chase2 = Chase(renderer, images_dir.c_str(), audio_dir.c_str(), 950.0f, 75.0f);
		Chase chase3 = Chase(renderer, images_dir.c_str(), audio_dir.c_str(), 300.0f, 675.0f);
		Chase chase4 = Chase(renderer, images_dir.c_str(), audio_dir.c_str(), 400.0f, 1200.0f);
		Chase chase5 = Chase(renderer, images_dir.c_str(), audio_dir.c_str(), 1375.0f, -250.0f);
		Chase chase6 = Chase(renderer, images_dir.c_str(), audio_dir.c_str(), 1425.0f, 300.0f);
		Chase chase7 = Chase(renderer, images_dir.c_str(), audio_dir.c_str(), 1500.0f, 850.0f);
		Chase chase8 = Chase(renderer, images_dir.c_str(), audio_dir.c_str(), 2850.0f, -700.0f);
		Chase chase9 = Chase(renderer, images_dir.c_str(), audio_dir.c_str(), 2650.0f, 100.0f);
		Chase chase10 = Chase(renderer, images_dir.c_str(), audio_dir.c_str(), 2400.0f, 1150.0f);
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
						key.active = false;
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
							else if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
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
								//player.posRect.y -= 15;
								pVelY -= player.speed;
								keyup = true;
								break;
							case SDLK_DOWN:
								//player.posRect.y += 15;
								pVelY += player.speed;
								keydown = true;
								break;
							case SDLK_LEFT:
								//player.posRect.x -= 15;
								pVelX -= player.speed;
								keyleft = true;
								break;
							case SDLK_RIGHT:
								//player.posRect.x += 15;
								pVelX += player.speed;
								keyright = true;
								break;

							case SDLK_w:

								//player.posRect.y -= 15;
								pVelY -= player.speed;
								keyup = true;
								break;

							case SDLK_s:

								//player.posRect.y += 15;
								pVelY += player.speed;
								keydown = true;
								break;

							case SDLK_d:
								//player.posRect.x += 15;
								pVelX += player.speed;
								keyright = true;
								break;

							case SDLK_a:
								//player.posRect.x -= 15;
								pVelX -= player.speed;
								keyleft = true;
								break;

							case SDLK_c:
								if(capture == true)
								{
									cage.active = false;
									capture = false;
									hasCerberus = true;
								}
								break;

							case SDLK_e:
								if(escape == true)
								{
									hasCerberus = false;
									hasKey = false;
									player.Reset();
									chase1.alive = true;
									chase2.alive = true;
									chase3.alive = true;
									chase4.alive = true;
									chase5.alive = true;
									chase6.alive = true;
									chase7.alive = true;
									chase8.alive = true;
									chase9.alive = true;
									chase10.alive = true;
									turret1.active = true;
									turret2.active = true;
									turret3.active = true;
									turret4.active = true;
									turret5.active = true;
									turret6.active = true;
									turret7.active = true;
									turret8.active = true;
									turret9.active = true;
									SoulWarden.active = true;
									cage.active = true;
									win = true;
									level = false;
									gameState = WIN;

								}
								break;
							}//END SWITCH KEYDOWN
								break;

							}
							else if(e.type == SDL_KEYUP && e.key.repeat == 0)
							{
								switch (e.key.keysym.sym)
								{
								case SDLK_UP:
									pVelY += player.speed;
									keyup = false;
									break;
								case SDLK_DOWN:
									pVelY -= player.speed;
									keydown = false;
									break;
								case SDLK_LEFT:
									pVelX += player.speed;
									keyleft = false;
									break;
								case SDLK_RIGHT:
									pVelX -= player.speed;
									keyright = false;
									break;

								case SDLK_w:
									pVelY += player.speed;
									keyup = false;
									break;

								case SDLK_s:
									pVelY -= player.speed;
									keydown = false;
									break;

								case SDLK_d:
									pVelX -= player.speed;
									keyright = false;
									break;

								case SDLK_a:
									pVelX += player.speed;
									keyleft = false;
									break;
								}//END SWITCH KEYUP
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
							}

						}// POLL EVENT

						//UPDATE SECTION
						//update player 1
						player.posRect.x += pVelX / 40;

						player.posRect.y += pVelY / 40;
						player.Update(deltaTime, cursor.cursorRect);

						cursor.Update(deltaTime);

						if(cursor.oldMouseX > player.posRect.x + player.posRect.w/2)
						{
							player.flip = false;
						}else if(cursor.oldMouseX < player.posRect.x + player.posRect.w/2)
						{
							player.flip = true;
						}

						if(player.playerMagic <= 75)
						{
							needMagic = true;
							magic1.active = true;
							magic2.active = true;
							magic3.active = true;
							magic4.active = true;
							magic5.active = true;
						}

						if(player.playerHealth <= 75)
						{
							needHealth = true;
							health1.active = true;
							health2.active = true;
							health3.active = true;
							health4.active = true;
							health5.active = true;
						}

						if(wardenDead)
						{
							key.active = true;
						}

						//move background
						if ((player.posRect.x >= 1024 - player.posRect.w) && keyright == true)
						{
							//Adjust position floats based on speed, direction and deltaTime
							X_pos -= (player.speed) * deltaTime;

							if (bkgdRect.x > -2048) {
								//Update bullet position with code to account for precision loss
								bkgdRect.x = (int)(X_pos + 0.5f);

								//move enemy
								chase1.ChaseMoveX(-player.speed, deltaTime);
								chase2.ChaseMoveX(-player.speed, deltaTime);
								chase3.ChaseMoveX(-player.speed, deltaTime);
								chase4.ChaseMoveX(-player.speed, deltaTime);
								chase5.ChaseMoveX(-player.speed, deltaTime);
								chase6.ChaseMoveX(-player.speed, deltaTime);
								chase7.ChaseMoveX(-player.speed, deltaTime);
								chase8.ChaseMoveX(-player.speed, deltaTime);
								chase9.ChaseMoveX(-player.speed, deltaTime);
								chase10.ChaseMoveX(-player.speed, deltaTime);

								turret1.MoveX(-player.speed, deltaTime);
								turret2.MoveX(-player.speed, deltaTime);
								turret3.MoveX(-player.speed, deltaTime);
								turret4.MoveX(-player.speed, deltaTime);
								turret5.MoveX(-player.speed, deltaTime);
								turret6.MoveX(-player.speed, deltaTime);
								turret7.MoveX(-player.speed, deltaTime);
								turret8.MoveX(-player.speed, deltaTime);
								turret9.MoveX(-player.speed, deltaTime);
								SoulWarden.MoveX(-player.speed, deltaTime);


								key.MoveX(-player.speed, deltaTime);
								health1.MoveX(-player.speed, deltaTime);
								magic1.MoveX(-player.speed, deltaTime);
								health2.MoveX(-player.speed, deltaTime);
								magic2.MoveX(-player.speed, deltaTime);
								health3.MoveX(-player.speed, deltaTime);
								magic3.MoveX(-player.speed, deltaTime);
								health4.MoveX(-player.speed, deltaTime);
								magic4.MoveX(-player.speed, deltaTime);
								health5.MoveX(-player.speed, deltaTime);
								magic5.MoveX(-player.speed, deltaTime);

								spirits.MoveX(-player.speed, deltaTime);
								lights.MoveX(-player.speed, deltaTime);
								cage.MoveX(-player.speed, deltaTime);
								exit.MoveX(-player.speed, deltaTime);
							}
							else
							{
								X_pos = bkgdRect.x;
							}
						}
						if ((player.posRect.x <= 0) && keyleft == true)
						{
							X_pos += (player.speed) * deltaTime;

							if (bkgdRect.x < 0) {
								//Update bullet position with code to account for precision loss
								bkgdRect.x = (int)(X_pos + 0.5f);

								//move enemy tank
								chase1.ChaseMoveX(player.speed, deltaTime);
								chase2.ChaseMoveX(player.speed, deltaTime);
								chase3.ChaseMoveX(player.speed, deltaTime);
								chase4.ChaseMoveX(player.speed, deltaTime);
								chase5.ChaseMoveX(player.speed, deltaTime);
								chase6.ChaseMoveX(player.speed, deltaTime);
								chase7.ChaseMoveX(player.speed, deltaTime);
								chase8.ChaseMoveX(player.speed, deltaTime);
								chase9.ChaseMoveX(player.speed, deltaTime);
								chase10.ChaseMoveX(player.speed, deltaTime);

								turret1.MoveX(player.speed, deltaTime);
								turret2.MoveX(player.speed, deltaTime);
								turret3.MoveX(player.speed, deltaTime);
								turret4.MoveX(player.speed, deltaTime);
								turret5.MoveX(player.speed, deltaTime);
								turret6.MoveX(player.speed, deltaTime);
								turret7.MoveX(player.speed, deltaTime);
								turret8.MoveX(player.speed, deltaTime);
								turret9.MoveX(player.speed, deltaTime);
								SoulWarden.MoveX(player.speed, deltaTime);

								key.MoveX(player.speed, deltaTime);
								health1.MoveX(player.speed, deltaTime);
								magic1.MoveX(player.speed, deltaTime);
								health2.MoveX(player.speed, deltaTime);
								magic2.MoveX(player.speed, deltaTime);
								health3.MoveX(player.speed, deltaTime);
								magic3.MoveX(player.speed, deltaTime);
								health4.MoveX(player.speed, deltaTime);
								magic4.MoveX(player.speed, deltaTime);
								health5.MoveX(player.speed, deltaTime);
								magic5.MoveX(player.speed, deltaTime);

								spirits.MoveX(player.speed, deltaTime);
								lights.MoveX(player.speed, deltaTime);
								cage.MoveX(player.speed, deltaTime);
								exit.MoveX(player.speed, deltaTime);

							}
							else
							{
								X_pos = bkgdRect.x;
							}
						}

						if ((player.posRect.y >= 768 - player.posRect.h) && keydown == true)
						{
							//Adjust position floats based on speed, direction and deltaTime
							Y_pos -= (player.speed) * deltaTime;

							if (bkgdRect.y > -1536) {
								//Update bullet position with code to account for precision loss
								bkgdRect.y = (int)(Y_pos + 0.5f);

								//move enemy tank
								chase1.ChaseMoveY(-player.speed, deltaTime);
								chase2.ChaseMoveY(-player.speed, deltaTime);
								chase3.ChaseMoveY(-player.speed, deltaTime);
								chase4.ChaseMoveY(-player.speed, deltaTime);
								chase5.ChaseMoveY(-player.speed, deltaTime);
								chase6.ChaseMoveY(-player.speed, deltaTime);
								chase7.ChaseMoveY(-player.speed, deltaTime);
								chase8.ChaseMoveY(-player.speed, deltaTime);
								chase9.ChaseMoveY(-player.speed, deltaTime);
								chase10.ChaseMoveY(-player.speed, deltaTime);

								turret1.MoveY(-player.speed, deltaTime);
								turret2.MoveY(-player.speed, deltaTime);
								turret3.MoveY(-player.speed, deltaTime);
								turret4.MoveY(-player.speed, deltaTime);
								turret5.MoveY(-player.speed, deltaTime);
								turret6.MoveY(-player.speed, deltaTime);
								turret7.MoveY(-player.speed, deltaTime);
								turret8.MoveY(-player.speed, deltaTime);
								turret9.MoveY(-player.speed, deltaTime);
								SoulWarden.MoveY(-player.speed, deltaTime);

								key.MoveY(-player.speed, deltaTime);
								health1.MoveY(-player.speed, deltaTime);
								magic1.MoveY(-player.speed, deltaTime);
								health2.MoveY(-player.speed, deltaTime);
								magic2.MoveY(-player.speed, deltaTime);
								health3.MoveY(-player.speed, deltaTime);
								magic3.MoveY(-player.speed, deltaTime);
								health4.MoveY(-player.speed, deltaTime);
								magic4.MoveY(-player.speed, deltaTime);
								health5.MoveY(-player.speed, deltaTime);
								magic5.MoveY(-player.speed, deltaTime);

								spirits.MoveY(-player.speed, deltaTime);
								lights.MoveY(-player.speed, deltaTime);
								cage.MoveY(-player.speed, deltaTime);
								exit.MoveY(-player.speed, deltaTime);
					}
							else
							{
								Y_pos = bkgdRect.y;
							}
						}
						if ((player.posRect.y <= 0) && keyup == true)
						{
							Y_pos += (player.speed) * deltaTime;

							if (bkgdRect.y < 0) {
								//Update bullet position with code to account for precision loss
								bkgdRect.y = (int)(Y_pos + 0.5f);

								//move enemy chase
								chase1.ChaseMoveY(player.speed, deltaTime);
								chase2.ChaseMoveY(player.speed, deltaTime);
								chase3.ChaseMoveY(player.speed, deltaTime);
								chase4.ChaseMoveY(player.speed, deltaTime);
								chase5.ChaseMoveY(player.speed, deltaTime);
								chase6.ChaseMoveY(player.speed, deltaTime);
								chase7.ChaseMoveY(player.speed, deltaTime);
								chase8.ChaseMoveY(player.speed, deltaTime);
								chase9.ChaseMoveY(player.speed, deltaTime);
								chase10.ChaseMoveY(player.speed, deltaTime);

								turret1.MoveY(player.speed, deltaTime);
								turret2.MoveY(player.speed, deltaTime);
								turret3.MoveY(player.speed, deltaTime);
								turret4.MoveY(player.speed, deltaTime);
								turret5.MoveY(player.speed, deltaTime);
								turret6.MoveY(player.speed, deltaTime);
								turret7.MoveY(player.speed, deltaTime);
								turret8.MoveY(player.speed, deltaTime);
								turret9.MoveY(player.speed, deltaTime);
								SoulWarden.MoveY(player.speed, deltaTime);

								key.MoveY(player.speed, deltaTime);
								health1.MoveY(player.speed, deltaTime);
								magic1.MoveY(player.speed, deltaTime);
								health2.MoveY(player.speed, deltaTime);
								magic2.MoveY(player.speed, deltaTime);
								health3.MoveY(player.speed, deltaTime);
								magic3.MoveY(player.speed, deltaTime);
								health4.MoveY(player.speed, deltaTime);
								magic4.MoveY(player.speed, deltaTime);
								health5.MoveY(player.speed, deltaTime);
								magic5.MoveY(player.speed, deltaTime);

								spirits.MoveY(player.speed, deltaTime);
								lights.MoveY(player.speed, deltaTime);
								cage.MoveY(player.speed, deltaTime);
								exit.MoveY(player.speed, deltaTime);
							}
							else
							{
								Y_pos = bkgdRect.y;
							}
						}

						//UDPATE ENEMIES*************
						chase1.Update(deltaTime, player.posRect);
						chase2.Update(deltaTime, player.posRect);
						chase3.Update(deltaTime, player.posRect);
						chase4.Update(deltaTime, player.posRect);
						chase5.Update(deltaTime, player.posRect);
						chase6.Update(deltaTime, player.posRect);
						chase7.Update(deltaTime, player.posRect);
						chase8.Update(deltaTime, player.posRect);
						chase9.Update(deltaTime, player.posRect);
						chase10.Update(deltaTime, player.posRect);

						turret1.Update(deltaTime, player.posRect);
						turret2.Update(deltaTime, player.posRect);
						turret3.Update(deltaTime, player.posRect);
						turret4.Update(deltaTime, player.posRect);
						turret5.Update(deltaTime, player.posRect);
						turret6.Update(deltaTime, player.posRect);
						turret7.Update(deltaTime, player.posRect);
						turret8.Update(deltaTime, player.posRect);
						turret9.Update(deltaTime, player.posRect);
						SoulWarden.Update(deltaTime, player.posRect);

						//check for hit from tanks
						//1
						if(chase1.alive)
						{
						if (SDL_HasIntersection(&player.posRect, &chase1.chaseRect))
						{
							player.chaseHit();
							if (player.playerHealth <= 0)
							{
								level = false;
								player.Reset();
								gameState = LOSE;
							}
						}
						}
						//2
						if(chase2.alive)
						{
						if (SDL_HasIntersection(&player.posRect, &chase2.chaseRect))
						{
							player.chaseHit();
							if (player.playerHealth <= 0)
							{
								level = false;
								player.Reset();
								gameState = LOSE;
							}
						}
						}
						//3
						if(chase3.alive)
						{
						if (SDL_HasIntersection(&player.posRect, &chase3.chaseRect))
						{
							player.chaseHit();
							if (player.playerHealth <= 0)
							{
								level = false;
								player.Reset();
								gameState = LOSE;
							}
						}
						}
						//4
						if(chase4.alive)
						{
						if (SDL_HasIntersection(&player.posRect, &chase4.chaseRect))
						{
							player.chaseHit();
							if (player.playerHealth <= 0)
							{
								level = false;
								player.Reset();
								gameState = LOSE;
							}
						}
						}
						//5
						if(chase5.alive)
						{
						if (SDL_HasIntersection(&player.posRect, &chase5.chaseRect))
						{
							player.chaseHit();
							if (player.playerHealth <= 0)
							{
								level = false;
								player.Reset();
								gameState = LOSE;
							}
						}
						}
						//6
						if(chase6.alive)
						{
						if (SDL_HasIntersection(&player.posRect, &chase6.chaseRect))
						{
							player.chaseHit();
							if (player.playerHealth <= 0)
							{
								level = false;
								player.Reset();
								gameState = LOSE;
							}
						}
						}
						//7
						if(chase7.alive)
						{
						if (SDL_HasIntersection(&player.posRect, &chase7.chaseRect))
						{
							player.chaseHit();
							if (player.playerHealth <= 0)
							{
								level = false;
								player.Reset();
								gameState = LOSE;
							}
						}
						}
						//8
						if(chase8.alive)
						{
						if (SDL_HasIntersection(&player.posRect, &chase8.chaseRect))
						{
							player.chaseHit();
							if (player.playerHealth <= 0)
							{
								level = false;
								player.Reset();
								gameState = LOSE;
							}
						}
						}
						//9
						if(chase9.alive)
						{
						if (SDL_HasIntersection(&player.posRect, &chase9.chaseRect))
						{
							player.chaseHit();
							if (player.playerHealth <= 0)
							{
								level = false;
								player.Reset();
								gameState = LOSE;
							}
						}
						}
						//10
						if(chase10.alive)
						{
						if (SDL_HasIntersection(&player.posRect, &chase10.chaseRect))
						{
							player.chaseHit();
							if (player.playerHealth <= 0)
							{
								level = false;
								player.Reset();
								gameState = LOSE;
							}
						}
						}

						//check if player hit chase
						for (int i = 0; i < player.bulletList.size(); i++)
						{
							//chase
							//1
							if(chase1.alive)
							{
							if (SDL_HasIntersection(&chase1.chaseRect, &player.bulletList[i].posRect))
							{
								//Mix_PlayChannel(-1, guardHit, 0);
								player.bulletList[i].Reset();
								if(chase1.active == true)
								{
									chase1.RemoveHealth();
								}
							}
							}
							//2
							if(chase2.alive)
							{
							if (SDL_HasIntersection(&chase2.chaseRect, &player.bulletList[i].posRect))
							{
								//Mix_PlayChannel(-1, guardHit, 0);
								player.bulletList[i].Reset();
								if(chase2.active == true)
								{
									chase2.RemoveHealth();
								}
							}
							}
							//3
							if(chase3.alive)
							{
							if (SDL_HasIntersection(&chase3.chaseRect, &player.bulletList[i].posRect))
							{
								//Mix_PlayChannel(-1, guardHit, 0);
								player.bulletList[i].Reset();
								if(chase3.active == true)
								{
									chase3.RemoveHealth();
								}
							}
							}
							//4
							if(chase4.alive)
							{
							if (SDL_HasIntersection(&chase4.chaseRect, &player.bulletList[i].posRect))
							{
								//Mix_PlayChannel(-1, guardHit, 0);
								player.bulletList[i].Reset();
								if(chase4.active == true)
								{
									chase4.RemoveHealth();
								}
							}
							}
							//5
							if(chase5.alive)
							{
							if (SDL_HasIntersection(&chase5.chaseRect, &player.bulletList[i].posRect))
							{
								//Mix_PlayChannel(-1, guardHit, 0);
								player.bulletList[i].Reset();
								if(chase5.active == true)
								{
									chase5.RemoveHealth();
								}
							}
							}
							//6
							if(chase6.alive)
							{
							if (SDL_HasIntersection(&chase6.chaseRect, &player.bulletList[i].posRect))
							{
								//Mix_PlayChannel(-1, guardHit, 0);
								player.bulletList[i].Reset();
								if(chase6.active == true)
								{
									chase6.RemoveHealth();
								}
							}
							}
							//7
							if(chase7.alive)
							{
							if (SDL_HasIntersection(&chase7.chaseRect, &player.bulletList[i].posRect))
							{
								//Mix_PlayChannel(-1, guardHit, 0);
								player.bulletList[i].Reset();
								if(chase7.active == true)
								{
									chase7.RemoveHealth();
								}
							}
							}
							//8
							if(chase8.alive)
							{
							if (SDL_HasIntersection(&chase8.chaseRect, &player.bulletList[i].posRect))
							{
								//Mix_PlayChannel(-1, guardHit, 0);
								player.bulletList[i].Reset();
								if(chase8.active == true)
								{
									chase8.RemoveHealth();
								}
							}
							}
							//9
							if(chase9.alive)
							{
							if (SDL_HasIntersection(&chase9.chaseRect, &player.bulletList[i].posRect))
							{
								//Mix_PlayChannel(-1, guardHit, 0);
								player.bulletList[i].Reset();
								if(chase9.active == true)
								{
									chase9.RemoveHealth();
								}
							}
							}
							//10
							if(chase10.alive)
							{
							if (SDL_HasIntersection(&chase10.chaseRect, &player.bulletList[i].posRect))
							{
								//Mix_PlayChannel(-1, guardHit, 0);
								player.bulletList[i].Reset();
								if(chase10.active == true)
								{
									chase10.RemoveHealth();
								}
							}
							}
						}

						//check for hit from turret
						//1
						if(turret1.active)
						{
						for (int i = 0; i < turret1.bulletList.size(); i++)
						{
							if (SDL_HasIntersection(&player.posRect, &turret1.bulletList[i].posRect))
							{
								turret1.bulletList[i].Reset();
								player.turretHit();
								if(player.playerHealth <= 0)
								{
									player.Reset();
									level = false;
									gameState = LOSE;
								}
							}
						}
						}
						//2
						if(turret2.active)
						{
						for (int i = 0; i < turret2.bulletList.size(); i++)
						{
							if (SDL_HasIntersection(&player.posRect, &turret2.bulletList[i].posRect))
							{
								turret2.bulletList[i].Reset();
								player.turretHit();
								if(player.playerHealth <= 0)
								{
									player.Reset();
									level = false;
									gameState = LOSE;
								}
							}
						}
						}
						//3
						if(turret3.active)
						{
						for (int i = 0; i < turret3.bulletList.size(); i++)
						{
							if (SDL_HasIntersection(&player.posRect, &turret3.bulletList[i].posRect))
							{
								turret3.bulletList[i].Reset();
								player.turretHit();
								if(player.playerHealth <= 0)
								{
									player.Reset();
									level = false;
									gameState = LOSE;
								}
							}
						}
						}
						//4
						if(turret4.active)
						{
						for (int i = 0; i < turret4.bulletList.size(); i++)
						{
							if (SDL_HasIntersection(&player.posRect, &turret4.bulletList[i].posRect))
							{
								turret4.bulletList[i].Reset();
								player.turretHit();
								if(player.playerHealth <= 0)
								{
									player.Reset();
									level = false;
									gameState = LOSE;
								}
							}
						}
						}
						//5
						if(turret5.active)
						{
						for (int i = 0; i < turret5.bulletList.size(); i++)
						{
							if (SDL_HasIntersection(&player.posRect, &turret5.bulletList[i].posRect))
							{
								turret5.bulletList[i].Reset();
								player.turretHit();
								if(player.playerHealth <= 0)
								{
									player.Reset();
									level = false;
									gameState = LOSE;
								}
							}
						}
						}
						//6
						if(turret6.active)
						{
						for (int i = 0; i < turret6.bulletList.size(); i++)
						{
							if (SDL_HasIntersection(&player.posRect, &turret6.bulletList[i].posRect))
							{
								turret6.bulletList[i].Reset();
								player.turretHit();
								if(player.playerHealth <= 0)
								{
									player.Reset();
									level = false;
									gameState = LOSE;
								}
							}
						}
						}
						//7
						if(turret7.active)
						{
						for (int i = 0; i < turret7.bulletList.size(); i++)
						{
							if (SDL_HasIntersection(&player.posRect, &turret7.bulletList[i].posRect))
							{
								turret7.bulletList[i].Reset();
								player.turretHit();
								if(player.playerHealth <= 0)
								{
									player.Reset();
									level = false;
									gameState = LOSE;
								}
							}
						}
						}
						//8
						if(turret8.active)
						{
						for (int i = 0; i < turret8.bulletList.size(); i++)
						{
							if (SDL_HasIntersection(&player.posRect, &turret8.bulletList[i].posRect))
							{
								turret8.bulletList[i].Reset();
								player.turretHit();
								if(player.playerHealth <= 0)
								{
									player.Reset();
									level = false;
									gameState = LOSE;
								}
							}
						}
						}
						//9
						if(turret9.active)
						{
						for (int i = 0; i < turret9.bulletList.size(); i++)
						{
							if (SDL_HasIntersection(&player.posRect, &turret9.bulletList[i].posRect))
							{
								turret9.bulletList[i].Reset();
								player.turretHit();
								if(player.playerHealth <= 0)
								{
									player.Reset();
									level = false;
									gameState = LOSE;
								}
							}
						}
						}
						//Warden
						if(SoulWarden.active)
						{
						for (int i = 0; i < SoulWarden.bulletList.size(); i++)
						{
							if (SDL_HasIntersection(&player.posRect, &SoulWarden.bulletList[i].posRect))
							{
								SoulWarden.bulletList[i].Reset();
								player.wardenHit();
								if(player.playerHealth <= 0)
								{
									player.Reset();
									level = false;
									gameState = LOSE;
								}
							}
						}
						}

						//check if player hit turret
						for (int i = 0; i < player.bulletList.size(); i++)
						{
							//turret1
							if(turret1.active)
							{
							if (SDL_HasIntersection(&turret1.baseRect, &player.bulletList[i].posRect))
							{
								//Mix_PlayChannel(-1, kingHit, 0);
								player.bulletList[i].Reset();
								turret1.RemoveHealth();
							}
							}
							//turret2
							if(turret2.active)
							{
							if (SDL_HasIntersection(&turret2.baseRect, &player.bulletList[i].posRect))
							{
								//Mix_PlayChannel(-1, kingHit, 0);
								player.bulletList[i].Reset();
								turret2.RemoveHealth();
							}
							}
							//turret3
							if(turret3.active)
							{
							if (SDL_HasIntersection(&turret3.baseRect, &player.bulletList[i].posRect))
							{
								//Mix_PlayChannel(-1, kingHit, 0);
								player.bulletList[i].Reset();
								turret3.RemoveHealth();
							}
							}
							//turret4
							if(turret4.active)
							{
							if (SDL_HasIntersection(&turret4.baseRect, &player.bulletList[i].posRect))
							{
								//Mix_PlayChannel(-1, kingHit, 0);
								player.bulletList[i].Reset();
								turret4.RemoveHealth();
							}
							}
							//turret5
							if(turret5.active)
							{
							if (SDL_HasIntersection(&turret5.baseRect, &player.bulletList[i].posRect))
							{
								//Mix_PlayChannel(-1, kingHit, 0);
								player.bulletList[i].Reset();
								turret5.RemoveHealth();
							}
							}
							//turret6
							if(turret6.active)
							{
							if (SDL_HasIntersection(&turret6.baseRect, &player.bulletList[i].posRect))
							{
								//Mix_PlayChannel(-1, kingHit, 0);
								player.bulletList[i].Reset();
								turret6.RemoveHealth();
							}
							}
							//turret7
							if(turret7.active)
							{
							if (SDL_HasIntersection(&turret7.baseRect, &player.bulletList[i].posRect))
							{
								//Mix_PlayChannel(-1, kingHit, 0);
								player.bulletList[i].Reset();
								turret7.RemoveHealth();
							}
							}
							//turret8
							if(turret8.active)
							{
							if (SDL_HasIntersection(&turret8.baseRect, &player.bulletList[i].posRect))
							{
								//Mix_PlayChannel(-1, kingHit, 0);
								player.bulletList[i].Reset();
								turret8.RemoveHealth();
							}
							}
							//turret9
							if(turret9.active)
							{
							if (SDL_HasIntersection(&turret9.baseRect, &player.bulletList[i].posRect))
							{
								//Mix_PlayChannel(-1, kingHit, 0);
								player.bulletList[i].Reset();
								turret9.RemoveHealth();
							}
							}
							//Warden
							if(SoulWarden.active)
							{
							if (SDL_HasIntersection(&SoulWarden.baseRect, &player.bulletList[i].posRect))
							{
								//Mix_PlayChannel(-1, kingHit, 0);
								player.bulletList[i].Reset();
								SoulWarden.health --;
								if(SoulWarden.health <= 0)
								{
									wardenDead = true;
									SoulWarden.Reset();
								}

							}
							}
						}

					//key
			if(key.active)
			{
				if (SDL_HasIntersection(&player.posRect, &key.pickupRect))
					{
					//	Mix_PlayChannel(-1, pickupSound, 0);
						key.active = false;
						wardenDead = false;
						key.pickupRect.x = -5000;
						key.pickupRect.y = -5000;
						hasKey = true;
					}
			}

			if(needHealth == true)
			{
				//health1
				if (SDL_HasIntersection(&player.posRect, &health1.pickupRect))
				{
				//	Mix_PlayChannel(-1, pickupSound, 0);
					health1.active = false;
					player.playerHealth += 25;
					if(player.playerHealth >= 100)
					{
						player.playerHealth = 100;
					}
					if(player.playerHealth > 75)
					{
						needHealth = false;
					}
					player.healthR.w = player.playerHealth/player.maxHealth * 147;
				}
				//health2
				if (SDL_HasIntersection(&player.posRect, &health2.pickupRect))
				{
				//	Mix_PlayChannel(-1, pickupSound, 0);
					health2.active = false;
					player.playerHealth += 25;
					if(player.playerHealth >= 100)
					{
						player.playerHealth = 100;
					}
					if(player.playerHealth > 75)
					{
						needHealth = false;
					}
					player.healthR.w = player.playerHealth/player.maxHealth * 147;
				}
				//health3
				if (SDL_HasIntersection(&player.posRect, &health3.pickupRect))
				{
				//	Mix_PlayChannel(-1, pickupSound, 0);
					health3.active = false;
					player.playerHealth += 25;
					if(player.playerHealth >= 100)
					{
						player.playerHealth = 100;
					}
					if(player.playerHealth > 75)
					{
						needHealth = false;
					}
					player.healthR.w = player.playerHealth/player.maxHealth * 147;
				}
				//health4
				if (SDL_HasIntersection(&player.posRect, &health4.pickupRect))
				{
				//	Mix_PlayChannel(-1, pickupSound, 0);
					health4.active = false;
					player.playerHealth += 25;
					if(player.playerHealth >= 100)
					{
						player.playerHealth = 100;
					}
					if(player.playerHealth > 75)
					{
						needHealth = false;
					}
					player.healthR.w = player.playerHealth/player.maxHealth * 147;
				}
				//health5
				if (SDL_HasIntersection(&player.posRect, &health5.pickupRect))
				{
				//	Mix_PlayChannel(-1, pickupSound, 0);
					health5.active = false;
					player.playerHealth += 25;
					if(player.playerHealth >= 100)
					{
						player.playerHealth = 100;
					}
					if(player.playerHealth > 75)
					{
						needHealth = false;
					}
					player.healthR.w = player.playerHealth/player.maxHealth * 147;
				}
			}

			if(needMagic == true)
			{
				//magic1
				if (SDL_HasIntersection(&player.posRect, &magic1.pickupRect))
				{
				//	Mix_PlayChannel(-1, pickupSound, 0);
					magic1.active = false;
					player.playerMagic += 25;
					if(player.playerMagic >= 100)
					{
						player.playerMagic = 100;
					}
					if(player.playerMagic > 75)
					{
						needMagic = false;
					}
					player.magicR.w = player.playerMagic/player.maxMagic * 147;
				}
				//magic2
				if (SDL_HasIntersection(&player.posRect, &magic2.pickupRect))
				{
				//	Mix_PlayChannel(-1, pickupSound, 0);
					magic2.active = false;
					player.playerMagic += 25;
					if(player.playerMagic >= 100)
					{
						player.playerMagic = 100;
					}
					if(player.playerMagic > 75)
					{
						needMagic = false;
					}
					player.magicR.w = player.playerMagic/player.maxMagic * 147;
				}
				//magic3
				if (SDL_HasIntersection(&player.posRect, &magic3.pickupRect))
				{
				//	Mix_PlayChannel(-1, pickupSound, 0);
					magic3.active = false;
					player.playerMagic += 25;
					if(player.playerMagic >= 100)
					{
						player.playerMagic = 100;
					}
					if(player.playerMagic > 75)
					{
						needMagic = false;
					}
					player.magicR.w = player.playerMagic/player.maxMagic * 147;
				}
				//magic4
				if (SDL_HasIntersection(&player.posRect, &magic4.pickupRect))
				{
				//	Mix_PlayChannel(-1, pickupSound, 0);
					magic4.active = false;
					player.playerMagic += 25;
					if(player.playerMagic >= 100)
					{
						player.playerMagic = 100;
					}
					if(player.playerMagic > 75)
					{
						needMagic = false;
					}
					player.magicR.w = player.playerMagic/player.maxMagic * 147;
				}
				//magic5
				if (SDL_HasIntersection(&player.posRect, &magic5.pickupRect))
				{
				//	Mix_PlayChannel(-1, pickupSound, 0);
					magic5.active = false;
					player.playerMagic += 25;
					if(player.playerMagic >= 100)
					{
						player.playerMagic = 100;
					}
					if(player.playerMagic > 75)
					{
						needMagic = false;
					}
					player.magicR.w = player.playerMagic/player.maxMagic * 147;
				}
			}
						if(hasKey == true && cage.active == true)
						{
						capture = SDL_HasIntersection(&player.posRect, &cage.pickupRect);
						}

						if(hasCerberus == true)
						{
						escape = SDL_HasIntersection(&player.posRect, &exit.pickupRect);
						}


						//DRAW SECTION
						//Clear the SDL RenderTarget
						SDL_RenderClear(renderer);

						//Draw Background

						SDL_RenderCopy(renderer, Level, NULL, &bkgdRect);

						spirits.Draw(renderer);

						lights.Draw(renderer);

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

						if(needHealth == true)
						{
						if (health1.active)
						{
							health1.Draw(renderer);
						}
						if (health2.active)
						{
							health2.Draw(renderer);
						}
						if (health3.active)
						{
							health3.Draw(renderer);
						}
						if (health4.active)
						{
							health4.Draw(renderer);
						}
						if (health5.active)
						{
							health5.Draw(renderer);
						}
						}

						if(needMagic == true)
						{
						if (magic1.active)
						{
							magic1.Draw(renderer);
						}
						if (magic2.active)
						{
							magic2.Draw(renderer);
						}
						if (magic3.active)
						{
							magic3.Draw(renderer);
						}
						if (magic4.active)
						{
							magic4.Draw(renderer);
						}
						if (magic5.active)
						{
							magic5.Draw(renderer);
						}
						}

						if(cage.active)
						{
							cage.Draw(renderer);
						}

						if(capture)
						{
							cText.Draw(renderer);
						}

						if(escape)
						{
							eText.Draw(renderer);
						}

						if(hasCerberus)
						{
							exit.Draw(renderer);
						}

						//Draw player1 tank
						player.Draw(renderer);

						turret1.Draw(renderer);
						turret2.Draw(renderer);
						turret3.Draw(renderer);
						turret4.Draw(renderer);
						turret5.Draw(renderer);
						turret6.Draw(renderer);
						turret7.Draw(renderer);
						turret8.Draw(renderer);
						turret9.Draw(renderer);
						SoulWarden.Draw(renderer);

						chase1.Draw(renderer);
						chase2.Draw(renderer);
						chase3.Draw(renderer);
						chase4.Draw(renderer);
						chase5.Draw(renderer);
						chase6.Draw(renderer);
						chase7.Draw(renderer);
						chase8.Draw(renderer);
						chase9.Draw(renderer);
						chase10.Draw(renderer);

						cursor.Draw(renderer);

						// SDL Render present
						SDL_RenderPresent(renderer);


						SDL_Delay(16);
								}//END LEVEL LOOP
						}//END CASE LEVEL

									break;
					case WIN:
					{
						alreadyOver = false;
						win = true;
						SDL_ShowCursor(0);

						//start loop
						while(win)
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
								win = false;
								break;
							}
							else if(e.type == SDL_KEYDOWN)
							{

							switch (e.key.keysym.sym)
							{
							case SDLK_q:
								quit = true;
								win = false;
								break;
							case SDLK_ESCAPE:
								quit = true;
								win = false;
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
												win = false;
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
						players1Over = SDL_HasIntersection(&cursor.cursorRect, &Players1ANPos);

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
						SDL_RenderCopy(renderer, winLevel, NULL, &winPos);
						SDL_RenderCopy(renderer, winText, NULL, &winTextPos);

						//Draw One Player image
						if(players1Pressed)
						{
							SDL_RenderCopy(renderer, playAP, NULL, &Players1ANPos);
						}
						else if (players1Over)
						{
							SDL_RenderCopy(renderer, playAO, NULL, &Players1AOPos);
						}
						else
						{
							SDL_RenderCopy(renderer, playAN, NULL, &Players1ANPos);
						}

						//Draw the cursor image
						cursor.Draw(renderer);


						// SDL Render present
						SDL_RenderPresent(renderer);
					}
				}break;
				case LOSE:
				{
					alreadyOver = false;
					lose = true;
					SDL_ShowCursor(0);

					//start loop
					while(lose)
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
							lose = false;
							break;
						}
						else if(e.type == SDL_KEYDOWN)
						{

						switch (e.key.keysym.sym)
						{
						case SDLK_q:
							quit = true;
							lose = false;
							break;
						case SDLK_ESCAPE:
							quit = true;
							lose = false;
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
											lose = false;
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
					players1Over = SDL_HasIntersection(&cursor.cursorRect, &Players1ANPos);

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
					SDL_RenderCopy(renderer, loseLevel, NULL, &winPos);
					SDL_RenderCopy(renderer, loseText, NULL, &loseTextPos);

					//Draw One Player image
					if(players1Pressed)
					{
						SDL_RenderCopy(renderer, playAP, NULL, &Players1ANPos);
					}
					else if (players1Over)
					{
						SDL_RenderCopy(renderer, playAO, NULL, &Players1AOPos);
					}
					else
					{
						SDL_RenderCopy(renderer, playAN, NULL, &Players1ANPos);
					}

					//Draw the cursor image
					cursor.Draw(renderer);


					// SDL Render present
					SDL_RenderPresent(renderer);
				}
			}break;
			}
		}

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}
