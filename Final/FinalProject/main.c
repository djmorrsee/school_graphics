/*
 * 
 */
#include "dj.h"

void SetupGLUT(int argc, char* argv[]);
void SetupScene();

int main (int argc, char* argv[]) 
{
	SetupGLUT(argc, argv);
	return 0;
}

void SetupScene () 
{
	
}

// Bootstrap function to start the GLUT window and bindings
void SetupGLUT(int argc, char* argv[])
{
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE | GLUT_STENCIL);
	glutInitWindowSize(window_size, window_size);
	glutCreateWindow("CSCI 4229 Final Project");

	SetupScene();

	// Callback Bindings
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutKeyboardFunc(key);
    glutMotionFunc(mouse_move);
	glutMainLoop();
}
