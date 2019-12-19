#ifndef __GAMEFRAME_H
#define __GAMEFRAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>


#include "DisplayManager.h"
#include "SpaceShip.h"
#include "MyEnums.h"
#include "Camera.h"
#include "TargetedWeapon.h"
#include "Human.h"
#include "Asteroid.h"
#include "Enemy.h"
#include "Saucer.h"
#include "Spikey.h"
#include "Bugeye.h"
#include "SaucerBlades.h"
#include "Crescent.h"
#include "Slicer.h"
#include "WarpZone.h"
#include "Pickup.h"
#include "FuelPickup.h"
#include "HealthPickup.h"
#include "Explosion.h"
#include "DataManager.h"
#include "Item.h"

class GameFrame{
    public:
        GameFrame();
        ~GameFrame();
        void init();
        void updateUI(GameState* state, int coins);
        void updateAllActors(bool* keyList, GameState* state, Item** boughtHealthItems, int boughtHealthItemsSize, Item** boughtFuelItems, int boughtFuelItemsSize, int& coins);
        void destroy();
       
    private:
        SpaceShip* spaceShip;
        Camera* camera;
        Asteroid* asteroid;
        TargetedWeapon** weaponList;
        int weaponListSize = 0;
        Human* humanList;
        int humanListSize = 0;
        Enemy** enemyList;
        int enemyListSize = 0;
        WarpZone* warpZone;
        Pickup* healthPickup;
        Pickup* fuelPickup;

        Explosion** explosionList;
        int explosionListSize = 0;

        //private methods
        bool isInScreen(Point point);
        void addHumans();
        void addAsteroids();
        void addEnemy();
        void removeActors(GameState* state);
        void addWarpZone();
        void addPickup();
	    void detectCollisions(int& coins);
	    bool collided(Point aPoint, int aWidth, int aHeight, Point bPoint, int bWidth, int bHeight);
        void addExplosion(Point thePoint);

        Mix_Chunk* pickupSound = NULL;
};

#endif
