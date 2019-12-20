#ifndef __SLICER_H
#define __SLICER_H

#include "Enemy.h"
#include "FireRedBolt.h"

class Slicer : public Enemy{
    public:
        Slicer(Point newPos, int newSpeed, int newOrientation);
        ~Slicer() override;
        
        void render(Point cameraPoint) override;
        void updatePosition(Point spaceShipPos, Human* humanList, int size) override;
        void fireWeapon(TargetedWeapon** &weaponList, int &size, Point spaceShipPos) override;
	int getWidth() override;
	int getHeight() override;

    private:
       int animation = 0;
       int angle = 90;
       int multiplier = -1;
       //textures and image addresses
	   DisplayManager::CustomTexture* mCTexture = NULL;
       string slicerSprite = "../resources/slicer.png";
};


#endif
