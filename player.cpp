#include "player.h"


//Tank Creation
Player::Player(SDL_Renderer *renderer, int pNum, string filePath, string audioPath, float x, float y)
{
	//load health GUI
	health = IMG_LoadTexture(renderer, (filePath + "health.png").c_str());
	magic = IMG_LoadTexture(renderer, (filePath + "magic.png").c_str());

	healthR.x = 110;
	healthR.y = 43;
	healthR.w = 147;
	healthR.h = 12;

	magicR.x = 110;
	magicR.y = 60;
	magicR.w = 147;
	magicR.h = 12;

	//player health
	playerHealth = 100.0f;
	maxHealth = 100.0f;

	playerMagic = 100.0f;
	maxMagic = 100.0f;

	//activate the player
	active = true;

	flip = false;

	//set the player number 0 or 1
	playerNum = pNum;

	//set float for player speed
	speed = 100.0f;
	pVelX = 0;
	pVelY = 0;

	//tank firing sound
	fire = Mix_LoadWAV((audioPath + "throw.wav").c_str());

	//tank path to image
	if(playerNum == 0)
	{
		playerPath = filePath + "player.png";
		player2Path = filePath + "player2.png";
	}

	//load the surface into the texture
	texture = IMG_LoadTexture(renderer, playerPath.c_str());
	texture2 = IMG_LoadTexture(renderer, player2Path.c_str());

	//set the SDL_Rect X and Y for the player
	posRect.x = x;
	posRect.y = y;

	//Use SDL_QueryTexture to get the W and H of the player's texture
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	posRect.w = w;
	posRect.h = h;

	//set the movement floats to the players original X and Y
	pos_X = x;
	pos_Y = y;

	//set the xDir and yDir for the joysticks
	xDir = 0;
	yDir = 0;

	//set initial values so the player can shoot
	xDirOld = 1;
	yDirOld = 0;

	//center of the image rectangle
	center.x = posRect.w/2;
	center.y = posRect.h/2;

	//String to create the path to the player's bullet path
	string bulletPath;

	//bullet path to image
	if(playerNum == 0)
	{
		bulletPath = filePath + "bullet.png";
	}

	//Create the player's bullet pool
	for (int i = 0; i < 10; i++)
	{
		//create the bullet and move offscreen, out of the game play area
		PlayerBullet tmpBullet(renderer, bulletPath, -1000, -1000,0,0);

		//add to bulletList
		bulletList.push_back(tmpBullet);
	}
}

void Player::Update(float deltaTime, SDL_Rect target)
{

	//get angle between the tank and turret
		x = (target.x + (target.w/2)) - (posRect.x + (posRect.w/2));
		y = (target.y + (target.h/2)) - (posRect.y + (posRect.h/2));
		fireangle = atan2(y,x) * 180 / 3.14;

	//check for gamepad input
	if(Xvalue != 0 || Yvalue != 0)
	{
		//get the angle that tank needs to face
		//x = posRect.x - xDir;
		//y = posRect.y - yDir;
		tankangle = atan2(Yvalue, Xvalue) * 180/3.14;

		//set this as the old angle and dir some the player/tank can shoot when stopped
		oldAngle = tankangle;
		//xDirOld = xDir;
		//yDirOld = yDir;

		float radians = (tankangle * 3.14)/180;

		float move_x = speed * cos(radians);
		float move_y = speed * sin(radians);

		//Update floats for precision loss
		pos_X += (move_x) * deltaTime;
		pos_Y += (move_y) * deltaTime;

		//Update player position with code to account for precision loss
		posRect.x = (int)(pos_X + 0.5f);
		posRect.y = (int)(pos_Y + 0.5f);

	}else
	{
		tankangle = oldAngle;
	}


	//Adjust position floats based on speed, direction of joystick axis and deltaTime
	pos_X += (speed * xDir) * deltaTime;
	pos_Y += (speed * yDir) * deltaTime;

	//check if the player is off screen and set it back
	if(posRect.x < 0)
	{
		posRect.x = 0;
		pos_X = posRect.x;
	}

	if(posRect.x > 1024 - posRect.w)
	{
		posRect.x = 1024 - posRect.w;
		pos_X = posRect.x;
	}

	if(posRect.y < 0)
	{
		posRect.y = 0;
		pos_Y = posRect.y;
	}

	if(posRect.y > 768 - posRect.h)
	{
		posRect.y = 768 - posRect.h;
		pos_Y = posRect.y;
	}

	//Update the tank's bullets
	for(int i = 0; i < bulletList.size(); i++)
	{
		//check to see if the bullet is active
		if(bulletList[i].active)
		{
			//Update Bullet
			bulletList[i].Update(deltaTime);
		}
	}

}

