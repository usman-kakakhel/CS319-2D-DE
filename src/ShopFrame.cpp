#include "ShopFrame.h"

ShopFrame::ShopFrame(){
    init();
}

ShopFrame::~ShopFrame() {
    destroy();
}

void ShopFrame::update(Point* clickLocation, GameState* state, Item** &boughtHealthItems, int& boughtHealthItemsSize, Item** &boughtFuelItems, int& boughtFuelItemsSize, int& coins) {
	//rendering background
    	DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth+100, mCTexture->mHeight, bgPoint, {0,0}, NULL, 0, NULL, SDL_FLIP_NONE);
    	//renderin the menu text
    	Point pos;
    	pos.setX(((DisplayManager::SCREEN_WIDTH - 130)/2));
    	pos.setY(DisplayManager::SCREEN_HEIGHT / 9);
    	DisplayManager::renderText("SHOP", pos);

    	pos.setY(50);
	pos.setX(((DisplayManager::SCREEN_WIDTH - mCTexture->mWidth)/2) + mCTexture->mWidth - 100);
	DisplayManager::renderText("Coins: "  + to_string(coins), pos);

	pos.setX(((DisplayManager::SCREEN_WIDTH - mCTexture->mWidth)/2) + 50);
	pos.setY(200);
	DisplayManager::renderText("Health Upgrades", pos);

	SDL_Rect r[4];
	SDL_Rect s[4];

	SDL_SetRenderDrawColor( DisplayManager::gRenderer, 255, 0, 0, 255 );
	for(int i = 0; i < 4; i++) {
		r[i].x = ((DisplayManager::SCREEN_WIDTH - mCTexture->mWidth)/2) + 50 + (260*i);
		s[i].x = ((DisplayManager::SCREEN_WIDTH - mCTexture->mWidth)/2) + 50 + (260*i);
		r[i].y = 250;
		s[i].y = 600;
		r[i].w = 260;
		s[i].w = 260;
		r[i].h = 250;
		s[i].h = 250;
		SDL_RenderDrawRect(DisplayManager::gRenderer, &r[i]);
		SDL_RenderDrawRect(DisplayManager::gRenderer, &s[i]);
	}

	for(int i = 0; i < healthUpgradeItemsSize; i++) {
		if(healthUpgradeItems[i] == NULL || healthUpgradeItems[i]->getBought()) {
			int x0 = ((DisplayManager::SCREEN_WIDTH - mCTexture->mWidth)/2) + 50 + (260*i);
			int x1 = x0 + 260;
			int y0 = 250;
			int y1 = 250 + 250;
			SDL_RenderDrawLine(DisplayManager::gRenderer, x0, y0, x1, y1);
			x0 = x0 + 260;
			x1 = x1 - 260;
			SDL_RenderDrawLine(DisplayManager::gRenderer, x0, y0, x1, y1);
		}
	}

	for(int i = 0; i < fuelUpgradeItemsSize; i++) {
                if(fuelUpgradeItems[i] == NULL || fuelUpgradeItems[i]->getBought()) {
                        int x0 = ((DisplayManager::SCREEN_WIDTH - mCTexture->mWidth)/2) + 50 + (260*i);
                        int x1 = x0 + 260;
                        int y0 = 600;
                        int y1 = 600 + 250;
                        SDL_RenderDrawLine(DisplayManager::gRenderer, x0, y0, x1, y1);
                        x0 = x0 + 260;
                        x1 = x1 - 260;
                        SDL_RenderDrawLine(DisplayManager::gRenderer, x0, y0, x1, y1);
                }
        }

	SDL_SetRenderDrawColor( DisplayManager::gRenderer, 0, 0, 0, 0 );

	for(int i = 0; i < healthUpgradeItemsButtonsSize; i++) {
		if(healthUpgradeItemsButtons[i] != NULL && healthUpgradeItems[i] != NULL && *state == SHOP) {
			healthUpgradeItemsButtons[i]->render();
			pos.setX(healthUpgradeItemsButtons[i]->getPosition().getX()-40);
			pos.setY(healthUpgradeItemsButtons[i]->getPosition().getY());
			pos.setY(pos.getY()+70);
			DisplayManager::renderText(to_string(healthUpgradeItems[i]->getAmount())+"pts", pos);
			pos.setX(healthUpgradeItemsButtons[i]->getPosition().getX()-80);
			pos.setY(pos.getY()+50);
			DisplayManager::renderText("Price: " + to_string(healthUpgradeItems[i]->getPrice()), pos);
		}
	}

	pos.setX(((DisplayManager::SCREEN_WIDTH - mCTexture->mWidth)/2) + 50);
	pos.setY(pos.getY() + 120);
	DisplayManager::renderText("Fuel Upgrades", pos);

        for(int i = 0; i < fuelUpgradeItemsButtonsSize; i++) {
                if(fuelUpgradeItemsButtons[i] != NULL && fuelUpgradeItems[i] != NULL && *state == SHOP) {
                        fuelUpgradeItemsButtons[i]->render();
                        pos.setX(fuelUpgradeItemsButtons[i]->getPosition().getX()-50);
			pos.setY(fuelUpgradeItemsButtons[i]->getPosition().getY());
                        pos.setY(pos.getY()+70);
                        DisplayManager::renderText(to_string(fuelUpgradeItems[i]->getAmount())+"pts", pos);
                        pos.setX(fuelUpgradeItemsButtons[i]->getPosition().getX()-90);
                        pos.setY(pos.getY()+50);
                        DisplayManager::renderText("Price: " + to_string(fuelUpgradeItems[i]->getPrice()), pos);
                }
        }

    	if (backButton != NULL && *state == SHOP)
        	backButton->render();

	for(int i = 0; i < healthUpgradeItemsButtonsSize; i++) {
		if(healthUpgradeItemsButtons[i] != NULL && healthUpgradeItemsButtons[i]->isPressed(clickLocation)) {
			if(healthUpgradeItems[i] != NULL) {
				if(!healthUpgradeItems[i]->getBought()) {
					if(coins >= healthUpgradeItems[i]->getPrice()) {
						Item** newList = new Item*[boughtHealthItemsSize+1];
						for(int j = 0; j < boughtHealthItemsSize; j++) {
							newList[j] = boughtHealthItems[j];
						}
						newList[boughtHealthItemsSize] = new Item(healthUpgradeItems[i]->getAmount(), healthUpgradeItems[i]->getPrice());
						boughtHealthItemsSize++;
						if(boughtHealthItems != NULL) {
							delete [] boughtHealthItems;
						}
						boughtHealthItems = newList;

						healthUpgradeItems[i]->setBought(true);
						coins = coins - healthUpgradeItems[i]->getPrice();
					}
				}
			}
		}
	}

        for(int i = 0; i < fuelUpgradeItemsButtonsSize; i++) {
                if(fuelUpgradeItemsButtons[i] != NULL && fuelUpgradeItemsButtons[i]->isPressed(clickLocation)) {
                        if(fuelUpgradeItems[i] != NULL) {
                                if(!fuelUpgradeItems[i]->getBought()) {
                                    	if(coins >= fuelUpgradeItems[i]->getPrice()) {
						Item** newList = new Item*[boughtFuelItemsSize+1];
                                        	for(int j = 0; j < boughtFuelItemsSize; j++) {
                                                	newList[j] = boughtFuelItems[j];
                                        	}
                                        	newList[boughtFuelItemsSize] = new Item(fuelUpgradeItems[i]->getAmount(), fuelUpgradeItems[i]->getPrice());
                                        	boughtFuelItemsSize++;
                                        	if(boughtFuelItems != NULL) {
                                                	delete [] boughtFuelItems;
                                        	}
                                        	boughtFuelItems = newList;

                                        	fuelUpgradeItems[i]->setBought(true);
						coins = coins - fuelUpgradeItems[i]->getPrice();
					}
                                }
                        }
                }
        }

	if (backButton != NULL && backButton->isPressed(clickLocation) && *state == SHOP){
        	*state = PAUSE;
    	}
}

