#include "Missile.h"

Missile::Missile(Point newPos, int newSpeed, int newDamage, int newOrientation, Enemy** enemyList, int listSize, Point cameraPoint):TargetedWeapon(newPos, newSpeed, newDamage, newOrientation){
	this->enemyToSeek = NULL;
	this->findEnemyToSeek(enemyList, listSize, cameraPoint);

	//create the textures for sprites
	mCTexture = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(missileSprite, mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight);

	//Load sound effects
    shortSound = Mix_LoadWAV( "../resources/Sounds/missile.wav" );
    if( shortSound == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
	if (shortSound != NULL)
		Mix_PlayChannel( -1, shortSound, 0 );
}

Missile::~Missile(){
	if (shortSound != NULL){
		//Free the sound effects
		Mix_FreeChunk( shortSound);
		shortSound = NULL;
	}
}

int Missile::getOrientation() {
        return this->orientation;
}

void Missile::setOrientation(int newOrientation) {
        this->orientation = newOrientation;
}

double calculateDistance(Point a, Point b)
{
    // sqrt ( (b.x - a.x)*(b.x - a.x) + (b.x - a.x)*(b.x - a.x) )
    int x = b.getX() - a.getX();
    int y = b.getY() - a.getY();
    return (sqrt((x * x) + (y * y)));
}

bool isInScreen(Point point, Point cameraPoint){
    bool check = true;
    point = DisplayManager::getRenderPointFor(point, cameraPoint);
    if (point.getX() < 0 || point.getX() > DisplayManager::SCREEN_WIDTH)
        check = false;
    if (point.getY() < 0 || point.getY() > DisplayManager::SCREEN_HEIGHT)
        check = false;
    return check;
}

void Missile::findEnemyToSeek(Enemy** enemyList, int listSize, Point cameraPoint) {
	Enemy* nearestEnemy = NULL;
	if(enemyList != NULL) {
		if(listSize > 0) {
			int index = 0;
			for(index = 0; index < listSize; index++) {
				if(isInScreen(enemyList[index]->getPosition(),cameraPoint)) {
					nearestEnemy = enemyList[index];
					break;
				}
			}

			if(nearestEnemy != NULL) {
				int smallestDistance = (int)(calculateDistance(nearestEnemy->getPosition(), this->getPosition()));
				for(int i = index+1; i < listSize; i++) {
					if(isInScreen(enemyList[index]->getPosition(),cameraPoint)) {
						int distance = (int)(calculateDistance(enemyList[i]->getPosition(), this->getPosition()));

						if(distance < smallestDistance) {
							nearestEnemy = enemyList[i];
							smallestDistance = distance;
						}
					}
				}
				enemyToSeek = nearestEnemy;
			}
		}
	}
}

void Missile::updatePosition() {
	int x = 0;
	int y = 0;
	if(timer >= 1) {
		if(enemyToSeek != NULL) {
			//int newOrientation = atan2(this->getPosition().getY() - enemyToSeek->getPosition().getY(), this->getPosition().getX() - enemyToSeek->getPosition().getX()) * 180/PI;
			//newOrientation = newOrientation + 180;
			//this->setOrientation(newOrientation+90);
		

		//x = (int)(cos((orientation-90)*(PI/180))*speed + this->getPosition().getX());
		//y = (int)(sin((orientation-90)*(PI/180))*speed + this->getPosition().getY());
		int followAccuracy = 0;
		if( enemyToSeek->getPosition().getX() > this->getPosition().getX())
        		x = this->getPosition().getX() + speed;
    		else if(enemyToSeek->getPosition().getX() < this->getPosition().getX())
        		x = this->getPosition().getX() - speed;
    	    	//go toward ship Y
    	    	if(enemyToSeek->getPosition().getY() > this->getPosition().getY())
        		y = this->getPosition().getY() + speed;
		else if(enemyToSeek->getPosition().getY() < this->getPosition().getY())
	        	y = this->getPosition().getY() - speed;

		}
		else {
		x = (int)(cos((orientation-90)*(PI/180))*speed + this->getPosition().getX());
		y = this->getPosition().getY();

		}
		timer = 1;
	}

	else {
		x = (int)(cos((orientation-90)*(PI/180))*speed + this->getPosition().getX());
		y = this->getPosition().getY();
		timer++;
	}


	Point p(x,y);
	this->setPosition(p);

}

int Missile::getWidth() {
	return mCTexture->mWidth;
}

int Missile::getHeight() {
	return mCTexture->mHeight;
}

void Missile::render( Point cameraPoint) {
        DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight, this->position, cameraPoint, NULL, this->orientation, NULL, SDL_FLIP_NONE);
}
