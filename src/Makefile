
OBJS = Defender.cpp DisplayManager.h DisplayManager.cpp GameFrame.h GameFrame.cpp SpaceShip.h SpaceShip.cpp EventListener.h EventListener.cpp MyEnums.h Point.h Point.cpp Camera.h Camera.cpp Enemy.h Enemy.cpp

COMOBJS = Defender.cpp DisplayManager.cpp GameFrame.cpp SpaceShip.cpp EventListener.cpp Point.cpp Camera.cpp Enemy.h Enemy.cpp

CC = g++

COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2 -lSDL2_image

OBJ_NAME = out

game : $(OBJS)
	$(CC) $(COMOBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	./$(OBJ_NAME)
