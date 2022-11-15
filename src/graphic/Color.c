#include <stdlib.h>
#include <stdio.h>
#include "Color.h"

Color *ColorNew(double red, double green, double blue) {
    Color *color = malloc(sizeof(Color));
    color->red = red;
    color->green = green;
    color->blue = blue;
    return color;    
}

void ColorPrint(Color *color) {
    printf("Color: red(%f), green(%f), blue(%f)\n", color->red, color->green, color->blue);
}

void ColorDestroy(Color *color) {
    free(color);
}