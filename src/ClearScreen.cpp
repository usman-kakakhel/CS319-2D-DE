#include "ClearScreen.h"

//constructor
ClearScreen::ClearScreen(int damageValue, int radiusValue): MassDestructionWeapon(damageValue, radiusValue){
        
}

//destructor
ClearScreen::~ClearScreen(){
        damage = 0;
        blastRadius = 0;
}

