#ifndef __MENUFRAME_H
#define __MENUFRAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "Point.h"
#include "DisplayManager.h"
#include "Button.h"
#include "MyEnums.h"

using namespace std;

class MenuFrame{
    public:
        MenuFrame();
        ~MenuFrame();
        
        void update(Point* pressPoint, GameState* state);
        

    private:
        void initializeMenu();

        //background position 
        Point bgPoint;

        Button* newGame;
        Button* resume;
        Button* shop;
        Button* quit;
        //textures and image addresses
		DisplayManager::CustomTexture* mCTexture = NULL;
		string bGSprite = "../resources/menuBackground.png";
        
        
};

#endif