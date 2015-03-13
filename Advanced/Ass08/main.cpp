/*
 * 
 */
#include "dj.h"
#include <pthread.h>

void SetupGLUT(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	
	SetupGLUT(argc, argv);
	return 0;
}

void LoadShaders() {
	v_current_shader_mode = 0;
	
	std::string frag0 = "libs/dj_resources/shaders/draw.frag";

	v_shader_programs[0] = load_shader(NULL, frag0.c_str());

	// Repeat 
}

void LoadObjects() {
	
}

void LoadTextures() {
	// Handled in object creation!
	v_textures[0] = 0;   
	
	//  Image texture
   //~ glGenTextures(1,&v_textures[0]);
   glBindTexture(GL_TEXTURE_2D,v_textures[0]);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	//~ 
	// Repeat
}

void SetupScene () {
	LoadShaders();
	LoadObjects();
	LoadTextures();
	
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void SetupGLUT(int argc, char* argv[]) 
{
	pthread_getconcurrency();
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(v_window_size.x, v_window_size.y);
	glutCreateWindow("Advanced Graphics Assignment 08");

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

