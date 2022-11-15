#ifndef _GameGraphic_
#define _GameGraphic_


#include "../graphic/Graphic.h"
#include "../linkedList/LinkedList.h"

Square **SquareGameToSquares(Vector2 **walls, int wallsCount, LinkedList *snake, LinkedList *food);

void SquareGamePrint(Square **squares, int size);

#endif