void ShopFrame::init() {
    healthUpgradeItems = new Item*[4];
    fuelUpgradeItems = new Item*[4];
    for(int i = 0; i < 4; i++) {
        healthUpgradeItems[i] = new Item(10 + (i*10), 40 + (i*10));
        fuelUpgradeItems[i] = new Item(10 + (i*10), 40 + (i*10));
    }

    healthUpgradeItemsButtons = new Button*[4];
    fuelUpgradeItemsButtons = new Button*[4];


    mCTexture = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(bGSprite, mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight);
    int x = ((DisplayManager::SCREEN_WIDTH - mCTexture->mWidth)/2);
    bgPoint.setX(x);
    bgPoint.setY(0);

    Point pos;

    pos.setX(((DisplayManager::SCREEN_WIDTH - mCTexture->mWidth)/2) + 50);
    pos.setY(50);

    backButton = new Button(pos, backButtonSprite);

    pos.setY(300);
    for(int i = 0; i < healthUpgradeItemsButtonsSize; i++) {
	pos.setX( (x+160) + (i*(mCTexture->mWidth)/4));
	healthUpgradeItemsButtons[i] = new Button(pos, healthUpgradeItemSprite);
    }

    pos.setY(pos.getY() + 350);
    for(int i = 0; i < fuelUpgradeItemsButtonsSize; i++) {
	pos.setX( (x+170) + (i*(mCTexture->mWidth)/4));
	fuelUpgradeItemsButtons[i] = new Button(pos, fuelUpgradeItemSprite);
    }
}

void ShopFrame::destroy() {
	for(int i = 0; i < healthUpgradeItemsSize; i++) {
		if(healthUpgradeItems[i] != NULL) {
			delete healthUpgradeItems[i];
		}
	}

	delete [] healthUpgradeItems;

	for(int i = 0; i < fuelUpgradeItemsSize; i++) {
                if(fuelUpgradeItems[i] != NULL) {
                        delete fuelUpgradeItems[i];
                }
        }

	delete [] fuelUpgradeItems;

	for(int i = 0; i < healthUpgradeItemsButtonsSize; i++) {
		if(healthUpgradeItemsButtons[i] != NULL) {
			delete healthUpgradeItemsButtons[i];
		}
	}

	delete [] healthUpgradeItemsButtons;

	for(int i = 0; i < fuelUpgradeItemsButtonsSize; i++) {
                if(fuelUpgradeItemsButtons[i] != NULL) {
                        delete fuelUpgradeItemsButtons[i];
                }
        }

        delete [] fuelUpgradeItemsButtons;

	delete backButton;

	if (mCTexture != NULL){
        	delete mCTexture->mTexture;
        	delete mCTexture;
        }
}
