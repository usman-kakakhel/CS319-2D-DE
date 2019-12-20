#include "WarpZone.h"
#include <cstdlib>

WarpZone::WarpZone(Point startPoint, Point endPoint ) {
    startPos = startPoint;
    endPos = endPoint;
    //make textures
    mCTexture = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(warpSprite, mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight);
}
WarpZone::~WarpZone() {
    if (mCTexture != NULL){
        delete mCTexture->mTexture;
        delete mCTexture;
    }
}
Point WarpZone::getStartPos() {
    return startPos;
}
void WarpZone::setStartPos(int x, int y) {
    startPos.setX(x);
    startPos.setY(y);
}
Point WarpZone::getEndPos() {
    return endPos;
}
void WarpZone::setEndPos(int x, int y) {
    endPos.setX(x);
    endPos.setY(y);
}

int WarpZone::getWidth() {
	return 192;
}

int WarpZone::getHeight() {
	return 192;
}

bool WarpZone::getToBeDestroyed(){
    return toBeDestroyed;
}
void WarpZone::setToBeDestroyed(bool toBeDestroyed){
    this->toBeDestroyed = toBeDestroyed;
}

void WarpZone::render( Point cameraPoint) {
    if (animation < 18)
            animation++;
    else
            animation = 1;
        
    SDL_Rect clip = { (192 * (animation % 5)), (192 * (animation / 5)), 192, 192 };
    // Render the starting point of warpzone
    DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight,startPos, cameraPoint, &clip, 0, NULL, SDL_FLIP_NONE);
    
    // Render the ending point of the warpzone
    DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight, endPos, cameraPoint, &clip, 0, NULL, SDL_FLIP_NONE);
}


