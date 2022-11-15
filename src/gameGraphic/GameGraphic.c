#include <stdlib.h>
#include <stdio.h>
#include "GameGraphic.h"

int SquareSize = 1;
int SquareIndex = 0;

Color *GameColor;

void applyVectorToSquare(void *data, void **array) {
    if (data != NULL) {
        Square **squares = (Square**)array;
        Vector2 *vec = (Vector2*)data;
        squares[SquareIndex] = squareNew(
                vector2New(vec->x, vec->y),
                vector2New(vec->x + SquareSize, vec->y),
                vector2New(vec->x + SquareSize, vec->y + SquareSize),
                vector2New(vec->x, vec->y + SquareSize),
                ColorNew(GameColor->red, GameColor->green, GameColor->blue)
            );
        SquareIndex++;
    }
}

Square **SquareGameToSquares(Vector2 **walls, int wallsCount, LinkedList *snake,  LinkedList *food) {
    Square **squares = malloc((wallsCount + snake->size + food->size) * sizeof(Square*));

    GameColor = ColorNew(0, 0.5, 0);
    LinkedListApplyAndFill(snake, (void**)squares, applyVectorToSquare);
    GameColor = ColorNew(0.5, 0, 0);
    LinkedListApplyAndFill(food, (void**)squares, applyVectorToSquare);

    for (int i = 0; i < wallsCount; i++) {
        Vector2 *currentWall = walls[i];
        squares[SquareIndex] = squareNew(
            vector2New(currentWall->x, currentWall->y),
            vector2New(currentWall->x + SquareSize, currentWall->y),
            vector2New(currentWall->x + SquareSize, currentWall->y + SquareSize),
            vector2New(currentWall->x, currentWall->y + SquareSize),
            ColorNew(0.0, 0.0, 0.5)
        );
        SquareIndex++;
    }
    SquareIndex = 0;
    return squares;
}

void SquareGameDestroy(Square ** squares, int size) {
    for (int i = 0; i < size; i++) {
        squareDestroy(squares[i]);
    }
}

void SquareGamePrint(Square **squares, int size) {
    for (int i = 0; i < size; i++) {
        squarePrint(squares[i]);
    }
}