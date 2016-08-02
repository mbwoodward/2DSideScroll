#include "pickup.h"

Pickup::Pickup(SDL_Renderer *renderer, string filePath, int number, float x, float y)
{
	active = true;

	if(number==0)
	{
		//Create the pickup file path
		string basePath = filePath + "key.png";

		//load image
		pickup = IMG_LoadTexture(renderer, basePath.c_str());
	}
	else if(number==1)
	{
		//Create the pickup file path
		string basePath = filePath + "healthEssence.png";

		//load image
		pickup = IMG_LoadTexture(renderer, basePath.c_str());
	}
	else if(number==2)
	{
		//Create the pickup file path
		string basePath = filePath + "magicEssence.png";

		//load image
		pickup = IMG_LoadTexture(renderer, basePath.c_str());
	}
	else if(number==3)
	{
		//Create the pickup file path
		string basePath = filePath + "spirits.png";

		//load image
		pickup = IMG_LoadTexture(renderer, basePath.c_str());
	}
	else if(number==4)
	{
		//Create the pickup file path
		string basePath = filePath + "lights.png";

		//load image
		pickup = IMG_LoadTexture(renderer, basePath.c_str());
	}
	//set SDL_Rect x and y for image
	pickupRect.x = x;
	pickupRect.y = y;

	//use SDL_QueryTexture
	int w, h;
	SDL_QueryTexture(pickup, NULL, NULL, &w, &h);
	pickupRect.w = w;
	pickupRect.h = h;

	posJ_X = pickupRect.x;
	posJ_Y = pickupRect.y;
}

//pickup draw method
void Pickup::Draw(SDL_Renderer *renderer)
{
	//draw
	SDL_RenderCopy(renderer, pickup, NULL, &pickupRect);
}

void Pickup::MoveX(float Speed, float deltaTime)
{
	posJ_X += (Speed) * deltaTime;

	//Update pickup position
	pickupRect.x = (int) (posJ_X + 0.5f);
}

void Pickup::MoveY(float Speed, float deltaTime)
{
	posJ_Y += (Speed) * deltaTime;

	//Update pickup position
	pickupRect.y = (int) (posJ_Y + 0.5f);
}

