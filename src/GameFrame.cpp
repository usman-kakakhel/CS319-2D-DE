#include "GameFrame.h"

GameFrame::GameFrame(){
    spaceShip = NULL;
    camera = NULL;
    init();
}

GameFrame::~GameFrame(){
    if (spaceShip == NULL)
        delete spaceShip;
    if (camera == NULL)
        delete camera;
}

void GameFrame::init(){
    if (spaceShip == NULL)
        spaceShip = new SpaceShip();
    if (camera == NULL)
        camera = new Camera();
}


void GameFrame::updateUI(SDL_Renderer* gRenderer){
    //now render the background and spaceship
    camera->render(gRenderer);
    spaceShip->render(gRenderer, camera->getPoint());
}

void GameFrame::updateSpaceshipPosition(Orientation orientation){
    //we calculate the initial and final ship position and give them to camera positioning
    Point shipInitialPoint = spaceShip->getPoint();
    spaceShip->setOrientation(orientation);
    spaceShip->updatePosition();
    Point shipFinalPoint = spaceShip->getPoint();
    camera->updateCameraPosition(shipInitialPoint, shipFinalPoint);
}