#include <stdlib.h>
#include <stdio.h>
#include "Vector2.h"

Vector2 *vector2New(double x, double y) {
    Vector2 *vec = malloc(sizeof(Vector2));
    vec->x = x;
    vec->y = y;
    return (vec);
}

void vector2Delete(Vector2 *vec) {
    free(vec);
}

void vector2Print(void *vec) {
    Vector2 *myVec = (Vector2*)vec;
    printf("Vector2: %f, %f\n", myVec->x, myVec->y);
}

int vector2Equals(void *vec1, void *vec2) {
    Vector2 *myVec1 = (Vector2*)vec1;
    Vector2 *myVec2 = (Vector2*)vec2;
    if (vec1 != NULL && vec2 != NULL && myVec1->x == myVec2->x && myVec1->y == myVec2->y) {
        return(1);
    } else {
        return(0);
    }
}