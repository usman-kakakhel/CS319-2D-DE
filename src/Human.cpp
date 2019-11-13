#include "Human.h"

Human::Human(int x) {
    position.setX(x);
    position.setY(550);
    state = true;
    // If we are going to have orientation, then we might need another orientation in MyEnums class called humanOrientation.
    // orientation = UP;
}
Human::~Human() {

}
// Orientation Human::getOrientation() {
//     return orientation;
// }
// void Human::setOrientation(Orientation newOrient) {
//     orientation = newOrient;
// }
bool Human::getState() {
    return state;
}
void Human::setState(bool newState) {
    state = newState;
}
Point Human::getPosition() {
    return position;
}
void Human::setPosition(int x, int y) {
    position.setX(x);
    position.setY(y);
}

void Human::render(SDL_Renderer* gRenderer, Point cameraPoint) {
    DisplayManager::render(gRenderer, sprite,
         position, cameraPoint, NULL, 0, NULL, SDL_FLIP_NONE);
}