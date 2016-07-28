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

class  Pickup
{
public:

	//is the pickup active
	bool active;

	//pickup's texture
	SDL_Texture *pickup;

	//rect
	SDL_Rect pickupRect;

	//float for pickup's position to avoid precision loss
	float posJ_X, posJ_Y;

	//pickup's creation method
	Pickup(SDL_Renderer *renderer, string filePath, int number, float x, float y);

	//draw
	void Draw(SDL_Renderer *renderer);

	//update pickup
	void Update(float deltaTime);

	void MoveX(float Speed, float deltaTime);

	void MoveY(float Speed, float deltaTime);
};
