#include "SpaceShip.h"
#include "iostream"

//for highscore update
#include "DataManager.h" 


SpaceShip::SpaceShip(){
    myPoint.setX(DisplayManager::SCREEN_WIDTH / 5);
    myPoint.setY(DisplayManager::SCREEN_HEIGHT / 2);
    orientation = RIGHT;
    prevOrientation = RIGHT;

    //create textures of all images once
    mCTextureList = new DisplayManager::CustomTexture*[3];
    for (int i = 0; i < 3; i++){
        mCTextureList[i] = new DisplayManager::CustomTexture();
        DisplayManager::loadFromFile(spriteList[i], mCTextureList[i]->mTexture, mCTextureList[i]->mWidth, mCTextureList[i]->mHeight); 
    }
    mCTexture = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(thrustSprite, mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight);
    
    //Load sound effects
    shortSound = Mix_LoadWAV( "../resources/Sounds/move.wav" );
    if( shortSound == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    if (shortSound != NULL)
		Mix_PlayChannel( 1, shortSound, -1 );
	Mix_Pause(1);
}

SpaceShip::~SpaceShip(){
    if (mCTextureList != NULL){
        for (int i = 0; i < 3; i++){
            delete mCTextureList[i]->mTexture;
        }
        delete[] mCTextureList;
    }
    if (mCTexture != NULL){
        delete mCTexture->mTexture;
        delete mCTexture;
    }
    if (shortSound != NULL){
		//Free the sound effects
		Mix_FreeChunk( shortSound);
		shortSound = NULL;
	}
}

int SpaceShip::getScore(){
    return score;
}

Point SpaceShip::getPoint() const{
    return myPoint;
}

Point* SpaceShip::getPointPointer() const{
    return NULL;
}

bool SpaceShip::getToBeDestroyed() {
	return this->toBeDestroyed;
}

int SpaceShip::getHealthStatus(){
    return healthStatus;
}
int SpaceShip::getFuelStatus(){
    return fuelStatus;
}

int SpaceShip::getMaxHealth() {
	return this->maxHealth;
}

int SpaceShip::getMaxFuel() {
	return this->maxFuel;
}

int SpaceShip::getMissileCountdown(){
    return missileCountdown;
}
int SpaceShip::getNuclearBombCountdown(){
    return nuclearBombCountdown;
}

int SpaceShip::getWidth() {
	return 128;
}

int SpaceShip::getHeight() {
	return 128;
}

Orientation SpaceShip::getOrientation(){
    return orientation;
}

void SpaceShip::setPoint(Point myPoint){
    SpaceShip::myPoint = myPoint;
}

void SpaceShip::setHealthStatus(int healthStatus) {
	this->healthStatus = healthStatus;
}

void SpaceShip::setFuelStatus(int fuelStatus){
	this->fuelStatus = fuelStatus;
}

void SpaceShip::setMaxHealth(int maxHealth) {
	this->maxHealth = maxHealth;
}

void SpaceShip::setMaxFuel(int maxFuel) {
	this->maxFuel = maxFuel;
}

void SpaceShip::setToBeDestroyed(bool toBeDestroyed) {
	this->toBeDestroyed = toBeDestroyed;
}

void SpaceShip::setOrientation(Orientation orientation){
    //prevOrientation shows the direction left or right the ship is in and orientation shows the up and down tilt
    if (orientation == RIGHT || orientation == LEFT)
        prevOrientation = orientation;
    this->orientation = orientation;
}


void SpaceShip::render( Point cameraPoint){
    if (fireAnimation < 15)
        fireAnimation++;
    else
        fireAnimation = 0;
    
    //render the image according to the direction the ship is in
    if (prevOrientation == RIGHT){
        DisplayManager::render(mCTextureList[(int)orientation]->mTexture, mCTextureList[(int)orientation]->mWidth, mCTextureList[(int)orientation]->mHeight, myPoint, cameraPoint, NULL, 90, NULL, SDL_FLIP_NONE);
        if(isMoving){
            SDL_Rect clip = { (64 * fireAnimation), 0, 64, 128 };
            Point firePoint = myPoint;
            firePoint.setX(firePoint.getX() - 65);
            DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight, firePoint, cameraPoint, &clip, 90, NULL, SDL_FLIP_HORIZONTAL);
        }
    }
    else if (prevOrientation == LEFT){
        if (orientation == LEFT){
            DisplayManager::render(mCTextureList[RIGHT]->mTexture, mCTextureList[RIGHT]->mWidth, mCTextureList[RIGHT]->mHeight, myPoint, cameraPoint, NULL, 270, NULL, SDL_FLIP_HORIZONTAL);
        }
        else{
            DisplayManager::render(mCTextureList[(int)orientation]->mTexture, mCTextureList[(int)orientation]->mWidth, mCTextureList[(int)orientation]->mHeight, myPoint, cameraPoint, NULL, 270, NULL, SDL_FLIP_HORIZONTAL);
        }
        if (isMoving){
            SDL_Rect clip = { (64 * fireAnimation), 0, 64, 128 };
            Point firePoint = myPoint;
            firePoint.setX(firePoint.getX() + 130);
            DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight, firePoint, cameraPoint, &clip, 270, NULL, SDL_FLIP_HORIZONTAL);  
        } 
    }
    //when the render is done, set the orientation to directional rather than tilt
    orientation = prevOrientation;
    isMoving = false;
}


