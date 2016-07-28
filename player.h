//needed includes
#include <string>
#include <iostream>
#include <vector>

using namespace std;

#if defined(__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#endif

#if defined(_WIN32) || (_WIN64)
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#endif

#if defined(__linux__)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#endif

#include "playerbullet.h"

class Player
{
public:

	//textures for health bar
	SDL_Texture *health;

	SDL_Texture *magic;

	//rect for health
	SDL_Rect healthR;

	SDL_Rect magicR;

	//player health
	float playerHealth, maxHealth;

	float playerMagic, maxMagic;

	bool flip;

	//tank hit by eTank
	void chaseHit();

	//tank hit by bullet
	void turretHit();
	void wardenHit();

	void Fire();

	//is the player active - still alive?
	bool active;

	//variable to hold the list of bullets
	vector<PlayerBullet> bulletList;

	//string to hold the path to the player's texture
	string playerPath;
	string player2Path;

	//Integer for the player's number
	int playerNum;

	//player's texture to hold image
	SDL_Texture *texture;
	SDL_Texture *texture2;
	//player's SDL_Rect for the X,Y,W, and H of texture
	SDL_Rect posRect;

	//floats to hold the joystick axis (-1 or 0 or 1)
	float xDir, xDirOld;
	float yDir, yDirOld;

	//float for player speed
	float speed;

	//float for the player's position to avoid precision loss
	float pos_X, pos_Y;

	//vars used to get the angle between the tank's position and the joystick position
	float x, y;

	//Point that will be used to track player
	SDL_Point center;

	//keep the last angle so the player can fire in the correct direction
	float oldAngle, tankangle;

	//audio sound effect - CHUNK
	Mix_Chunk *fire;

	//add X and Y values
	Sint16 Xvalue, Yvalue;

	//Player's creation method using passed in values for renderer, player number, path to the texture
	//starting position X, starting position Y
	Player(SDL_Renderer *renderer, int pNum, string filePath, string audioPath, float x, float y);

	void OnMouseButton(const SDL_MouseButtonEvent event);

	//update the player using the passed in deltaTime
	void Update(float deltaTime);

	//draw the player main's passed in renderer
	void Draw(SDL_Renderer *renderer);

	//reset the player
	void Reset();

private:

	void CreateBullet();
};
