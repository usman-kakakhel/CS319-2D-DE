/*
Bugeye Class
This class implements the Bugeye enemy. Bugeye is the enemy which picks up the humans from the ground
*/
#include "Bugeye.h"

// Bugeye state should false at first, cause it has not picked up a human yet.
bool Bugeye::picked = false;

// Constructor for the bugeye requires its position, speed and orientation and initializes it for its parent class too.
Bugeye::Bugeye(Point newPos, int newSpeed, int newOrientation) : Enemy(newPos, newSpeed, newOrientation){
    health = 100;
    mCTexture = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(bugeyeSprite, mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight);
}

Bugeye::~Bugeye()
{   
    if (pickedHuman != NULL){
        pickedHuman->setState(FALLING);
        Bugeye::picked = false;
    }
    if (mCTexture != NULL)
    {
        delete mCTexture->mTexture;
        delete mCTexture;
    }
}

//gives the distancce between 2 points
float Bugeye::calculateDistance(Point a, Point b)
{
	// Formulae for calculating distance between two points
    // sqrt ( (b.x - a.x)*(b.x - a.x) + (b.x - a.x)*(b.x - a.x) )
    int x = b.getX() - a.getX();
    int y = b.getY() - a.getY();
    return (sqrt((x * x) + (y * y)));
}

//3 movement patterns. Move like saucer, go towards human, move up.
void Bugeye::updatePosition(Point spaceShipPos, Human* humanList, int size)
{
    //if not picking, move like a saucer
    if (!pick)
    {
        //timer to do pickup
        if(hTimer >= 30){
            if (!Bugeye::picked)
                pickHuman();
            hTimer = 0;
        }
        else{
            hTimer++;
        }

        myPoint.setX(myPoint.getX() + (speed * cos(orientation * PI / 180)));
        myPoint.setY(myPoint.getY() + (speed * sin(orientation * PI / 180)));
        if (myPoint.getX() < 0 || myPoint.getX() > DisplayManager::GAME_WIDTH - 128)
        {
            orientation = abs(180 - orientation);
        }
        else if (myPoint.getY() < 140 || myPoint.getY() > DisplayManager::SCREEN_HEIGHT - (DisplayManager::SCREEN_HEIGHT / 5))
        {
            if (myPoint.getY() <= 140)
            {
                myPoint.setY(140 + speed);
            }
            else if (myPoint.getY() >= DisplayManager::SCREEN_HEIGHT - (DisplayManager::SCREEN_HEIGHT / 5))
            {
                myPoint.setY(DisplayManager::SCREEN_HEIGHT - (DisplayManager::SCREEN_HEIGHT / 5) - speed);
            }
            orientation = abs(360 - orientation);
        }
    }
    //else go get a human
    else
    {
        //if you dont have a target, which ofcourse you wont have at the start, get a target
        if (!hasTarget)
        {
            int indexOfHuman = 0;
            float currentDistance = 0;
            float nearestDistance = calculateDistance(myPoint, humanList[0].getPosition());
			// Find the closest human and set it as its target
            for (int i = 1; i < size; i++) 
            {
                //calculate distance of this human
                currentDistance = calculateDistance(myPoint, humanList[i].getPosition());
                if (currentDistance < nearestDistance)
                {
                    nearestDistance = currentDistance;
                    indexOfHuman = i;
                }
                //we got the closeset human
                humanToPick = humanList[indexOfHuman]; //saving the human just in case
                target = humanList[indexOfHuman].getPosition();
                hasTarget = true;
            }
        }
        //if u do have the target move to the target using spikeys movement
        else
        {
            int myX = myPoint.getX(); //get your own points
            int myY = myPoint.getY();
            //if you have not picked up the human yet, go to the human!
            if (pickedHuman == NULL)
            {
				//get target points
                int targetX = target.getX(); 
                int targetY = target.getY();
                //go toward human
                if (targetX - followAccuracy > myX)
                    myPoint.setX(myX + speed);
                else if (targetX + followAccuracy < myX)
                    myPoint.setX(myX - speed);
                //go toward ship Y
                if (targetY - followAccuracy > myY)
                    myPoint.setY(myY + speed);
                else if (targetY + followAccuracy < myY)
                    myPoint.setY(myY - speed);
            }
            //you have the  human,go to top now!
            else{
                myPoint.setY(myY - speed);
                pickedHuman->updatePosition({0,0}, 0 , myPoint, mCTexture->mHeight);
                if (pickedHuman->getPosition().getY() >= DisplayManager::SCREEN_WIDTH || pickedHuman->getPosition().getY() <= 140)
                    pickedHuman->setState(FALLING);
            }
        }
    }
}

// picking up the human
void Bugeye::pickHuman()
{
    pick = true;
    picked = true;
}

// render the bugeye in the cameraview
void Bugeye::render(Point cameraPoint)
{
    if (animation < 15)
        animation++;
    else
        animation = 0;

    SDL_Rect clip = {(128 * animation), 0, 128, 128};
    DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight, this->myPoint, cameraPoint, &clip, 0, NULL, SDL_FLIP_NONE);
}

// FireWeapon method
void Bugeye::fireWeapon(TargetedWeapon** &weaponList, int &size, Point spaceShipPos){

}


// Get the height and width of the bugeye
int Bugeye::getWidth() {
        return 128;
}
int Bugeye::getHeight() {
        return 128;
}
 
// Return the picked human
Human* Bugeye::getHuman(){
    return pickedHuman;
}
// Return whether bugeye has picked or not
bool Bugeye::getPick(){
    return pick;
}
// Set the pickedHuman as the human who was picked up by bugeye
void Bugeye::setHuman(Human* theHuman){
    pickedHuman = theHuman;
}
