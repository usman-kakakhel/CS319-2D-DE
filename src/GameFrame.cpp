#include "GameFrame.h"
int DisplayManager::SCREEN_WIDTH = 0;
int DisplayManager::SCREEN_HEIGHT = 0;
int DisplayManager::GAME_WIDTH = 0;

GameFrame::GameFrame(int SCREEN_WIDTH, int SCREEN_HEIGHT, int GAME_WIDTH){
    DisplayManager::SCREEN_WIDTH = SCREEN_WIDTH;
    DisplayManager::SCREEN_HEIGHT = SCREEN_HEIGHT;
    DisplayManager::GAME_WIDTH = GAME_WIDTH;
    
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