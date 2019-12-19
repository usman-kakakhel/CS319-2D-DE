#include "GameFrame.h"


GameFrame::GameFrame(){
    //setting seed
    srand(time(0));
    
    spaceShip = NULL;
    camera = NULL;
    weaponList = NULL;
    humanList = NULL;
    enemyList = NULL;
    asteroid = NULL;
    warpZone = NULL;
    healthPickup = NULL;
    fuelPickup = NULL;
    explosionList = NULL;
}

GameFrame::~GameFrame(){
    destroy();
}

void GameFrame::destroy(){
    //update highscore if needed
    if( spaceShip != NULL && camera != NULL){
	    int temp = spaceShip->getScore();
        DataManager::saveHighScore(temp);
    }

    if (spaceShip != NULL)
        delete spaceShip;
    spaceShip = NULL;

    if (camera != NULL)
        delete camera;
    camera = NULL;

    if (weaponList != NULL){
        for (int i = 0; i < weaponListSize; i++){
            delete weaponList[i];
            weaponList[i] = NULL;
        }
        delete [] weaponList;
    }
    weaponList = NULL;
    weaponListSize = 0;

    if (humanList != NULL){
        delete [] humanList;
    }
    humanList = NULL;
    humanListSize = 0;

    if (asteroid != NULL){
        delete asteroid;
    }
    asteroid = NULL;  

    if (enemyList != NULL){
        for (int i = 0; i < enemyListSize; i++){
            delete enemyList[i];
            enemyList[i] = NULL;
        }
        delete [] enemyList;
    }
    enemyListSize = 0;
    enemyList = NULL;

    if (warpZone != NULL)
        delete warpZone;
    warpZone = NULL;

    if (healthPickup != NULL)
        HealthPickup::deleteInstance();
    healthPickup = NULL;

    if (fuelPickup != NULL)
        FuelPickup::deleteInstance();
    fuelPickup = NULL;

    if (explosionList != NULL){
        for (int i = 0; i < explosionListSize; i++){
            delete explosionList[i];
            explosionList[i] = NULL;
        }
        delete [] explosionList;
    }
    explosionListSize = 0;
    explosionList = NULL;

    Bugeye::picked = false;
    
    if (pickupSound != NULL){
		//Free the sound effects
		Mix_FreeChunk( pickupSound);
		pickupSound = NULL;
	}
}

