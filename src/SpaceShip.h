#ifndef __SPACESHIP_H
#define __SPACESHIP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>


#include "DisplayManager.h"
#include "MyEnums.h"
#include "Point.h"
#include "TargetedWeapon.h"
#include "BlueBolt.h"
#include "Enemy.h"
#include "NuclearBomb.h"
#include "Missile.h"

class SpaceShip{
    public:
        SpaceShip();
        ~SpaceShip();
        Point getPoint() const;
        Point* getPointPointer() const;
        int getScore();
	int getWidth();
	int getHeight();
        int getHealthStatus();
	int getMaxHealth();
	int getMaxFuel();
        int getFuelStatus();
        int getMissileCountdown();
        int getNuclearBombCountdown();
	bool getToBeDestroyed();
        void setPoint(Point myPoint);
	void setHealthStatus(int healthStatus);
	void setFuelStatus(int fuelStatus);
	void setToBeDestroyed(bool toBeDestroyed);
	void setMaxHealth(int maxHealth);
	void setMaxFuel(int maxFuel);
        Orientation getOrientation();
        void setOrientation(Orientation orientation);

        void render( Point cameraPoint);
        void fireBullet(TargetedWeapon** &weaponList, int &size);
        void fireMissile(TargetedWeapon** &weaponList, int &weaponSize, Enemy** enemyList, int enemySize, Point cameraPoint);
        void dropNuclearBomb(Enemy** &enemyList, int &size, Point cameraPoint);
        void controlSpaceship(bool* keyList, TargetedWeapon** &weaponList, int &weaponSize, Enemy** &enemyList, int &enemySize, Point cameraPoint);
        
    private:
        Point myPoint;
        bool isMoving;
	bool toBeDestroyed = false;
        int healthStatus = 100;
	int maxHealth = 100;
        int fuelStatus = 100;
	int maxFuel = 100;
        int speed = 10;
        int nuclearBombCountdown = 0;
        int missileCountdown = 0;
        int fireAnimation = 0;
        int score = 0;
        Orientation orientation;
        Orientation prevOrientation;

        Mix_Chunk* shortSound = NULL;
        //textures and image addresses
        DisplayManager::CustomTexture** mCTextureList = NULL;
        DisplayManager::CustomTexture* mCTexture = NULL;
        string spriteList[3] = {"../resources/right.png", "../resources/up.png", "../resources/down.png"};
        string thrustSprite = "../resources/thrust.png";

};

#endif
