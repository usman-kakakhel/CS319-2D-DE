/*
Bugeye Class Header
This class implements the Bugeye enemy. Bugeye is the enemy which picks up the humans from the ground
*/
#ifndef __BUGEYE_H
#define __BUGEYE_H

#include "Enemy.h"
#include "Human.h"

// Bugeye inherits Enemy, because bugeye is an enemy
class Bugeye : public Enemy{
    public:
        Bugeye(Point newPos, int newSpeed, int newOrientation);
        ~Bugeye() override;
        
        void render(Point cameraPoint) override;
        void pickHuman();
        void updatePosition(Point spaceShipPos, Human* humanList, int size) override;
        void fireWeapon(TargetedWeapon** &weaponList, int &size, Point spaceShipPos) override;
	    int getWidth() override; 
	    int getHeight() override;
        Human* getHuman();
        bool getPick();
        void setHuman(Human* theHuman);
        static bool picked;
    private:
       float calculateDistance(Point a, Point b);
       
       int animation = 0;
       bool pick = false;
       //bool hasHuman = false;
       Human* pickedHuman = NULL;
       bool hasTarget = false;
       Human humanToPick;
       Point target;
       int hTimer = 0;


       DisplayManager::CustomTexture* mCTexture = NULL;
       string bugeyeSprite = "../resources/bugeye.png";
};

#endif