void GameFrame::init(){
    if (spaceShip == NULL)
        spaceShip = new SpaceShip();
    if (camera == NULL)
        camera = new Camera();

    addHumans();

     //Load sound effects
    pickupSound = Mix_LoadWAV( "../resources/Sounds/pickup.wav" );
    if( pickupSound == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    //get highscore from the file
    int temp = DataManager::loadHighScore();
    camera->setHighScore(temp);
}

bool GameFrame::isInScreen(Point point){
    bool check = true;
    point = DisplayManager::getRenderPointFor(point, camera->getPoint());
    if (point.getX() < 0 || point.getX() > DisplayManager::SCREEN_WIDTH)
        check = false;
    if (point.getY() < 0 || point.getY() > DisplayManager::SCREEN_HEIGHT)
        check = false;
    return check;
}


void GameFrame::updateUI(GameState* state, int coins){

    //now render the background and spaceship
    if (camera != NULL)
        camera->render(spaceShip->getHealthStatus(), spaceShip->getFuelStatus(), coins, spaceShip->getScore(), spaceShip->getMissileCountdown(), spaceShip->getNuclearBombCountdown());
    
    //render spaceship
    if (spaceShip != NULL && !spaceShip->getToBeDestroyed())
        spaceShip->render(camera->getPoint());
    //render weapons
    for (int i = 0; i < weaponListSize; i++){
        if (isInScreen(weaponList[i]->getPosition()))
            weaponList[i]->render(camera->getPoint());
    }
    //render humans
    for (int i = 0; i < humanListSize; i++){
        if (isInScreen(humanList[i].getPosition()))
            humanList[i].render(camera->getPoint());
    }
    //render asteroid
    if (asteroid != NULL && isInScreen(asteroid->getPosition()))
        asteroid->render(camera->getPoint());
    //render enemies
    for (int i = 0; i < enemyListSize; i++){
        if (isInScreen(enemyList[i]->getPosition()))
            enemyList[i]->render(camera->getPoint());
    }

    //render the warp zone
    if (warpZone != NULL && (isInScreen(warpZone->getStartPos()) || isInScreen(warpZone->getEndPos())))
        warpZone->render(camera->getPoint());

    //update the mapview on top to show all actors
    if (camera != NULL)
        camera->updateMap(spaceShip, enemyList, enemyListSize, humanList, humanListSize);

    //render any fuel and health drops available
    if (healthPickup != NULL)
        healthPickup->render(camera->getPoint());
    if (fuelPickup != NULL)
        fuelPickup->render(camera->getPoint());

    //render any possible explosions
    for (int i = 0; i < explosionListSize; i++){
        if (isInScreen(explosionList[i]->getPos()))
            explosionList[i]->render(camera->getPoint());
    }

    if (*state == GAME_OVER){
        camera->showGameOver();
    }
}


void GameFrame::updateAllActors(bool* keyList, GameState* state, Item** boughtHealthItems, int boughtHealthItemsSize, Item** boughtFuelItems, int boughtFuelItemsSize, int& coins){

    //update all actions of spaceship
    if (camera != NULL && spaceShip != NULL){
        Point shipInitialPoint = spaceShip->getPoint();
        spaceShip->controlSpaceship(keyList, weaponList, weaponListSize, enemyList, enemyListSize, camera->getPoint());
        Point shipFinalPoint = spaceShip->getPoint();
        camera->updateCameraPosition(shipInitialPoint, shipFinalPoint);

	for(int i = 0; i < boughtHealthItemsSize; i++) {
		spaceShip->setMaxHealth(spaceShip->getMaxHealth() + boughtHealthItems[i]->getAmount());
	}
	for(int i = 0; i < boughtFuelItemsSize; i++) {
		spaceShip->setMaxFuel(spaceShip->getMaxFuel() + boughtFuelItems[i]->getAmount());
	}

    }

    //check score here
    if(spaceShip->getScore() >= camera->getHighScore()){
        camera->setHighScore(spaceShip->getScore());
    }

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
        enemyList[i]->updatePosition(spaceShip->getPoint(), humanList, humanListSize);
        if (isInScreen(enemyList[i]->getPosition()))
            enemyList[i]->fireWeapon(weaponList, weaponListSize, spaceShip->getPoint());
    }

    //fix for enemy running out of boundds sometimes
    for (int i = 0; i < enemyListSize; i++){
        Point temp;
        if(enemyList[i]->getPosition().getY() < 139){
            temp.setX(enemyList[i]->getPosition().getX());
            temp.setY(145);
            enemyList[i]->setPosition(temp);
        }
    }

    //updating the human position
    for (int i = 0; i < humanListSize; i++){
        if (humanList[i].getState() == FALLING){
            humanList[i].updatePosition({0,0}, 0, {0,0}, 0);
        }
    }

    //add the warpZone on the screen
    addWarpZone();

    //add the pickups
    addPickup();

    //detect collisions
    detectCollisions(coins);

    //remove any useless actors
    removeActors(state);
}



void GameFrame::addHumans(){
    humanListSize = 10;
    humanList = new Human[humanListSize];

    for (int i = 2; i <= 11; i++){
        Point a((DisplayManager::GAME_WIDTH/13) *  i, DisplayManager::SCREEN_HEIGHT  - 165);
        Human* newHuman = new Human(a);

        humanList[i - 2] = *newHuman;
    }
}

