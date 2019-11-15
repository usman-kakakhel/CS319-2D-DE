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


class GameFrame : public DisplayManager{
    public:
        GameFrame(int SCREEN_WIDTH = 1920, int SCREEN_HEIGHT = 1080, int GAME_WIDTH = 5760);
        ~GameFrame();
        void init();
        void updateUI( SDL_Renderer* gRenderer);
        void updateSpaceshipPosition(Orientation orientation);
        void updateAllActors();
        void fire(bool* keyList);

       
    private:
        SpaceShip* spaceShip;
        Camera* camera;
        
        int score = 0;
        int highScore = 0;
        int coins = 0;
        
        TargetedWeapon** weaponList;
        int weaponListSize = 0;

        //private methods
        bool isInScreen(Point point);
};

#endif