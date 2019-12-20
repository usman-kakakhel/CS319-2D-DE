
#ifndef __MISSILE_H
#define __MISSILE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "DisplayManager.h"
#include  "TargetedWeapon.h"
#include "Enemy.h"
#include <math.h>

#define PI 3.14159265

class Missile : public TargetedWeapon{
        public:
                Missile(Point newPos, int newSpeed, int newDamage, int newOrientation, Enemy** enemyList, int listSize, Point cameraPoint);
                ~Missile() override;
                int getOrientation();
		void findEnemyToSeek(Enemy** enemyList, int listSize, Point cameraPoint);
                void setOrientation(int newOrientation);

		int getWidth() override;
		int getHeight() override;
                void render(Point CameraPoint);
                //update position method
                void updatePosition();

        private:
		int timer = 0;
		Enemy* enemyToSeek;

                //textures and image addresses
		DisplayManager::CustomTexture* mCTexture = NULL;
		string missileSprite = "../resources/missile.png";
};



#endif
