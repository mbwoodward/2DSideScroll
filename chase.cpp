#include "chase.h"

//Tank create
Chase::Chase(SDL_Renderer *renderer, string filePath, string audioPath, float x, float y)
{
	//activate
	active = false;

	//fire sound
	explode = Mix_LoadWAV((audioPath + "fire.wav").c_str());

	//create the guard
	string enemyPath = filePath + "chase.png";

	//load image
	chase = IMG_LoadTexture(renderer, enemyPath.c_str());

	//set the SDL_Rect
	chaseRect.x = x;
	chaseRect.y = y;

	//use SDL_QueryTexture
	int w,h;
	SDL_QueryTexture(chase, NULL, NULL, &w, &h);
	chaseRect.w = w;
	chaseRect.h = h;

	posT_X = chaseRect.x;
	posT_Y = chaseRect.y;

	speed = 50;

	center.x = 32;
	center.y = 32;

	health = 10;
}

void Chase::Reset()
{
	//reset the x pos
	chaseRect.x = -1000;

	//update pos_X
	posT_X = chaseRect.x;

	health = 10;

	//deactivate
	active = false;
}

void Chase::RemoveHealth()
{
	health --;

	if(health <= 0)
	{
		Reset();
	}
}

//tank moves X
void Chase::ChaseMoveX(float tankSpeed, float deltaTime)
{
	posT_X += (tankSpeed) * deltaTime;

	//update pos
	chaseRect.x = (int) (posT_X + 0.5f);
}

//tank moves Y
void Chase::ChaseMoveY(float tankSpeed, float deltaTime)
{
	posT_Y += (tankSpeed) * deltaTime;

	//update pos
	chaseRect.y = (int) (posT_Y + 0.5f);
}

//turret draw
void Chase::Draw(SDL_Renderer *renderer)
{
	//draw
	SDL_RenderCopyEx(renderer, chase, NULL, &chaseRect, angle, &center, SDL_FLIP_NONE);
}

//tank update
void Chase::Update(float deltaTime, SDL_Rect tankRect)
{

	double distancex = (chaseRect.x - tankRect.x) * (chaseRect.x - tankRect.x);
	double distancey = (chaseRect.y - tankRect.y) * (chaseRect.y - tankRect.y);

	double calcdistance = sqrt(distancex + distancey);

	if(calcdistance <= 350)
	{
		active = true;
	}
	else
	{
		active = false;
	}
	if(active)
	{
		//get angle
		x = (tankRect.x + (tankRect.w/2)) - (chaseRect.x + (chaseRect.w/2));
		y = (tankRect.y + (tankRect.h/2)) - (chaseRect.y + (chaseRect.h/2));
		angle = atan2(y,x) * 180 / 3.14;

		//gives radians
		float radians = (angle * 3.14) / 180;

		//get x and y
		float move_x = speed * cos(radians);
		float move_y = speed * sin(radians);

		//update floats
		posT_X += (move_x) * deltaTime;
		posT_Y += (move_y) * deltaTime;

		//update player pos
		chaseRect.x = (int)(posT_X + 0.5f);
		chaseRect.y = (int)(posT_Y + 0.5f);
	}
}



