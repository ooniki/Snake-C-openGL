#ifndef _Square_
#define _Square_

#include "../math/Vector.h"
#include "Color.h"

typedef struct sSquare {
    Vector2 *p1;
    Vector2 *p2;
    Vector2 *p3;
    Vector2 *p4;
    Color *color;
} Square;

Square *squareNew(Vector2 *p1, Vector2 *p2, Vector2 *p3, Vector2 *p4, Color *color);

void squareDraw(Square *square);

void squarePrint(Square *square);

void squareDestroy(Square *square);

#endif
