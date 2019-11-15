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
    weaponList = NULL;
    init();
}

GameFrame::~GameFrame(){
    if (spaceShip != NULL)
        delete spaceShip;
    if (camera != NULL)
        delete camera;
    if (weaponList != NULL){
        for (int i = 0; i < weaponListSize; i++){
            delete weaponList[i];
        }
        delete [] weaponList;
    }
        
}

void GameFrame::init(){
    if (spaceShip == NULL)
        spaceShip = new SpaceShip();
    if (camera == NULL)
        camera = new Camera();

}

bool GameFrame::isInScreen(Point point){
    bool check = true;
    point = getRenderPointFor(point, camera->getPoint());
    if (point.getX() < 0 || point.getX() > SCREEN_WIDTH)
        check = false;
    if (point.getY() < 0 || point.getY() > SCREEN_HEIGHT)
        check = false;
    return check;
}


void GameFrame::updateUI(SDL_Renderer* gRenderer){
    //update all actors before updating the UI
    updateAllActors();
    //now render the background and spaceship
    camera->render(gRenderer, spaceShip->getHealthStatus(), spaceShip->getFuelStatus(), coins, score, highScore, spaceShip->getMissileCountdown(), spaceShip->getClearScreenCountdown());
    spaceShip->render(gRenderer, camera->getPoint());
    //render weapons
    for (int i = 0; i < weaponListSize; i++){
        if (isInScreen(weaponList[i]->getPosition()))
            weaponList[i]->render(gRenderer, camera->getPoint());
    }
}

void GameFrame::updateSpaceshipPosition(Orientation orientation){
    //we calculate the initial and final ship position and give them to camera positioning
    Point shipInitialPoint = spaceShip->getPoint();
    spaceShip->setOrientation(orientation);
    spaceShip->updatePosition();
    Point shipFinalPoint = spaceShip->getPoint();
    camera->updateCameraPosition(shipInitialPoint, shipFinalPoint);
}

void GameFrame::updateAllActors(){
    //update weapons
    for (int i = 0; i < weaponListSize; i++){
        weaponList[i]->updatePosition();
    }
}

void GameFrame::fire(bool* keyList){
    if (keyList[BULLET_KEY]){
        spaceShip->fireBullet(weaponList, weaponListSize);
    }
    if (keyList[MISSILE_KEY]){
        
    }
    if (keyList[DESTRUCTION_KEY]){
        
    }
}