void GameFrame::addAsteroids(){
    if (asteroid == NULL || asteroid->getPosition().getY() >= DisplayManager::SCREEN_HEIGHT || asteroid->getPosition().getY() < 0){
        if (asteroid != NULL)
            delete asteroid;   
        int x  = (DisplayManager::SCREEN_WIDTH * (rand() / (RAND_MAX + 1.0))) + camera->getPoint().getX();
        int randAngle = (90 * (rand() / (RAND_MAX + 1.0))) + 135;
        Point newPos(x, 0);
        asteroid = new Asteroid(newPos,  15, 50,  randAngle);
    }
}

void GameFrame::addEnemy(){
    int maxEnemies = (DisplayManager::GAME_WIDTH / DisplayManager::SCREEN_WIDTH) * 3;
    if (enemyListSize < maxEnemies){
        Point newPos(0,0);
        do{
            int xPos = (DisplayManager::GAME_WIDTH * (rand() / (RAND_MAX + 1.0)));
            int yPos = (DisplayManager::SCREEN_HEIGHT * (rand() / (RAND_MAX + 1.0)));
            newPos.setX(xPos);
            newPos.setY(yPos);
        } while (isInScreen(newPos) || newPos.getY() >= DisplayManager::SCREEN_HEIGHT - (DisplayManager::SCREEN_HEIGHT / 5) || newPos.getY() <= 180);

        int orientation = (360 * (rand() / (RAND_MAX + 1.0)));
        //make a new list of enemies
        enemyListSize++;
        Enemy** newList = new Enemy*[enemyListSize];
        
        //copy existing list to new one
        for (int i = 0; i < enemyListSize - 1; i++){
            newList[i] = enemyList[i];
        }
        //new enemy
        if (humanListSize > 0){
            int random = rand() % 6;
            switch (random){
                case 0:
                    newList[(enemyListSize - 1)] = new Saucer(newPos, 3, orientation);
                    break;
                case 1:
                    newList[(enemyListSize - 1)] = new Bugeye(newPos, 3, orientation);
                    break;
                case 2:
                    newList[(enemyListSize - 1)] = new Saucer(newPos, 3, orientation);
                    //newList[(enemyListSize - 1)] = new Crescent(newPos, 5, orientation);
                    break;
                case 3:
                    newList[(enemyListSize - 1)] = new SaucerBlades(newPos, 4, orientation);
                    break;
                case 4:
                    newList[(enemyListSize - 1)] = new Slicer(newPos, 3, orientation);
                    break;
                case 5:
                    newList[(enemyListSize - 1)] = new Spikey(newPos, 2, orientation);
                    break;
            }
        }
        else{
            newList[(enemyListSize - 1)] = new Crescent(newPos, 5, orientation);
        }
        

        //delete existing list
        if (enemyList != NULL)
            delete [] enemyList;

        enemyList = newList;
    }
}


void GameFrame::addWarpZone(){
    if (warpZone == NULL){
        //start pos of warpZone
        Point startPos;
        Point endPos;
        do
        {
            {
                int x,y;
                do {
                    x = rand() % DisplayManager::GAME_WIDTH;
                    y = (rand() % DisplayManager::SCREEN_HEIGHT / 3) + DisplayManager::SCREEN_HEIGHT / 3;
                }while(x < DisplayManager::GAME_WIDTH / 7 ||  x > DisplayManager::GAME_WIDTH - (DisplayManager::GAME_WIDTH / 9));
                
                
                startPos.setX(x);       
                startPos.setY(y);
            }

            
            {
                int x,y;
                do {
                    x = rand() % DisplayManager::GAME_WIDTH;
                    y = (rand() % DisplayManager::SCREEN_HEIGHT / 3) + DisplayManager::SCREEN_HEIGHT / 3;
                }while(x < DisplayManager::GAME_WIDTH / 7 ||  x > DisplayManager::GAME_WIDTH - (DisplayManager::GAME_WIDTH / 9));
                
                
                endPos.setX(x);       
                endPos.setY(y);
            }
        } while (abs(startPos.getX() - endPos.getX()) < DisplayManager::SCREEN_WIDTH);
        
        
        warpZone = new WarpZone(startPos, endPos);
    }
}


