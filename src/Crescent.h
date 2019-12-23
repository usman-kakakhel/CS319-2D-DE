/*
Crescent Class header
This class implements the crescent crescent enemy.
*/
#ifndef __CRESCENT_H
#define __CRESCENT_H

#include "Enemy.h"
#include "FireOrangeGlow.h"

class Crescent : public Enemy{
public:
    Crescent(Point newPos, int newSpeed, int newOrientation);
    ~Crescent() override;
    
    void render(Point cameraPoint) override;
    void updatePosition(Point spaceShipPos, Human* humanList, int size) override;
    void fireWeapon(TargetedWeapon** &weaponList, int &size, Point spaceShipPos) override;
	int getWidth() override; 
	int getHeight() override; 
private:
	float calculateDistance(Point a, Point b);
	int animation = 0;

	//textures and image addresses
	DisplayManager::CustomTexture* mCTexture = NULL;
	string saucerSprite = "../resources/crescent.png";
	int requiredDistance = 500;
	int cushion = 150; 
};


#endif
