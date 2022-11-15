#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "math/Vector.h"
#include "graphic/Graphic.h"
#include "game/Game.h"
#include "gameGraphic/GameGraphic.h"

void exitProgram(int x, int y) {
	printf("EXIT !!!\n");
	windowDetroy();
	exit(0);
}

int main(int argc, char **argv) {
	printf("Ooniki Snake\n");

	Game *game = gameInit(vector2New(30, 30));
	//gamePrint(game);

	keyboardAddCallBack(27, exitProgram);
	windowInit(argc, argv, "Ooniki Snake !!", vector2New(100, 100), vector2New(800, 600));

    return(0);
}