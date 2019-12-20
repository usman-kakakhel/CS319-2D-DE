#ifndef __SHOPFRAME_H
#define __SHOPFRAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "DisplayManager.h"
#include "Item.h"
#include "Button.h"
#include "MyEnums.h"

// Items for purchase
// SkinItem* skinItem = NULL;
// DamageItem* damageItem = NULL;
// ShieldItem* shieldItem = NULL;

class ShopFrame {
public:
	ShopFrame();
	~ShopFrame();

	void init();
	void destroy();
	void update(Point* pressPoint, GameState* state, Item** &boughtHealthItems, int& boughtHealthItemsSize , Item** &boughtFuelItems, int& boughtFuelItemsSize, int& coins);

private:
	Item** healthUpgradeItems;
        int healthUpgradeItemsSize = 4;
	Item** fuelUpgradeItems;
        int fuelUpgradeItemsSize = 4;

        Button** healthUpgradeItemsButtons;
	int healthUpgradeItemsButtonsSize = 4;
        Button** fuelUpgradeItemsButtons;
	int fuelUpgradeItemsButtonsSize = 4;

	// Shield Item
	string healthUpgradeItemSprite = "../resources/health.png";
	// Damage Item
	string fuelUpgradeItemSprite = "../resources/fuel.png";

	// Back to previous menu button
    	Button* backButton;
	string backButtonSprite = "../resources/back.png";

	//background position
    	Point bgPoint;

	//textures and image addresses
	DisplayManager::CustomTexture* mCTexture = NULL;
	string bGSprite = "../resources/menuBackground.png";
};

#endif

