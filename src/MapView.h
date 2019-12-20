#ifndef __MapView_H
#define __MapView_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "DisplayManager.h"
#include "Point.h"
#include "SpaceShip.h"
#include "MyEnums.h"
#include "Human.h"
#include "Enemy.h"

class MapView{
    public:
        MapView(Point position);
        ~MapView();

        void render(SpaceShip* spaceShip, Enemy** enemyList, int enemyListSize, Human* humanList, int humanListSize, Point camPoint);
        
    private:
        Point position;

        //textures and image addresses
        DisplayManager::CustomTexture* mCTextureBG = NULL;
        string bGSprite = "../resources/mapBackground.png";

        DisplayManager::CustomTexture* mCTexture = NULL;
        string gameBGSprite = "../resources/background.jpg";

        DisplayManager::CustomTexture* mCTextureShip = NULL;
        string shipSprite = "../resources/blue.png";

        DisplayManager::CustomTexture* mCTextureHuman = NULL;
        string humanSprite = "../resources/yellow.png";

        DisplayManager::CustomTexture* mCTextureEnemy = NULL;
        string enemySprite = "../resources/orange.png";
};


#endif