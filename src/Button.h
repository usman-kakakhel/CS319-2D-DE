#ifndef __Button_H
#define __Button_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "Point.h"
#include "DisplayManager.h"

using namespace std;

class Button{
    public:
        Button(Point position, string sprite = "");
        ~Button();
        
        void render();
        bool isPressed(Point* pressPosition);
        Point getPosition();

    private:
        Point position;
        Mix_Chunk* shortSound = NULL;
        //textures and image addresses
		DisplayManager::CustomTexture* mCTexture = NULL;
		string buttonSprite;  
};

#endif