#ifndef _Window_
#define _Window_

#include "../math/Vector.h"
#include "Keyboard.h"
#include "Square.h"

typedef void (LoopCallback)();

void windowSetLoopCallback(LoopCallback func);

void windowInit(int argc, char **argv, const char* name, Vector2 *position, Vector2 *size);

void windowSetSquares(Square **squares, int size);

void windowDetroy();

#endif