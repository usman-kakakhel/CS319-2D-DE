#include "FireOrangeGlow.h"

void FireOrangeGlow::fire(TargetedWeapon** &weaponList, int &size, Point spaceShipPos, Point newPos, int newOrientation) {
        //make a new list of weapons
        size++;
        TargetedWeapon** newList = new TargetedWeapon*[size];

        //copy existing list to new one
        for (int i = 0; i < size - 1; i++){
            newList[i] = weaponList[i];
        }
        //new bullet
        newList[(size - 1)] = new OrangeGlow(newPos, 13, 30, newOrientation);
        //delete existing list
        if(weaponList != NULL)
            delete [] weaponList;

        weaponList = newList;
}