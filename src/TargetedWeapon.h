#ifndef __TARGETEDWEAPON_H
#define __TARGETEDWEAPON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Weapon.h"
#include "Point.h"

class TargetedWeapon : public Weapon{
    public:
        TargetedWeapon(Point newPos = {0,0}, int newSpeed = 0, int newDamage = 0, int newOrientation = 0);
        ~TargetedWeapon();

	//setter methods
	void setPosition(Point newPos);
	void setSpeed(int newSpeed);
	void setDamage(int newDamage);
	void setOrientation(int newOrientation);
	//getter methods
	Point getPosition() const;
	int getSpeed() const;
	int getDamage() const;
	int getOrientation() const;
	
	virtual void updatePosition();
	virtual void render(SDL_Renderer* gRenderer, Point cameraPoint);

	void operator= (TargetedWeapon const &weapon);

    protected:
	Point position;
	int speed;
	int damage;
	int orientation;
};

#endif
