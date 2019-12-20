#include "MapView.h"

MapView::MapView(Point position){
    this->position = position;
    //texture of backplate of map
    mCTextureBG = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(bGSprite, mCTextureBG->mTexture, mCTextureBG->mWidth, mCTextureBG->mHeight);

    //texture of background of map
    mCTexture = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(gameBGSprite, mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight);

    //texture of spaceship
    mCTextureShip = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(shipSprite, mCTextureShip->mTexture, mCTextureShip->mWidth, mCTextureShip->mHeight);

    //texture of human
    mCTextureHuman = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(humanSprite, mCTextureHuman->mTexture, mCTextureHuman->mWidth, mCTextureHuman->mHeight);

    //texture of enenmy
    mCTextureEnemy = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(enemySprite, mCTextureEnemy->mTexture, mCTextureEnemy->mWidth, mCTextureEnemy->mHeight);
}
MapView::~MapView(){
    if (mCTextureBG != NULL){
        delete mCTextureBG->mTexture;
        delete mCTextureBG;
    }

    if (mCTexture != NULL){
        delete mCTexture->mTexture;
        delete mCTexture;
    }

    if (mCTextureShip != NULL){
        delete mCTextureShip->mTexture;
        delete mCTextureShip;
    }

    if (mCTextureHuman != NULL){
        delete mCTextureHuman->mTexture;
        delete mCTextureHuman;
    }

    if (mCTextureEnemy != NULL){
        delete mCTextureEnemy->mTexture;
        delete mCTextureEnemy;
    }
}

void MapView::render(SpaceShip* spaceShip, Enemy** enemyList, int enemyListSize, Human* humanList, int humanListSize, Point camPoint){
    //rendering the base for map
    DisplayManager::render(mCTextureBG->mTexture, 540, mCTextureBG->mHeight / 3, position, 0);
    

    //base background for map
    Point newPoint(position.getX() + 5, position.getY() + 4); // my origin point
    DisplayManager::render(mCTexture->mTexture, 530, 80, newPoint, 0);
    SDL_Rect clip = { 960, 0, 265, 80 };//690, 1080 
    DisplayManager::render(mCTexture->mTexture, 265, 80, {newPoint.getX() + 40, newPoint.getY()}, 0, &clip);

    Point temp;
    //spaceship on map
    if (spaceShip != NULL){
        temp.setX((int)(spaceShip->getPoint().getX() * 530/(double)DisplayManager::GAME_WIDTH) + newPoint.getX());
        temp.setY((int)(spaceShip->getPoint().getY() * 80/(double)DisplayManager::SCREEN_HEIGHT)+ newPoint.getY());
        double tempX = (mCTextureShip->mWidth * 530/(double)DisplayManager::GAME_WIDTH);
        double tempY = (mCTextureShip->mHeight * 80/(double)DisplayManager::SCREEN_HEIGHT);
        DisplayManager::render(mCTextureShip->mTexture,  (int)tempX/3, (int)tempY/3, temp, 0, NULL, 0); 
    }
    
    //enenmies on map
    for (int i = 0; i < enemyListSize; i++){
        temp.setX((int)(enemyList[i]->getPosition().getX() * 530/(double)DisplayManager::GAME_WIDTH) + newPoint.getX());
        temp.setY((int)(enemyList[i]->getPosition().getY() * 80/(double)DisplayManager::SCREEN_HEIGHT)+ newPoint.getY());
        double tempX = (mCTextureEnemy->mWidth * 530/(double)DisplayManager::GAME_WIDTH);
        double tempY = (mCTextureEnemy->mHeight * 80/(double)DisplayManager::SCREEN_HEIGHT);
        DisplayManager::render(mCTextureEnemy->mTexture,  (int)tempX/3, (int)tempY/3, temp, 0, NULL, 0);
    }   

    //humans on map
    for (int i = 0; i < humanListSize; i++){
        temp.setX((int)(humanList[i].getPosition().getX() * 530/(double)DisplayManager::GAME_WIDTH) + newPoint.getX());
        temp.setY((int)(humanList[i].getPosition().getY() * 80/(double)DisplayManager::SCREEN_HEIGHT)+ newPoint.getY());
        double tempX = (mCTextureHuman->mWidth * 530/(double)DisplayManager::GAME_WIDTH);
        double tempY = (mCTextureHuman->mHeight * 80/(double)DisplayManager::SCREEN_HEIGHT);
        DisplayManager::render(mCTextureHuman->mTexture,  (int)tempX/3, (int)tempY/3, temp, 0, NULL, 0);
    }

    //boundary for reference
    temp.setX((int)(camPoint.getX() * 530/(double)DisplayManager::GAME_WIDTH) + newPoint.getX());
    temp.setY((int)(camPoint.getY() * 80/(double)DisplayManager::SCREEN_HEIGHT)+ newPoint.getY());
    Point temp2;
    temp2.setX(temp.getX());
    temp2.setY(temp.getY() + 80);
    int offset =  + ((double)DisplayManager::SCREEN_WIDTH * 530/ (double)DisplayManager::GAME_WIDTH);
    SDL_SetRenderDrawColor( DisplayManager::gRenderer, 0xFF, 0x00, 0x00, 0x00 );
    SDL_RenderDrawLine(DisplayManager::gRenderer, temp.getX(), temp.getY(), temp2.getX(), temp2.getY());
    SDL_RenderDrawLine(DisplayManager::gRenderer, temp.getX() + offset, temp.getY(), temp2.getX() + offset, temp2.getY());
    SDL_SetRenderDrawColor( DisplayManager::gRenderer, 0x00, 0x00, 0x00, 0x00 );
}   