/*
Button Class Header
This class implements all the buttons used in the game. Each selection in any of the menus is a button, e.g. Start New Game, Resume...
*/

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
	// Position and sound of the button when pressed
    Point position;
    Mix_Chunk* shortSound = NULL;

    //textures and image addresses
	DisplayManager::CustomTexture* mCTexture = NULL;
	string buttonSprite;  
};

#endif
