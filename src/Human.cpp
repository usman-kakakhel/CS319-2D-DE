#include "Human.h"

Human::Human(Point thePoint) {
    position.setX(thePoint.getX());
    position.setY(thePoint.getY());
    state = IDLE;

    mCTexture = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(humanSprite, mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight);
}
Human::~Human() {
    if (mCTexture != NULL){
        delete mCTexture->mTexture;
        delete mCTexture;
    }
}

HumanState Human::getState() {
    return state;
}
void Human::setState(HumanState newState) {
    state = newState;
}

void Human::setToBeDestroyed(bool toBeDestroyed) {
	this->toBeDestroyed = toBeDestroyed;
}

bool Human::getToBeDestroyed() {
	return this->toBeDestroyed;
}

Point Human::getPosition() {
    return position;
}
void Human::setPosition(Point thePoint) {
    position.setX(thePoint.getX());
    position.setY(thePoint.getY());
}

void Human::updatePosition(Point spaceShipPosition, int spaceShipHeight, Point bugeyePosition, int bugeyeHeight) {
	if(this->state == PICKED_BY_ENEMY) {
		int y = (int)(round(bugeyePosition.getY() + (bugeyeHeight * 0.3)));
		Point p(bugeyePosition.getX() + mCTexture->mWidth/2, y);
		this->setPosition(p);
	}
	else if(this->state == PICKED_BY_SPACESHIP) {
		int y = (int)(round(spaceShipPosition.getY() + (spaceShipHeight * 0.30)));
		Point p(spaceShipPosition.getX()+ mCTexture->mWidth/2, y);
		this->setPosition(p);
	}
	else if(this->state == FALLING) {
		Point p(this->getPosition().getX(), 3 + this->getPosition().getY());
        this->setPosition(p);
	}
}

int Human::getWidth() {
	return (int)(mCTexture->mWidth);
}

int Human::getHeight() {
        return (int)(mCTexture->mHeight);
}

void Human::render( Point cameraPoint) {
    DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth , mCTexture->mHeight , position, cameraPoint, NULL, 0, NULL, SDL_FLIP_NONE);
}

void Human::operator=(Human const &myHuman){
    position = myHuman.position;
    state = myHuman.state;
    toBeDestroyed = myHuman.toBeDestroyed;
}