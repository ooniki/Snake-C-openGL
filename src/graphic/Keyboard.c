#include "Keyboard.h"

KeyboardCallBack callbakcs[256];

void keyboardAddCallBack(unsigned char key, KeyboardCallBack callBack) {
    callbakcs[key] = callBack;
}

void keyboardProcessKey(unsigned char key, int x, int y) {
    callbakcs[key](x, y);
}