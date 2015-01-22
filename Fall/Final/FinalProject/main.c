/*
 * 
 */
#include "dj.h"

void SetupGLUT(int argc, char* argv[]);
void SetupScene();

int main(int argc, char* argv[]) {
	SetupGLUT(argc, argv);
	return 0;
}

void SetupScene() {
	v_window_height = v_window_width = c_window_size;
	glutSetKeyRepeat(0);

	// GL Settings //
	glClearColor(1, 0, 1, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	GLfloat amb[] = { v_ambient_intensity, v_ambient_intensity,
			v_ambient_intensity, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

	load_shaders();
	setup_textures();
}

// Bootstrap function to start the GLUT window and bindings
void SetupGLUT(int argc, char* argv[]) {
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE | GLUT_STENCIL);
	glutInitWindowSize(c_window_size, c_window_size);
	glutCreateWindow("CSCI 4229 Final Project");

	SetupScene();

	// Callback Bindings
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutKeyboardFunc(key);
	glutKeyboardUpFunc(key_up);
	glutMouseFunc(mouse_click);
	glutMotionFunc(mouse_move);
	glutMotionFunc(mouse_move);
	glutMainLoop();
}
