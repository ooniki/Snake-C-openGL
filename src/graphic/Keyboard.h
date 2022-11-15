#ifndef _Keyboard_
#define _Keyboard_

typedef void (*KeyboardCallBack)(int x, int y);

void keyboardAddCallBack(unsigned char key, KeyboardCallBack callBack);

void keyboardProcessKey(unsigned char key, int x, int y);

#endif