void GameFrame::addPickup(){
    Point newPos;
    //calculate the place where the fuel pickup is dropped
    do{
        int xPos = (DisplayManager::GAME_WIDTH * (rand() / (RAND_MAX + 1.0)));
        int yPos = (DisplayManager::SCREEN_HEIGHT * (rand() / (RAND_MAX + 1.0)));
        if (yPos >= DisplayManager::SCREEN_HEIGHT - (DisplayManager::SCREEN_HEIGHT / 4))
            yPos = yPos - DisplayManager::SCREEN_HEIGHT - (DisplayManager::SCREEN_HEIGHT / 4);
        else if(yPos <= 100)
            yPos = yPos + 100;
        newPos.setX(xPos);
        newPos.setY(yPos);
    } while (!isInScreen(newPos) || newPos.getX() < DisplayManager::GAME_WIDTH / 9 ||  newPos.getX() > DisplayManager::GAME_WIDTH - (DisplayManager::GAME_WIDTH / 9));
    //if the fuel is less than 30 then get the pickup
    if (spaceShip->getFuelStatus() <= 30){
        fuelPickup = FuelPickup::getInstance(newPos, spaceShip->getMaxFuel() - spaceShip->getFuelStatus());
    }
    //calculate the place where the health pickup is dropped
    do{
        int xPos = (DisplayManager::GAME_WIDTH * (rand() / (RAND_MAX + 1.0)));
        int yPos = (DisplayManager::SCREEN_HEIGHT * (rand() / (RAND_MAX + 1.0)));
        if (yPos >= DisplayManager::SCREEN_HEIGHT - (DisplayManager::SCREEN_HEIGHT / 4))
            yPos = yPos - DisplayManager::SCREEN_HEIGHT - (DisplayManager::SCREEN_HEIGHT / 4);
        else if(yPos <= 100)
            yPos = yPos + 100;
        newPos.setX(xPos);
        newPos.setY(yPos);
    } while (!isInScreen(newPos) || newPos.getX() < DisplayManager::GAME_WIDTH / 9 ||  newPos.getX() > DisplayManager::GAME_WIDTH - (DisplayManager::GAME_WIDTH / 9));
    //if the health is less than 30 then make the pickup
    if (spaceShip->getHealthStatus() <= 30){
        healthPickup = HealthPickup::getInstance(newPos, spaceShip->getMaxHealth() - spaceShip->getHealthStatus());
    }
}

void GameFrame::addExplosion(Point thePoint){
    //make a new list of explosions
    explosionListSize++;
    Explosion** newList = new Explosion*[explosionListSize];
    
    //copy existing list to new one
    for (int i = 0; i < explosionListSize - 1; i++){
        newList[i] = explosionList[i];
    }
    //new explosions
    Explosion* newExp = new Explosion(thePoint);
    
    newList[explosionListSize - 1] = newExp;
    //delete existing list
    if (explosionList != NULL)
        delete [] explosionList;

    explosionList = newList;
}


