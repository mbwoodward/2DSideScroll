#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <stdint.h>
#include <sstream>
#include <stdlib.h>
#include <time.h>
//#include "player.h"



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
string images_dir = currentWorkingDirectory + "/src/";

//create a string to link to the audio folder on __APPLE__
string audio_dir = currentWorkingDirectory + "/src/";
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
string images_dir = currentWorkingDirectory + "\\src\\";

//create a string to link to the audio folder on __APPLE__
string audio_dir = currentWorkingDirectory + "\\src\\";
#endif;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
