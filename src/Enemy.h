/*
Enemy Class Header
This class implements all the different types of Enemy. Enemy types inherit from this class
*/
#ifndef __ENEMY_H
#define __ENEMY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <cmath>
#define PI 3.14159265

#include "DisplayManager.h"
#include "MyEnums.h"
#include "Point.h"
#include "TargetedWeapon.h"
#include "RedBolt.h"
#include "FiringBehavior.h"
#include "Human.h"

class Enemy{
public:
	Enemy(Point newPos, int newSpeed , int newOrientation);
	virtual ~Enemy();
	Point getPosition() const;
	void setPosition(Point myPoint);
	void setHealthStatus(int health);
	int getHealthStatus();
	int getOrientation();
	int getBounty();
	bool getToBeDestroyed();
	void setToBeDestroyed(bool toBeDestroyed);
	bool getMutated();
	void setMutated(bool toBeDestroyed);
	void setFireBehavior(FiringBehavior* fireBehavior);
	virtual void updatePosition(Point spaceShipPos, Human* humanList, int size);
	virtual void render(Point cameraPoint);
	virtual void fireWeapon(TargetedWeapon** &weaponList, int &size, Point spaceShipPos);
	virtual int getWidth();
	virtual int getHeight();
	
protected:
	Point myPoint;
	int speed;
	int health;
	int bounty;
	int orientation;
	int followAccuracy = 2;
	bool toBeDestroyed = false;
	bool mutated = false;
	FiringBehavior* fireBehavior = NULL;
	int shootInterval = 0;
};

#endif
