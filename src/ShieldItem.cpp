#include "ShieldItem.h"

ShieldItem::ShieldItem() {
    name = "Shield Item";
}
ShieldItem::~ShieldItem() {

}
string ShieldItem::getName() {
    return name;
}
void ShieldItem::setName(string newName) {
    name = newName;
}
// Does it need to be rendered or not? If yes, then we need a Point for it
// void ShieldItem::render(SDL_Renderer* gRenderer, Point cameraPoint) {
//             DisplayManager::render(gRenderer, sprite,
//                 Point(), cameraPoint, NULL, 0, NULL, SDL_FLIP_NONE);
// }