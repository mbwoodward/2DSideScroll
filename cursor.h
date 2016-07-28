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

class Cursor
{
public:

	SDL_Texture *cursor;

	SDL_Rect cursorRect;

	string cursorPath;

	Cursor(SDL_Renderer *renderer, string filePath, string audioPath, float x, float y);

	void MouseMotion(const SDL_MouseButtonEvent event);

	void Draw(SDL_Renderer *renderer);
};
