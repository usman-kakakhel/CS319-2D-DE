#include "GameFrame.h"
int DisplayManager::SCREEN_WIDTH = 0;
int DisplayManager::SCREEN_HEIGHT = 0;
int DisplayManager::GAME_WIDTH = 0;

GameFrame::GameFrame(int SCREEN_WIDTH, int SCREEN_HEIGHT, int GAME_WIDTH){
    DisplayManager::SCREEN_WIDTH = SCREEN_WIDTH;
    DisplayManager::SCREEN_HEIGHT = SCREEN_HEIGHT;
    DisplayManager::GAME_WIDTH = GAME_WIDTH;
    //setting seed
    srand(time(0));
    
    spaceShip = NULL;
    camera = NULL;
    weaponList = NULL;
    humanList = NULL;
    enemyList = NULL;
    asteroid = NULL;
    
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
    if (humanList != NULL){
        delete [] humanList;
    }
    if (asteroid != NULL){
        delete asteroid;
    }     
    if (enemyList != NULL){
        for (int i = 0; i < enemyListSize; i++){
            delete enemyList[i];
        }
        delete [] enemyList;
    }    
}

void GameFrame::init(){
    if (spaceShip == NULL)
        spaceShip = new SpaceShip();
    if (camera == NULL)
        camera = new Camera();

    addHumans();
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
    //render humans
    for (int i = 0; i < humanListSize; i++){
        if (isInScreen(humanList[i].getPosition()))
            humanList[i].render(gRenderer, camera->getPoint());
    }
    //render asteroid
    if (isInScreen(asteroid->getPosition()))
        asteroid->render(gRenderer, camera->getPoint());
    //render enenmes
    for (int i = 0; i < enemyListSize; i++){
        if (isInScreen(enemyList[i]->getPoint()))
            enemyList[i]->render(gRenderer, camera->getPoint());
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
    //updating and creating asteroids
    addAsteroids();
    if (asteroid != NULL)
        asteroid->updatePosition();
    
    //updating and creating Enenmies
    addEnemy();
    for (int i = 0; i < enemyListSize; i++){
        enemyList[i]->updatePosition(spaceShip->getPoint());
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


void GameFrame::addHumans(){
    humanListSize = 10;
    humanList = new Human[humanListSize];

    for (int i = 0; i < 10; i++){
        Point a((GAME_WIDTH/10) *  i, SCREEN_HEIGHT  - 200);
        Human* newHuman = new Human(a);

        humanList[i] = *newHuman;
    }
}

void GameFrame::addAsteroids(){
    if (asteroid == NULL || asteroid->getPosition().getY() >= SCREEN_HEIGHT || asteroid->getPosition().getY() < 0){
        if (asteroid != NULL)
            delete asteroid;   
        int x  = (SCREEN_WIDTH * (rand() / (RAND_MAX + 1.0))) + camera->getPoint().getX();
        int randAngle = (90 * (rand() / (RAND_MAX + 1.0))) + 135;
        coins = randAngle;
        Point newPos(x, 0);
        asteroid = new Asteroid(newPos,  40, 100,  randAngle);
    }
}

void GameFrame::addEnemy(){
    int maxEnemies = (GAME_WIDTH / SCREEN_WIDTH) * 3;
    if (enemyListSize < maxEnemies){
        Point newPos((GAME_WIDTH * (rand() / (RAND_MAX + 1.0))), (SCREEN_HEIGHT * (rand() / (RAND_MAX + 1.0))));
        int orientation = (360 * (rand() / (RAND_MAX + 1.0)));
        //make a new list of enemies
        enemyListSize++;
        Enemy** newList = new Enemy*[enemyListSize];
        
        //copy existing list to new one
        for (int i = 0; i < enemyListSize - 1; i++){
            newList[i] = enemyList[i];
        }
        //new enemy
        //newList[(enemyListSize - 1)] = new Saucer(newPos, 5, orientation, weaponList, weaponListSize, spaceShip->getPoint());
        newList[(enemyListSize - 1)] = new Saucer(newPos, 5, orientation);
        //delete existing list
        delete [] enemyList;

        enemyList = newList;
    }
}