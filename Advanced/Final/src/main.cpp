/*
 * 
 */
#include "dj.h"
#include <pthread.h>
#include <map>

void SetupGLUT(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	srand(time(NULL));

	
	SetupGLUT(argc, argv);
	return 0;
}

void LoadShaders() {
	v_current_shader_mode = 0;
	
	std::string vert0 = "shaders/simple.vert";
	std::string frag0 = "shaders/simple.frag";
	std::string geo0 = "shaders/terrain.geom";

	v_shader_programs[0] = load_shader(vert0.c_str(), frag0.c_str(), geo0.c_str());

	// Repeat 
}

void LoadObjects() {

}

void LoadTextures() {
	v_textures[0] = load_texture("textures/atlas.bmp");
}

void SetupScene () {
	
	LoadShaders();
	LoadObjects();
	LoadTextures();
	
	glClearColor(0.0, 0.75, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);

}

void SetupGLUT(int argc, char* argv[]) 
{
	pthread_getconcurrency(); // Weird fix for an even more weird linking bug
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE | GLUT_ALPHA);
	glutInitWindowSize(v_window_size.x, v_window_size.y);
	glutCreateWindow("Advanced Graphics Assignment 09");

	// Scene Specific Setup (Textures, Shaders, Objects)
	SetupScene();

	// GLUT Callback Bindings
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutKeyboardFunc(key);
	glutKeyboardUpFunc(key_up);
	glutMouseFunc(mouse_click);
	glutMotionFunc(mouse_move);
	
	glutMainLoop();
}

