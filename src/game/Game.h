#ifndef _Game_
#define _Game_

#include "../math/Vector.h"
#include "../linkedList/LinkedList.h"
#include "../graphic/Graphic.h"
#include "../gameGraphic/GameGraphic.h"

typedef enum eDirection{
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef struct sGame {
    Vector2 **walls;
    int wallsCount;
    LinkedList *snake;
    LinkedList *food;
    Direction direction;
} Game;

Game *gameInit(Vector2 *vec);

void gamePrint(Game *game);

void gameDestroy(Game *game);

#endif