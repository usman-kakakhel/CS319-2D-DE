
OBJS = Defender.cpp DisplayManager.h DisplayManager.cpp GameFrame.h GameFrame.cpp SpaceShip.h SpaceShip.cpp EventListener.h EventListener.cpp MyEnums.h Point.h Point.cpp Camera.h Camera.cpp  Asteroid.h Asteroid.cpp BlueBolt.h BlueBolt.cpp Bullet.h Bullet.cpp ClearScreen.h ClearScreen.cpp MassDestructionWeapon.h MassDestructionWeapon.cpp Missile.h Missile.cpp OrangeGlow.h OrangeGlow.cpp RedBolt.h RedBolt.cpp TargetedWeapon.h TargetedWeapon.cpp Weapon.h Weapon.cpp 

COMOBJS = Defender.cpp DisplayManager.cpp GameFrame.cpp SpaceShip.cpp EventListener.cpp Point.cpp Camera.cpp Asteroid.cpp BlueBolt.cpp Bullet.cpp ClearScreen.cpp MassDestructionWeapon.cpp Missile.cpp OrangeGlow.cpp RedBolt.cpp TargetedWeapon.cpp Weapon.cpp 

CC = g++

COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

OBJ_NAME = out

game : $(OBJS)
	$(CC) $(COMOBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	./$(OBJ_NAME)