void GameFrame::removeActors(GameState* state){
    //check weapons for out of screen deletion
    {
    bool* toBeDestroyed = NULL;
    if (weaponListSize > 0)
        toBeDestroyed = new bool[weaponListSize];
	int numToBeKept = 0;

	for(int i = 0; i < weaponListSize; i++) {
		toBeDestroyed[i] = false;
	}

	for(int i = 0; i < weaponListSize; i++){
		//checking whether the bullet is out of bounds
		bool inScreen = true;

		if(weaponList[i]->getPosition().getX() < camera->getPoint().getX() || weaponList[i]->getPosition().getX() > camera->getPoint().getX() + DisplayManager::SCREEN_WIDTH - 50) {
			inScreen = false;
		}

		//if bullet out of screen mark it as deletion worthy
		if (!inScreen || weaponList[i]->getToBeDestroyed()){
			toBeDestroyed[i] = true;
		}
		else {
			numToBeKept++;
		}
	}
    if (numToBeKept < weaponListSize){
        TargetedWeapon** toBeKept = NULL;
        if (numToBeKept > 0)
            toBeKept = new TargetedWeapon*[numToBeKept];
        //delete the marked bullets
        int tempIndex = 0;
        for(int i = 0; i < weaponListSize; i++) {
            if(toBeDestroyed[i]) {
                delete weaponList[i];
            }
            else {
                toBeKept[tempIndex++] = weaponList[i];
            }
        }

        delete [] weaponList;
        weaponList = toBeKept;
        weaponListSize = numToBeKept;
    }

    if (toBeDestroyed != NULL)
        delete [] toBeDestroyed;
	
    }

    //check enemies to delete if they are marked as to be deleted
    {
    bool* toBeDestroyed = NULL;
    if (enemyListSize > 0)
        toBeDestroyed = new bool[enemyListSize];
	int numToBeKept = 0;

	for(int i = 0; i < enemyListSize; i++) {
		toBeDestroyed[i] = false;
	}

	for(int i = 0; i < enemyListSize; i++){

		//if the enemy is marked as toRemove then remove it
		if (enemyList[i]->getToBeDestroyed() || enemyList[i]->getPosition().getX() < DisplayManager::GAME_WIDTH / 10 || 
            enemyList[i]->getPosition().getX() > DisplayManager::GAME_WIDTH - (DisplayManager::GAME_WIDTH / 10) ||
            enemyList[i]->getPosition().getY() < 135 || enemyList[i]->getPosition().getY() > DisplayManager::SCREEN_HEIGHT  - 140){
			toBeDestroyed[i] = true;
            if (isInScreen(enemyList[i]->getPosition()))
                addExplosion(enemyList[i]->getPosition());
		}
		else {
			numToBeKept++;
		}
	}
    if (numToBeKept < enemyListSize){
        Enemy** toBeKept = NULL;
        if (numToBeKept > 0)
            toBeKept = new Enemy*[numToBeKept];

        int tempIndex = 0;
        for(int i = 0; i < enemyListSize; i++) {
            if(toBeDestroyed[i]) {
                delete enemyList[i];
            }
            else {
                toBeKept[tempIndex++] = enemyList[i];
            }
        }

        delete [] enemyList;
        enemyList = toBeKept;
        enemyListSize = numToBeKept;
    }
    if (toBeDestroyed != NULL)
        delete [] toBeDestroyed;
	
    }

    //check spaceship for out of fuel or if marked as to be deleted
    if (spaceShip != NULL && (spaceShip->getFuelStatus() <= 0 || spaceShip->getToBeDestroyed())){
        //update highscore if needed
        if( spaceShip != NULL && camera != NULL){
            int temp = spaceShip->getScore();
            DataManager::saveHighScore(temp);
        }
        spaceShip->setToBeDestroyed(true);
        *state = GAME_OVER;
    }

    //check warpzone if it is marked to be deleted
    if (warpZone != NULL && (warpZone->getToBeDestroyed())){
        delete warpZone;
        warpZone = NULL;
    }

    //check pickups for out of screen or if marked as to be deleted
    if (fuelPickup != NULL && (!isInScreen(fuelPickup->getPosition()) || fuelPickup->getToBeDestroyed())){
        FuelPickup::deleteInstance();
        fuelPickup = NULL;
    }
    if (healthPickup != NULL && (!isInScreen(healthPickup->getPosition()) || healthPickup->getToBeDestroyed())){
        HealthPickup::deleteInstance();
        healthPickup = NULL;
    }

    //check humans if marked as deleted
    {
    bool* toBeDestroyed = NULL;
    if (humanListSize > 0)
        toBeDestroyed = new bool[humanListSize];
	int numToBeKept = 0;

	for(int i = 0; i < humanListSize; i++) {
		toBeDestroyed[i] = false;
	}

	for(int i = 0; i < humanListSize; i++){
		//if the human is marked as toRemove then remove it
		if (humanList[i].getToBeDestroyed()){
			toBeDestroyed[i] = true;
		}
		else {
			numToBeKept++;
		}
	}
    if (numToBeKept < humanListSize){
        Human* toBeKept = NULL;
        if (numToBeKept > 0)
            toBeKept = new Human[numToBeKept];

        int tempIndex = 0;
        for(int i = 0; i < humanListSize; i++) {
            if(!toBeDestroyed[i]) {
                toBeKept[tempIndex++] = humanList[i];
            }
        }

        delete [] humanList;
        humanList = toBeKept;
        humanListSize = numToBeKept;
    }
    if (toBeDestroyed != NULL)
        delete [] toBeDestroyed;
    }

    //check if asteroid needs to be destroyed
    if (asteroid != NULL && (asteroid->getToBeDestroyed())){
        if (isInScreen(asteroid->getPosition()))
            addExplosion(asteroid->getPosition());
        delete asteroid;
        asteroid = NULL;
    }


    //check if the explosions need to be removed
    {
    bool* toBeDestroyed = NULL;
    if (explosionListSize > 0)
        toBeDestroyed = new bool[explosionListSize];
	int numToBeKept = 0;

	for(int i = 0; i < explosionListSize; i++) {
		toBeDestroyed[i] = false;
	}

	for(int i = 0; i < explosionListSize; i++){
		//if the explosions is marked as toRemove then remove it
		if (explosionList[i]->getToBeDestroyed()){
			toBeDestroyed[i] = true;
		}
		else {
			numToBeKept++;
		}
	}
    if (numToBeKept < explosionListSize){
        Explosion** toBeKept = NULL;
        if (numToBeKept > 0)
            toBeKept = new Explosion*[numToBeKept];

        int tempIndex = 0;
        for(int i = 0; i < explosionListSize; i++) {
            if(!toBeDestroyed[i]) {
                toBeKept[tempIndex++] = explosionList[i];
            }
            else{
                delete explosionList[i];
            }
        }
        delete [] explosionList;
        explosionList = toBeKept;
        explosionListSize = numToBeKept;
    }
    if (toBeDestroyed != NULL)
        delete [] toBeDestroyed;
    }
    
}


