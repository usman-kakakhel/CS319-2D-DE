#include "SkinItem.h"

SkinItem::SkinItem() {
    name = "Skin Item";
}
SkinItem::~SkinItem() {

}
string SkinItem::getName() {
    return name;
}
void SkinItem::setName(string newName) {
    name = newName;
}

// Does it need to be rendered or not? If yes, then we need a Point for it
// void ShieldItem::render(SDL_Renderer* gRenderer, Point cameraPoint) {
//             DisplayManager::render(gRenderer, sprite,
//                 Point(), cameraPoint, NULL, 0, NULL, SDL_FLIP_NONE);
// }