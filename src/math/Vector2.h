#ifndef _Vector2_
#define _Vector2_

typedef struct sVector2 {
    double x;
    double y;
} Vector2;

Vector2 *vector2New(double x, double y);

void vector2Delete(Vector2 *vec);

void vector2Print(void *vec);

int vector2Equals(void *vec1, void *vec2);

#endif