void GameFrame::detectCollisions(int& coins) {

	if(collided(spaceShip->getPoint(), spaceShip->getWidth(), spaceShip->getHeight(), asteroid->getPosition(), asteroid->getWidth(), asteroid->getHeight())) {
		asteroid->setToBeDestroyed(true);
		spaceShip->setHealthStatus(spaceShip->getHealthStatus() - asteroid->getDamage());
		if(spaceShip->getHealthStatus() <= 0) {
			spaceShip->setToBeDestroyed(true);
		}
	}

	if(collided(warpZone->getStartPos(), warpZone->getWidth(), warpZone->getHeight(), spaceShip->getPoint(), spaceShip->getWidth(), spaceShip->getHeight())) {
        Point shipInitialPoint = spaceShip->getPoint();
        spaceShip->setPoint(warpZone->getEndPos());
        Point shipFinalPoint = spaceShip->getPoint();
        camera->updateCameraPosition(shipInitialPoint, shipFinalPoint);
        
        warpZone->setToBeDestroyed(true);
	}
	else if(collided(warpZone->getEndPos(),warpZone->getWidth(), warpZone->getHeight(), spaceShip->getPoint(), spaceShip->getWidth(), spaceShip->getHeight())) {
        Point shipInitialPoint = spaceShip->getPoint();
        spaceShip->setPoint(warpZone->getStartPos());
        Point shipFinalPoint = spaceShip->getPoint();
        camera->updateCameraPosition(shipInitialPoint, shipFinalPoint);
        warpZone->setToBeDestroyed(true);
	}

	for(int i = 0; i < humanListSize; i++) {
		if(collided(humanList[i].getPosition(), humanList[i].getWidth(), humanList[i].getHeight(), spaceShip->getPoint(), spaceShip->getWidth(), spaceShip->getHeight())) {

			if(humanList[i].getState() == FALLING || humanList[i].getState() == PICKED_BY_ENEMY) {
				if(humanList[i].getPosition().getY() < DisplayManager::SCREEN_HEIGHT - (DisplayManager::SCREEN_WIDTH / 8)) {
					humanList[i].setState(PICKED_BY_SPACESHIP);
                    humanList[i].updatePosition(spaceShip->getPoint(), spaceShip->getHeight(), {0,0}, 0);
				}
				else {
					//humanList[i].setState(IDLE);
				}
			}
			else if(humanList[i].getState() == PICKED_BY_SPACESHIP) {
				if(humanList[i].getPosition().getY() >= DisplayManager::SCREEN_HEIGHT - (DisplayManager::SCREEN_WIDTH / 5)) {
					humanList[i].setState(IDLE);
                    //reposition human on ground
                    humanList[i].setPosition({humanList[i].getPosition().getX(), DisplayManager::SCREEN_HEIGHT  - 165});
				}
                else{
                    humanList[i].updatePosition(spaceShip->getPoint(), spaceShip->getHeight(), {0,0}, 0);
                }
			}
		}

		for(int j = 0; j < enemyListSize; j++) {
			Bugeye* bugeye = dynamic_cast<Bugeye*>(enemyList[j]);
			if(bugeye != NULL) {
				if(collided(humanList[i].getPosition(), humanList[i].getWidth(), humanList[i].getHeight(), bugeye->getPosition(), bugeye->getWidth(), bugeye->getHeight())) {

					if(humanList[i].getState() == IDLE && bugeye->getPick() && bugeye->getHuman() == NULL) {
						humanList[i].setState(PICKED_BY_ENEMY);
                        bugeye->setHuman(&(humanList[i]));
                        humanList[i].updatePosition({0,0}, 0, bugeye->getPosition(), bugeye->getHeight());
					}
					else if(humanList[i].getState() == PICKED_BY_ENEMY  && bugeye->getHuman() == &(humanList[i])) {

						if(bugeye->getPosition().getY() <= 155) {
							humanList[i].setToBeDestroyed(true);
                            //mutate bugeye here
                            Enemy* newCrescent = new Crescent(bugeye->getPosition(), 5, 200);
                            delete enemyList[j];
                            enemyList[j] = newCrescent;
						}
					}
				}
			}
		}
	}

	for(int i = 0; i < weaponListSize; i++) {
		RedBolt* redBolt = dynamic_cast<RedBolt*>(weaponList[i]);
		OrangeGlow* orangeGlow = dynamic_cast<OrangeGlow*>(weaponList[i]);

		if(redBolt != NULL) {
			if(collided(redBolt->getPosition(), redBolt->getWidth(), redBolt->getHeight(), spaceShip->getPoint(), spaceShip->getWidth(), spaceShip->getHeight())) {

				spaceShip->setHealthStatus(spaceShip->getHealthStatus() - redBolt->getDamage());
				redBolt->setToBeDestroyed(true);
                addExplosion(redBolt->getPosition());
				if(spaceShip->getHealthStatus() <= 0) {
					spaceShip->setToBeDestroyed(true);
				}
			}
		}

		if(orangeGlow != NULL) {
			if(collided(orangeGlow->getPosition(), orangeGlow->getWidth(), orangeGlow->getHeight(), spaceShip->getPoint(), spaceShip->getWidth(), spaceShip->getHeight())) {

				spaceShip->setHealthStatus(spaceShip->getHealthStatus() - orangeGlow->getDamage());
				orangeGlow->setToBeDestroyed(true);
                addExplosion(orangeGlow->getPosition());
				if(spaceShip->getHealthStatus() <= 0) {
					spaceShip->setToBeDestroyed(true);
				}
			}
		}
	}

	for(int i = 0; i < enemyListSize; i++) {
		for(int j = 0; j < weaponListSize; j++) {
			BlueBolt* blueBolt = dynamic_cast<BlueBolt*>(weaponList[j]);
			Missile* missile = dynamic_cast<Missile*>(weaponList[j]);

			if(blueBolt != NULL) {
				if(collided(enemyList[i]->getPosition(), enemyList[i]->getWidth(), enemyList[i]->getHeight(), blueBolt->getPosition(), blueBolt->getWidth(), blueBolt->getHeight())) {

					enemyList[i]->setHealthStatus(enemyList[i]->getHealthStatus() - blueBolt->getDamage());
					blueBolt->setToBeDestroyed(true);
					if(enemyList[i]->getHealthStatus() <= 0) {
						coins = coins + enemyList[i]->getBounty();
						enemyList[i]->setToBeDestroyed(true);
					}
				}
			}
			if(missile != NULL) {
				if(collided(enemyList[i]->getPosition(), enemyList[i]->getWidth(), enemyList[i]->getHeight(), missile->getPosition(), missile->getWidth(), missile->getHeight())) {

					enemyList[i]->setHealthStatus(enemyList[i]->getHealthStatus() - missile->getDamage());
					missile->setToBeDestroyed(true);
					if(enemyList[i]->getHealthStatus() <= 0) {
						coins = coins + enemyList[i]->getBounty();
						enemyList[i]->setToBeDestroyed(true);
					}
				}
			}
		}

		if(collided(enemyList[i]->getPosition(), enemyList[i]->getWidth(), enemyList[i]->getHeight(), spaceShip->getPoint(), spaceShip->getWidth(), spaceShip->getHeight() )) {
            Spikey* spikey = dynamic_cast<Spikey*>(enemyList[i]);
            if (spikey != NULL){
                spaceShip->setHealthStatus(spaceShip->getHealthStatus() - 15);
            }
            else{
                spaceShip->setHealthStatus(spaceShip->getHealthStatus() - spaceShip->getHealthStatus());
            }
			enemyList[i]->setToBeDestroyed(true);
			if(spaceShip->getHealthStatus() <= 0) {
                spaceShip->setToBeDestroyed(true);
            }
		}
	}

	if(healthPickup != NULL) {
		if(collided(spaceShip->getPoint(), spaceShip->getWidth(), spaceShip->getHeight(), healthPickup->getPosition(), healthPickup->getWidth(), healthPickup->getHeight())) {

			if(spaceShip->getMaxHealth() >= spaceShip->getHealthStatus() + healthPickup->getAmount()) {
				spaceShip->setHealthStatus(spaceShip->getHealthStatus() + healthPickup->getAmount());
                if (pickupSound != NULL)
		            Mix_PlayChannel( -1, pickupSound, 0 );
			}
			healthPickup->setToBeDestroyed(true);
		}
	}

	if(fuelPickup != NULL) {
		if(collided(spaceShip->getPoint(), spaceShip->getWidth(), spaceShip->getHeight(), fuelPickup->getPosition(), fuelPickup->getWidth(), fuelPickup->getHeight())) {

			if(spaceShip->getMaxFuel() >= spaceShip->getFuelStatus() + fuelPickup->getAmount()) {
				spaceShip->setFuelStatus(spaceShip->getFuelStatus() + fuelPickup->getAmount());
                if (pickupSound != NULL)
		            Mix_PlayChannel( -1, pickupSound, 0 );
			}
			fuelPickup->setToBeDestroyed(true);
		}
	}

    //human with floor
    for (int i = 0; i < humanListSize; i++){
        if (humanList[i].getState() == FALLING && humanList[i].getPosition().getY() > DisplayManager::SCREEN_HEIGHT - 150){
            humanList[i].setToBeDestroyed(true);
        }
    }
}

bool GameFrame::collided(Point aPoint, int aWidth, int aHeight, Point bPoint, int bWidth, int bHeight) {
    double aW = aWidth * 0.60;
    double aH = aHeight * 0.60;
    double bW = bWidth * 0.60;
    double bH = bHeight * 0.60;

    double aX = aPoint.getX() +  (aWidth * 0.20);
    double aY = aPoint.getY() +  (aHeight * 0.20);
    double bX = bPoint.getX() +  (bWidth * 0.20);
    double bY = bPoint.getY() +  (bHeight * 0.20);
    

	if(bX >= aX + aW
	|| bX + bW <= aX
	|| bY >= aY + aH
	|| bY + bH <= aY) {
		return false;
	}
    
	return true;
}
