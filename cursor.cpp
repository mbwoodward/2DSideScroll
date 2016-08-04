#include "cursor.h"

//Cursor creation method
Cursor::Cursor(SDL_Renderer *renderer, string filePath, float x, float y)
{
	cursorPath = filePath + "cursor.png";

	cursor = IMG_LoadTexture(renderer, cursorPath.c_str());

	cursorRect.x = x;
	cursorRect.y = y;

	cursorSpeed = 10;

	mouseX = 0, mouseY = 0, oldMouseX = 0, oldMouseY = 0;

	int w, h;
	SDL_QueryTexture(cursor, NULL, NULL, &w, &h);
	cursorRect.w = w;
	cursorRect.h = h;
}

void Cursor::MouseMotion(const SDL_Event event)
{
	if(event.type == SDL_MOUSEMOTION)
	{
		SDL_GetMouseState(&mouseX, &mouseY);
	}
}

void Cursor::Draw(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, cursor, NULL, &cursorRect);
}

//update cursor on screen
void Cursor::Update(float deltaTime)
{
	//Update cursor
	pos_X = mouseX;
	pos_Y = mouseY;

	//assign to SDL_Rect ints X and Y
	cursorRect.x = (int) (pos_X + 0.5f);
	cursorRect.y = (int) (pos_Y + 0.5f);


	//off the screen in X
	if(cursorRect.x < 0)
	{
		cursorRect.x = 0;
		pos_X = cursorRect.x;
	}
	if(cursorRect.x > 1024 - cursorRect.w)
	{
		cursorRect.x = 1024 - cursorRect.w;
		pos_X = cursorRect.x;
	}

	//off the screen in Y
	if(cursorRect.y < 0)
	{
		cursorRect.y = 0;
		pos_Y = cursorRect.y;
	}
	if(cursorRect.y > 768 - cursorRect.h)
	{
		cursorRect.y = 768 - cursorRect.h;
		pos_Y = cursorRect.y;
	}
}

