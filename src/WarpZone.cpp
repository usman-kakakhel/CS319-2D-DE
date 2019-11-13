#include "WarpZone.h"
#include <cstdlib>

WarpZone::WarpZone() {
    int x = rand() % 5000;
    int y = rand() % 700;
    startPos.setX(x);       // 5000 is the maximum width of the game, I guess
    startPos.setY(y);        // Height is 768 so warpzone should be between these limits

    // New position for the spaceship to be spawned at
    int newX = rand() % 500;
    int newY = rand() % 700;
    endPos.setX(newX);
    endPos.setY(newY);
}
WarpZone::~WarpZone() {

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

void WarpZone::render(SDL_Renderer* gRenderer, Point cameraPoint) {
    // Render the starting point of warpzone
    DisplayManager::render(gRenderer, sprite,
         startPos, cameraPoint, NULL, 0, NULL, SDL_FLIP_NONE);
    
    // Render the ending point of the warpzone
    DisplayManager::render(gRenderer, sprite,
         endPos, cameraPoint, NULL, 0, NULL, SDL_FLIP_NONE);
}