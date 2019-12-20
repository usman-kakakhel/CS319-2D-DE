
OBJS = Defender.cpp DisplayManager.h DisplayManager.cpp GameFrame.h GameFrame.cpp SpaceShip.h SpaceShip.cpp EventListener.h EventListener.cpp MyEnums.h Point.h Point.cpp Camera.h Camera.cpp  Asteroid.h Asteroid.cpp BlueBolt.h BlueBolt.cpp Bullet.h Bullet.cpp NuclearBomb.h NuclearBomb.cpp MassDestructionWeapon.h MassDestructionWeapon.cpp Missile.h Missile.cpp OrangeGlow.h OrangeGlow.cpp RedBolt.h RedBolt.cpp TargetedWeapon.h TargetedWeapon.cpp Weapon.h Weapon.cpp Human.h Human.cpp Enemy.h Enemy.cpp Saucer.h Saucer.cpp Slicer.h Slicer.cpp Spikey.h Spikey.cpp Bugeye.h Bugeye.cpp SaucerBlades.h SaucerBlades.cpp Crescent.h Crescent.cpp FiringBehavior.h FiringBehavior.cpp FireRedBolt.h FireRedBolt.cpp FireOrangeGlow.h FireOrangeGlow.cpp WarpZone.h WarpZone.cpp MenuFrame.h MenuFrame.cpp Button.h Button.cpp MapView.h MapView.cpp Pickup.h Pickup.cpp FuelPickup.h FuelPickup.cpp HealthPickup.h HealthPickup.cpp DataManager.h DataManager.cpp Explosion.h Explosion.cpp ShopFrame.h ShopFrame.cpp Item.h Item.cpp

COMOBJS = Defender.cpp DisplayManager.cpp GameFrame.cpp SpaceShip.cpp EventListener.cpp Point.cpp Camera.cpp Asteroid.cpp BlueBolt.cpp Bullet.cpp NuclearBomb.cpp MassDestructionWeapon.cpp Missile.cpp OrangeGlow.cpp RedBolt.cpp TargetedWeapon.cpp Weapon.cpp Human.cpp Enemy.cpp Saucer.cpp Spikey.cpp Bugeye.cpp SaucerBlades.cpp Crescent.cpp Slicer.cpp FiringBehavior.cpp FireRedBolt.cpp FireOrangeGlow.cpp WarpZone.cpp MenuFrame.cpp Button.cpp MapView.cpp Pickup.cpp FuelPickup.cpp HealthPickup.cpp DataManager.cpp Explosion.cpp ShopFrame.cpp Item.cpp

CC = g++

CCVER = -std=c++0x

THR = -pthread

COMPILER_FLAGS = -w -g -ggdb3

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

OBJ_NAME = out

game : $(OBJS)
	$(CC) $(CCVER) $(THR) $(COMOBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	./$(OBJ_NAME)
