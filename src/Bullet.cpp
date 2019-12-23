/*
Bullet Class
This class implements the bullet of the spaceship. Bullet has subclasses which different entities in the game fires these different bullets
*/
#include "Bullet.h"

// Constructor needs position, speed, damage, orientation and also the parent class's attributes.
Bullet::Bullet(Point newPos, int newSpeed, int newDamage, int newOrientation):TargetedWeapon(newPos, newSpeed, newDamage, newOrientation){
	//Load sound effects
    shortSound = Mix_LoadWAV( "../resources/Sounds/bullet.wav" );		// Sound effect for bullet
    if( shortSound == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
	if (shortSound != NULL)
		Mix_PlayChannel( -1, shortSound, 0 );
}

// Destructor for Bullet
Bullet::~Bullet(){
	if (shortSound != NULL){
		//Free the sound effects
		Mix_FreeChunk( shortSound);
		shortSound = NULL;
	}
}


//update position
void Bullet::updatePosition(){
	int x = this->position.getX();
	int y = this->position.getY();
	x = cos((orientation - 90)*(PI/180))*speed + x; //x= speed*cos(theta) + x
	y = sin((orientation - 90)*(PI/180))*speed + y;
	Point p(x,y);
	this->setPosition(p);
}
