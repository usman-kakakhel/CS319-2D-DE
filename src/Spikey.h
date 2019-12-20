#ifndef __SPIKEY_H
#define __SPIKEY_H

#include "Enemy.h"

class Spikey : public Enemy{
    public:
     Spikey(Point newPos, int newSpeed, int newOrientation);
     ~Spikey() override;
        
     void render(Point cameraPoint) override;
     void updatePosition(Point spaceShipPos, Human* humanList, int size) override;
     void fireWeapon(TargetedWeapon** &weaponList, int &size, Point spaceShipPos) override;
     int getWidth() override;
     int getHeight() override;
     
    private:
      int animation = 0;
      DisplayManager::CustomTexture* mCTexture = NULL;
      string spikeySprite = "../resources/spikey.png";
};

#endif
