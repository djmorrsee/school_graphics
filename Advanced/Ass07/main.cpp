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

//~ void InitMonkey()
//~ {   
	//~ //  Copy data to vertex buffer object
    //~ glGenBuffers(1,&v_objects[0]);
    //~ glBindBuffer(GL_ARRAY_BUFFER,v_object_buffer);
    //~ glBufferData(GL_ARRAY_BUFFER,sizeof(v_data_buffer),v_objects[0],GL_STATIC_DRAW);
//~ 
	//~ //  Unbind this buffer
	//~ glBindBuffer(GL_ARRAY_BUFFER,0);
	//~ 
//~ }

void LoadShaders() {
	v_current_shader_mode = 0;
	
	std::string vert0 = "libs/dj_resources/name.vert";
	std::string frag0 = "libs/dj_resources/name.frag";
	
	v_shader_programs[v_current_shader_mode] = load_shader(vert0, frag0); // No File Suffix!
	
	
	// Repeat 
}

void LoadObjects() {
	std::string obj_file = "libs/dj_resources/objects/monkey.obj";
	dj_object monkey = load_object(obj_file);
	
}

void LoadTextures() {
	v_textures[0] = load_texture("libs/dj_resources/textures/monkey.bmp");
	
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

