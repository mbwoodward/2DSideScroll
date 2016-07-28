//needed includes
#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>

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

class Chase{
public:
	//is the enemy active - still alive?
	bool active;

	//string to hold the path the enemy's texture
	string chasePath;

	//enemy's texture to hold
	SDL_Texture *chase;

	//enemy's rect
	SDL_Rect chaseRect;

	//vars used to get the angle between the enemy's position and the player's position
	float x, y, angle;

	//audio
	Mix_Chunk *explode;

	//enemy speed
	float speed;

	//enemy health
	int health;

	//Point that will be used to rotate the enemy
	SDL_Point center;

	//chase's creation method using passed in values for renderer, player number, path to texture, x, y
	Chase(SDL_Renderer *renderer, string filePath, string audioPath, float x, float y);

	//update the tank
	void Update(float deltaTime, SDL_Rect playerRect);

	//draw the enemy tank
	void Draw(SDL_Renderer *renderer);

	//Reset
	void Reset();

	//remove health
	void RemoveHealth();

	void ChaseMoveX(float tankSpeed, float deltaTime);

	void ChaseMoveY(float tankSpeed, float deltaTime);

	//float for the turret's position to avoid precision loss
	float posT_X, posT_Y;
};


