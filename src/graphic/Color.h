#ifndef _Color_
#define _Color_

typedef struct sColor {
    double red;
    double green;
    double blue;
} Color;

Color *ColorNew(double red, double green, double blue);

void ColorPrint(Color *color);

void ColorDestroy(Color *color);

#endif