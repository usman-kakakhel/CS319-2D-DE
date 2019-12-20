#ifndef __TARGETEDWEAPON_H
#define __TARGETEDWEAPON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>

#include "Weapon.h"
#include "Point.h"

class TargetedWeapon : public Weapon{
    public:
        TargetedWeapon(Point newPos = {0,0}, int newSpeed = 0, int newDamage = 0, int newOrientation = 0);
        virtual ~TargetedWeapon();

	//setter methods
	void setPosition(Point newPos);
	void setSpeed(int newSpeed);
	void setDamage(int newDamage);
	void setOrientation(int newOrientation);
	bool getToBeDestroyed();
	void setToBeDestroyed(bool toBeDestroyed);
	//getter methods
	Point getPosition() const;
	int getSpeed() const;
	int getDamage() const;
	int getOrientation() const;
	
	virtual void updatePosition();
	virtual void render( Point cameraPoint);
	virtual int getWidth();
	virtual int getHeight();

	void operator= (TargetedWeapon const &weapon);

    protected:
	Point position;
	int speed;
	int damage;
	int orientation;
	bool toBeDestroyed = false;
	Mix_Chunk* shortSound = NULL;
};

#endif
