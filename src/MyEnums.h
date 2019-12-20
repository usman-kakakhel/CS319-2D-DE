#ifndef __MYENUMS_H
#define __MYENUMS_H

enum GameState{
    MAIN_MENU = 0,
    NEW_GAME = 1,
    RESUME = 2,
    PAUSE = 3,
    SHOP = 4,
    QUIT = 5,
    GAME_OVER = 6
};

enum SoundState{
    MENU = 0,
    GAME = 1
};

enum HumanState{
    IDLE = 0,
    PICKED_BY_ENEMY = 1,
    PICKED_BY_SPACESHIP = 2,
    FALLING = 3
};

enum Events{
    QUIT_PRESSED = 0,
    UP_PRESSED = 1,
    DOWN_PRESSED = 2,
    LEFT_PRESSED = 3,
    RIGHT_PRESSED = 4,
    BULLET_KEY = 5,
    MISSILE_KEY = 6,
    DESTRUCTION_KEY = 7,
    DEFAULT = 8
};

enum Orientation{
    RIGHT = 0,
    UP = 1,
    DOWN = 2,
    LEFT = 3,
};

#endif
