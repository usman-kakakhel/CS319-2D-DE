#ifndef __GAMEFRAME_H
#define __GAMEFRAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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


class GameFrame : public DisplayManager{
    public:
        GameFrame(int SCREEN_WIDTH = 1920, int SCREEN_HEIGHT = 1080, int GAME_WIDTH = 5760);
        ~GameFrame();
        void init();
        void updateUI( SDL_Renderer* gRenderer);
        void updateSpaceshipPosition(Orientation orientation);
        void fire(bool* keyList);
       
    private:
        SpaceShip* spaceShip;
        Camera* camera;
        Asteroid* asteroid;
        
        int score = 0;
        int highScore = 0;
        int coins = 0;
        
        TargetedWeapon** weaponList;
        int weaponListSize = 0;
        Human* humanList;
        int humanListSize = 0;
        Enemy** enemyList;
        int enemyListSize = 0;

        //private methods
        void updateAllActors();
        bool isInScreen(Point point);
        void addHumans();
        void addAsteroids();
        void addEnemy();
};

#endif