void Player::chaseHit()
{
	playerHealth -= .01f;

	healthR.w = playerHealth/maxHealth * 147;
}

//hit by tank
void Player::turretHit()
{
		playerHealth -= 15;

	healthR.w = playerHealth/maxHealth * 147;
}

void Player::wardenHit()
{
		playerHealth -= 25;
		playerMagic -= 25;

	healthR.w = playerHealth/maxHealth * 147;
	magicR.w = playerMagic/maxMagic * 147;
}

void Player::Fire()
{
	if(playerMagic > 0)
	{
		playerMagic -= 1;

		magicR.w = playerMagic/maxMagic * 147;
	}
}

//hit by bullet
void Player::Draw(SDL_Renderer *renderer)
{
	//draw the player's bullets
	for(int i = 0; i < bulletList.size(); i++)
	{
		//check to see if the bullet is active
		if(bulletList[i].active)
		{
			//Draw Bullet
			bulletList[i].Draw(renderer);
		}
	}

	//draw the player texture using the vars texture and posRect
	if(flip == true)
	{
	SDL_RenderCopy(renderer, texture2, NULL, &posRect);
	}else
	{
	SDL_RenderCopy(renderer, texture, NULL, &posRect);
	}

	SDL_RenderCopy(renderer, health, NULL, &healthR);

	SDL_RenderCopy(renderer, magic, NULL, &magicR);
}

void Player::OnMouseButton(const SDL_MouseButtonEvent event)
{
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		switch(event.button)
		{
		case SDL_BUTTON_LEFT:
			CreateBullet();
			break;
		}
	}
}

void Player::CreateBullet()
{
	//see if there is a bullet active to fire
	for (int i = 0; i < bulletList.size(); i++)
	{
		//see if bullet is not active
		if (bulletList[i].active == false)
		{
			//Play the Over Sound - plays fine through levels, must pause for QUIT
			Mix_PlayChannel(-1, fire, 0);

			//set bullet to active
			bulletList[i].active = true;

			//use some math in the x position to get the bullet close to
			//the center of the player using player width
			if (flip == false)
			{
			bulletList[i].posRect.x = (posRect.x + (posRect.w));
			bulletList[i].posRect.y = (posRect.y + (posRect.h / 3));

			//finishing aligning to the player center using the texture width
			bulletList[i].posRect.x = bulletList[i].posRect.x - (bulletList[i].posRect.w / 2);
			bulletList[i].posRect.y = bulletList[i].posRect.y - (bulletList[i].posRect.h / 2);
			}
			else
			{
				bulletList[i].posRect.x = (posRect.x);
				bulletList[i].posRect.y = (posRect.y + (posRect.h/3));

				//finishing aligning to the player center using the texture width
				bulletList[i].posRect.x = bulletList[i].posRect.x - (bulletList[i].posRect.w / 2);
				bulletList[i].posRect.y = bulletList[i].posRect.y - (bulletList[i].posRect.h / 2);
			}

			//Set the x and y positions of the bullet's float positions
			bulletList[i].pos_X = bulletList[i].posRect.x;
			bulletList[i].pos_Y = bulletList[i].posRect.y;


			//if the tank is moving fire in the direction
			if (Xvalue != 0 || Yvalue != 0)
			{
				//Set the x and y positions of the bullet's float positions
				bulletList[i].tankangle = fireangle;
			}
			else
			{
				//if the tank is not moving, fire in the direction currently facing
				//Set the x and y positions of the bullet's float positions
				bulletList[i].tankangle = fireangle;
			}

			//once bullet is found, break out of loop
			break;
		}
	}
}




