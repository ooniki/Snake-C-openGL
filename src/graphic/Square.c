#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include "Square.h"

Square *squareNew(Vector2 *p1, Vector2 *p2, Vector2 *p3, Vector2 *p4, Color *color) {
    Square *square = malloc(sizeof(Square));
    square->p1 = p1;
    square->p2 = p2;
    square->p3 = p3;
    square->p4 = p4;
    square->color = color;
    return square;
}

void squareDraw(Square *square) {
    //printf("SQUARE DRAW\n");
    glColor4d(square->color->red, square->color->green, square->color->blue, 1);
    glBegin(GL_QUADS);
	glVertex3f(square->p1->x, square->p1->y, 0);
    glVertex3f(square->p2->x, square->p2->y, 0);
    glVertex3f(square->p3->x, square->p3->y, 0);
    glVertex3f(square->p4->x, square->p4->y, 0);
	glEnd();
}

void squarePrint(Square *square) {
    printf("------------------SQUARE------------------\n");
    vector2Print(square->p1);
    vector2Print(square->p2);
    vector2Print(square->p3);
    vector2Print(square->p4);
    ColorPrint(square->color);
    printf("------------------------------------------\n");
}

void squareDestroy(Square *square) {
    free(square->p1);
    free(square->p2);
    free(square->p3);
    free(square->p4);
    free(square->color);
    free(square);
}