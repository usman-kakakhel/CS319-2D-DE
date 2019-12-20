#include "Bullet.h"

Bullet::Bullet(Point newPos, int newSpeed, int newDamage, int newOrientation):TargetedWeapon(newPos, newSpeed, newDamage, newOrientation){
	//Load sound effects
    shortSound = Mix_LoadWAV( "../resources/Sounds/bullet.wav" );
    if( shortSound == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
	if (shortSound != NULL)
		Mix_PlayChannel( -1, shortSound, 0 );
}


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
