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
	
	std::string vert0 = "libs/dj_resources/shaders/gl430.vert";
	std::string frag0 = "libs/dj_resources/shaders/gl430.frag";
	
	std::string frag1 = "libs/dj_resources/shaders/laplacian.frag";
	
	std::string frag2 = "libs/dj_resources/shaders/edge.frag";
	
	
	
	v_shader_programs[0] = load_shader(vert0.c_str(), frag0.c_str());
	v_shader_programs[1] = load_shader(NULL, frag1.c_str());
	v_shader_programs[2] = load_shader(NULL, frag2.c_str());
	
	// Repeat 
}

void LoadObjects() {
	v_objects[0] = create_object_from_parsed();
	
}

void LoadTextures() {
	// Handled in object creation!
	//v_textures[0] = load_texture("libs/dj_resources/textures/monkey.bmp");   
	
	//  Image texture
   glGenTextures(1,&v_textures[0]);
   glBindTexture(GL_TEXTURE_2D,v_textures[0]);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	
	// Repeat
}

void SetupScene () {
	LoadShaders();
	LoadObjects();
	LoadTextures();
}

void SetupGLUT(int argc, char* argv[]) 
{
	pthread_getconcurrency();
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE | GLUT_STENCIL);
	glutInitWindowSize(v_window_size.x, v_window_size.y);
	glutCreateWindow("Advanced Graphics Assignment 04");

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
	glutMotionFunc(mouse_move);
	
	glutMainLoop();
}

