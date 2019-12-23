/*
Crescent Class
This class implements the crescent crescent enemy.
*/
#include "Crescent.h"

// Constructor which initializes the position, speed and orientation of a crescent
Crescent::Crescent(Point newPos, int newSpeed, int newOrientation) : Enemy(newPos, newSpeed, newOrientation)
{
    health = 100;
    FiringBehavior *firingBehavior = new FireOrangeGlow();
    Enemy::setFireBehavior(firingBehavior);

    mCTexture = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(saucerSprite, mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight);
}

// Destructor which deletes all the created textures for the crescent
Crescent::~Crescent()
{
    if (mCTexture != NULL)
    {
        delete mCTexture->mTexture;
        delete mCTexture;
    }
}

float Crescent::calculateDistance(Point a, Point b)
{
    // sqrt ( (b.x - a.x)*(b.x - a.x) + (b.x - a.x)*(b.x - a.x) )
    int x = b.getX() - a.getX();
    int y = b.getY() - a.getY();
    return abs(sqrt((x * x) - (y * y)));
}

//enemy goes toward the ship
void Crescent::updatePosition(Point spaceShipPos, Human* humanList, int size)
{
    int dist = calculateDistance(myPoint, spaceShipPos);
    //if not in range move toward the spaceship, like spikey
    if (dist > requiredDistance )
    {
        int myX = myPoint.getX();
        int myY = myPoint.getY();
        int shipX = spaceShipPos.getX();
        int shipY = spaceShipPos.getY();
        //go toward ship X
        if (shipX - followAccuracy > myX)
            myPoint.setX(myX + speed);
        else if (shipX + followAccuracy < myX)
            myPoint.setX(myX - speed);
        //go toward ship Y
        if (shipY - followAccuracy > myY)
            myPoint.setY(myY + speed);
        else if (shipY + followAccuracy < myY)
            myPoint.setY(myY - speed);
    }
    else//else start the saucer behaviour
    {
        myPoint.setX(myPoint.getX() + (speed * cos(orientation * PI / 180)));
        myPoint.setY(myPoint.getY() + (speed * sin(orientation * PI / 180)));
		// Turn around if reached end of horizontal space
        if (myPoint.getX() <= 20 || myPoint.getX() > DisplayManager::GAME_WIDTH - 128)
        {
            orientation = abs(180 - orientation);
        }
        //or start circiling
        else if (myPoint.getY() < 100 || myPoint.getY() > DisplayManager::SCREEN_HEIGHT - (DisplayManager::SCREEN_HEIGHT / 5))
        {
            if (myPoint.getY() <= 100)
            {
                myPoint.setY(100 + speed);
            }
            else if (myPoint.getY() >= DisplayManager::SCREEN_HEIGHT - (DisplayManager::SCREEN_HEIGHT / 5))
            {
                myPoint.setY(DisplayManager::SCREEN_HEIGHT - (DisplayManager::SCREEN_HEIGHT / 5) - speed);
            }
            orientation = abs(360 - orientation);
        }
    }
}

// Crescent firing targetedWeapon at the spaceship
void Crescent::fireWeapon(TargetedWeapon **&weaponList, int &size, Point spaceShipPos)
{
    Enemy::fireWeapon(weaponList, size, spaceShipPos);		// Call the parent(Enemy) class's fireWeapon method
}

// Rendering the crescent in the map
void Crescent::render(Point cameraPoint)
{
    if (animation < 15)
        animation++;
    else
        animation = 0;

    SDL_Rect clip = {(128 * animation), 0, 128, 128};

    DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight, this->myPoint, cameraPoint, &clip, 0, NULL, SDL_FLIP_NONE);
}

// Getting width and height of the crescent
int Crescent::getWidth() {
        return 128;
}
int Crescent::getHeight() {
        return 128;
}
 