void SpaceShip::fireBullet(TargetedWeapon** &weaponList, int &size){
    int newOrientation = 0;
    Point newPos = myPoint;
    if (prevOrientation == LEFT){
        newOrientation = 270;
        newPos.setX(newPos.getX() - 0);
        newPos.setY(newPos.getY() + 32);
    }
    else{
        newOrientation = 90;
        newPos.setX(newPos.getX() + 84);
        newPos.setY(newPos.getY() + 32);
    }
    //make a new list of weapons
    size++;
    TargetedWeapon** newList = new TargetedWeapon*[size];
    
    //copy existing list to new one
    for (int i = 0; i < size - 1; i++){
        newList[i] = weaponList[i];
    }
    //new bullet
    newList[(size - 1)] = new BlueBolt(newPos, 13, 50, newOrientation);
    //delete existing list
    if (weaponList != NULL)
        delete [] weaponList;

    weaponList = newList;
}

void SpaceShip::dropNuclearBomb(Enemy** &enemyList, int &size, Point cameraPoint){
    //Two counters, 1) Timer per second, 2) Timer for cooldown
    //static counters
    
    if(nuclearBombCountdown <= 0){
        nuclearBombCountdown = 10;

        int width = DisplayManager::SCREEN_WIDTH/2;
        int height = DisplayManager::SCREEN_HEIGHT/2;
        width = width * width;
        height = height * height;
        int radius = (int)round(sqrt((double)(width + height)));
        MassDestructionWeapon* bomb = new NuclearBomb(myPoint,100,radius);
        bomb->destroy(enemyList, size, cameraPoint);
        delete bomb;
    }
}

void SpaceShip::fireMissile(TargetedWeapon** &weaponList, int &weaponSize, Enemy** enemyList, int enemySize, Point cameraPoint){
    if(missileCountdown == 0){
        missileCountdown = 3;

        int newOrientation = 0;
        Point newPos = myPoint;
        if (prevOrientation == LEFT){
            newOrientation = 270;
            newPos.setX(newPos.getX() - 0);
            newPos.setY(newPos.getY() + 32);
        }
        else{
            newOrientation = 90;
            newPos.setX(newPos.getX() + 84);
            newPos.setY(newPos.getY() + 32);
        }

        //make a new list of weapons
        weaponSize++;
        TargetedWeapon** newList = new TargetedWeapon*[weaponSize];

        //copy existing list to new one
        for (int i = 0; i < weaponSize - 1; i++){
            newList[i] = weaponList[i];
        }

        //new missile
        newList[(weaponSize - 1)] = new Missile(newPos, 26, 100, newOrientation, enemyList, enemySize, cameraPoint);

        //delete existing list
        if(weaponList != NULL)
            delete [] weaponList;

        weaponList = newList;

    }

}


void SpaceShip::controlSpaceship(bool* keyList, TargetedWeapon** &weaponList, int &weaponSize, Enemy** &enemyList, int &enemySize, Point cameraPoint){
    //first check for firing keys pressed and fire accordingly
    if (keyList[BULLET_KEY]){
        fireBullet(weaponList, weaponSize);
    }
    if (keyList[MISSILE_KEY]){
        fireMissile(weaponList, weaponSize, enemyList, enemySize, cameraPoint);
    }
    if (keyList[DESTRUCTION_KEY]){
        dropNuclearBomb(enemyList, enemySize, cameraPoint);
    }
    //then handle spaceship movement
    if (keyList[UP_PRESSED] || keyList[DOWN_PRESSED] || keyList[LEFT_PRESSED] || keyList[RIGHT_PRESSED])
    {
        if (keyList[UP_PRESSED]){
            setOrientation(UP);
        }
        else if (keyList[DOWN_PRESSED]){
            setOrientation(DOWN);
        }
        else if (keyList[LEFT_PRESSED]){
            setOrientation(LEFT);
        }
        else if (keyList[RIGHT_PRESSED]){
            setOrientation(RIGHT);
        }
        isMoving = true;
        //update the position of the spaceship in the direction it is according to its speed
        if (orientation == RIGHT){
            if (myPoint.getX() > DisplayManager::GAME_WIDTH - (DisplayManager::SCREEN_WIDTH / 5)){
                //myPoint.setX(DisplayManager::SCREEN_WIDTH );
            }
            else{
                myPoint.setX(myPoint.getX() + speed);
            }
        }
        else if (orientation == UP && myPoint.getY() > (DisplayManager::SCREEN_HEIGHT / 8)){
            myPoint.setY(myPoint.getY() - speed);
        }
        else if (orientation == DOWN && myPoint.getY() < DisplayManager::SCREEN_HEIGHT - (DisplayManager::SCREEN_HEIGHT / 4)){
            myPoint.setY(myPoint.getY() + speed);
        }
        else if (orientation == LEFT){
            if (myPoint.getX() < (DisplayManager::SCREEN_WIDTH / 5) ){
                //myPoint.setX(DisplayManager::GAME_WIDTH - (DisplayManager::SCREEN_WIDTH ));
            }
            else{
                myPoint.setX(myPoint.getX() - speed);
            }
        }
    }

        static int cTimer = 0; //time count will go till 29 to show 1 second has passed
    if(cTimer >= 29){
        //one second has passed need to update the score and fuel
        fuelStatus--;    //reduce the amount of fuel
        score = score + 1;  //increment the score
        cTimer = 0; //reset the timer
    }
    else{
        cTimer++;
    }

    int static mTimer = 0; //goes till 29 for 1 second lapse
    int static nTimer = 0; //goes till 29 for 1 second lapse

    if(mTimer >= 29){
        if (missileCountdown > 0)
            missileCountdown--;
        mTimer = 0;
    }
    else{
        mTimer++;
    }

    if(nTimer >= 29){
	if(nuclearBombCountdown > 0) 
        	nuclearBombCountdown--;
        nTimer = 0;
    }
    else{
        nTimer++;
    }

    if (isMoving){
        
        Mix_Resume(1);
    }
    else{
        Mix_Pause(1);
    }

}

