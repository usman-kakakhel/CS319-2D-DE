#ifndef __FIRE_ORANGE_GLOW_H
#define __FIRE_ORANGE_GLOW_H

#include "FiringBehavior.h"
#include "OrangeGlow.h"

class FireOrangeGlow : public FiringBehavior {
	public:
		void fire(TargetedWeapon** &weaponList, int &size, Point spaceShipPos, Point newPos, int newOrientation) override;
};

#endif
