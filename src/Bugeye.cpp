#include "Bugeye.h"

bool Bugeye::picked = false;

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
        //if you dont have a target, which ofcourse you wont have at the start u alien, get a target
        if (!hasTarget)
        {
            int indexOfHuman = 0;
            float currentDistance = 0;
            float nearestDistance = calculateDistance(myPoint, humanList[0].getPosition());
            for (int i = 1; i < size; i++) //for all available humans
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
        //if u do have the target move to the yaindu using spikeys movement
        else
        {
            int myX = myPoint.getX(); //get your own points
            int myY = myPoint.getY();
            //if you dont have the human, go to the human!
            if (pickedHuman == NULL)
            {
                int targetX = target.getX(); //get target points
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
            //you have the  human,go now!
            else{
                myPoint.setY(myY - speed);
                pickedHuman->updatePosition({0,0}, 0 , myPoint, mCTexture->mHeight);
                if (pickedHuman->getPosition().getY() >= DisplayManager::SCREEN_WIDTH || pickedHuman->getPosition().getY() <= 140)
                    pickedHuman->setState(FALLING);
            }
        }
    }
}

void Bugeye::pickHuman()
{
    pick = true;
    picked = true;
}

void Bugeye::render(Point cameraPoint)
{
    if (animation < 15)
        animation++;
    else
        animation = 0;

    SDL_Rect clip = {(128 * animation), 0, 128, 128};
    DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight, this->myPoint, cameraPoint, &clip, 0, NULL, SDL_FLIP_NONE);
}

void Bugeye::fireWeapon(TargetedWeapon** &weaponList, int &size, Point spaceShipPos){

}

int Bugeye::getWidth() {
        return 128;
}

int Bugeye::getHeight() {
        return 128;
}
 

Human* Bugeye::getHuman(){
    return pickedHuman;
}
bool Bugeye::getPick(){
    return pick;
}
void Bugeye::setHuman(Human* theHuman){
    pickedHuman = theHuman;
}
