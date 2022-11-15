#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include "Game.h"

Vector2 *GameSize;
Game *GameEnv;
long LastTIme = 0;
long LastFoodTime = 0;

double PreviousX;
double PreviousY;

char GamePause = 0;

void *ApplySnakeMove(void *elt, void *previousElt) {
    Vector2 *vecElt = elt;
    if (previousElt == NULL) {
        PreviousX = vecElt->x;
        PreviousY = vecElt->y;
        if (GameEnv->direction == RIGHT) {
         vecElt->x = vecElt->x + 1;
        } else if (GameEnv->direction == LEFT) {
            vecElt->x = vecElt->x - 1;
        } else if (GameEnv->direction == UP) {
            vecElt->y = vecElt->y + 1;
        } else if (GameEnv->direction == DOWN) {
            vecElt->y = vecElt->y - 1;
        }
    } else {
        double currentX = vecElt->x;
        double currentY = vecElt->y;
        vecElt->x = PreviousX;
        vecElt->y = PreviousY;
        PreviousX = currentX;
        PreviousY = currentY;
    }
    
    return (vecElt);
}

long getTimeMs() {
    struct timespec spec; 
    clock_gettime(CLOCK_REALTIME, &spec);
    long milliseconds = spec.tv_sec*1000L + spec.tv_nsec / 1.0e6; // calculate milliseconds
    return milliseconds;
}

int checkCollision(Game* game) {
    int snakeCollision = LinkedListHeadEqualsOthers(game->snake, vector2Equals); 
    if (snakeCollision) {
        return(1);
    } else {
        Vector2 *snakeHead = LinkedListGetFirstElement(game->snake);
        for (int i = 0; i < game->wallsCount; i++) {
            if (vector2Equals(snakeHead, game->walls[i])) {
                return(1);
            }
        }
    }
    return(0);
}

int checkFoodCollision(Game* game) {
    Vector2 *snakeHead = LinkedListGetFirstElement(game->snake);
    if (LinkedListFoundAndFree(game->food, snakeHead, vector2Equals)) {
        return(1);
    }
    return(0);
}

void snakeInit(Game *game) {
    printf("Snake Reset!!\n");
    if (game->snake != NULL) {
        LinkedListDestroy(game->snake);
    }
    game->snake = LinkedListNew();
    LinkedListAddElement(game->snake , vector2New(GameSize->x / 2, GameSize->y / 2));
    LinkedListAddElement(game->snake , vector2New((GameSize->x / 2) - 1, GameSize->y / 2));
    game->direction = UP;
}

void initFood(Game *game){
    printf("Food Reset!!\n");
    if (game->food != NULL) {
        LinkedListDestroy(game->food);
    }
    game->food = LinkedListNew();
}

void createFood(Game *game) {
    int modX = GameSize->x - 2;
    int modY = GameSize->y - 2;
    int rX = (rand() % modX) + 1;
    int rY = (rand() % modY) + 1;
    printf("CREATE FOOD: %i, %i\n", rX, rY);;
    LinkedListAddElement(game->food , vector2New(rX, rY));
}

void *extendSnake(void *elt, void* previousElt) {
    printf("ExtendSnake !!!!!!\n");
    Vector2 *vec = elt;
    Vector2 *previousVec = previousElt;
    Vector2 *newVec = vector2New(vec->x + (vec->x - previousVec->x), vec->y + (vec->y - previousVec->y));
    return newVec;
}

void gameCallback() {
    if (!GamePause) {
        long ms = getTimeMs();
        if (ms - LastTIme > 100) {
            LastTIme = ms;
            //printf("DO SOMETHING !!!!!!!!!\n");
            LinkedListApply(GameEnv->snake, ApplySnakeMove);
            if (checkCollision(GameEnv)) {
                printf("COLLISION !!!!!!!!!!!!!!!!!\n");
                snakeInit(GameEnv);
                initFood(GameEnv);
                createFood(GameEnv);
            }
            if (checkFoodCollision(GameEnv))  {
                printf("FOOOD !!!!!!\n");
                LinkedListCreateFromTwoLast(GameEnv->snake, extendSnake);
                createFood(GameEnv);
            }
            Square **squares = SquareGameToSquares(GameEnv->walls, GameEnv->wallsCount, GameEnv->snake, GameEnv->food);
            //SquareGamePrint(squares, game->wallsCount + game->snake->size);
            windowSetSquares(squares, GameEnv->wallsCount + GameEnv->snake->size + GameEnv->food->size);
        }
        if (ms - LastFoodTime > 1000) {
            LastFoodTime = ms;
            //createFood(GameEnv); 
        }
    }   
}

void moveLeft() {
    if (GameEnv->direction != RIGHT)
        GameEnv->direction = LEFT;
}
void moveRight() {
    if (GameEnv->direction != LEFT)
        GameEnv->direction = RIGHT;
}
void moveUp() {
    if (GameEnv->direction != DOWN)
        GameEnv->direction = UP;
}
void moveDown() {
    if (GameEnv->direction != UP)
        GameEnv->direction = DOWN;
}
void pause() {
    if (GamePause == 0) {
        GamePause = 1;
    } else {
        GamePause = 0;
    }
}

Game *gameInit(Vector2 *vec) {
    printf("GameInit\n");
    GameSize = vec;
    Game *game = malloc(sizeof(Game));
    game->wallsCount = (GameSize->x * 2) + ((GameSize->y - 2) * 2);
    game->walls = malloc(game->wallsCount  * sizeof(Vector2));
    int indexToInsert = 0;
    for (int i = 0; i < GameSize->x; i++) {
        game->walls[indexToInsert] = vector2New(i, 0);
        indexToInsert++;
        game->walls[indexToInsert] = vector2New(i, GameSize->y -1);
        indexToInsert++;
    }
    for (int i = 1; i < GameSize->y - 1; i++) {
        game->walls[indexToInsert] = vector2New(0, i);
        indexToInsert++;
        game->walls[indexToInsert] = vector2New(GameSize->x - 1, i);
        indexToInsert++;
    }

    srand(time(NULL));

    snakeInit(game);
    initFood(game);
    createFood(game);

    windowSetLoopCallback(gameCallback);
    keyboardAddCallBack('q', moveLeft);
    keyboardAddCallBack('d', moveRight);
    keyboardAddCallBack('z', moveUp);
    keyboardAddCallBack('s', moveDown);
    keyboardAddCallBack('p', pause);

    GameEnv = game;
    return(game);
}

void gamePrint(Game *game) {
    printf("GamePrint\n");
    for (int i = 0; i < game->wallsCount; i++) {
        vector2Print(game->walls[i]);
    }
}

void gameDestroy(Game *game) {
    for (int i = 0; i < game->wallsCount; i++) {
        free(game->walls[i]);
    }
    LinkedListDestroy(game->snake);
    LinkedListDestroy(game->food);
    free(game);
    free(GameSize);
}