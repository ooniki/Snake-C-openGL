#include <stdio.h>
#include <GL/glut.h>
#include "Window.h"

Vector2 *WindowPosition;
Vector2 *WindowSize;
Square **WindowSquares;
int WindowSquaresSize;

void fakeLoopCallback() {
	printf("DO NOTHING!!\n");
};

LoopCallback *loopCallback = fakeLoopCallback;

void renderScene(void) {

	loopCallback();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(15, 15, 40,
			15, 15,  0,
			0.0f, 1.0f,  0.0f);	

	for(int i = 0; i < WindowSquaresSize; i++) {
		squareDraw(WindowSquares[i]);
	}

	glutSwapBuffers();
}

void changeSize(int w, int h) {
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	double ratio =  w * 1.0 / h;
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set the correct perspective.
	gluPerspective(45, ratio, 1, 200);
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void windowSetLoopCallback(LoopCallback func) {
	loopCallback = func;
}

void windowSetSquares(Square **squares, int size) {
	WindowSquaresSize = size;
	WindowSquares = squares;
};

void windowInit(int argc, char **argv, const char* name, Vector2 *position, Vector2 *size) {
	printf("Init Window\n");
	WindowPosition = position;
	WindowSize = size;
	 // init GLUT and create Window
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(WindowPosition->x, WindowPosition->y);
	glutInitWindowSize(WindowSize->x, WindowSize->y);
	glutCreateWindow(name);
	
	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	// here is the idle func registration
	glutIdleFunc(renderScene);
	// here are the new entries
	glutKeyboardFunc(keyboardProcessKey);

	//loopCallback = fakeLoopCallback;

	//glClearColor(0.176, 0.55, 0.41, 255);
	glClearColor(0.1, 0.1, 0.1, 255);

	// enter GLUT event processing cycle
	glutMainLoop();
}

void windowDetroy() {
	printf("Destroy Window\n");
	vector2Delete(WindowPosition);
	vector2Delete(WindowSize);
}