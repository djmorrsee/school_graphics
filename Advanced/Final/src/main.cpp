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
	//~ chunk chk = CreateChunk(3);
	//~ printf("%i\n", chk.blocks[0][0][0].block_id);
	//~ printf("%i\n\n", chk.blocks[0][0][1].block_id);
	
	//~ std::vector<int> ids;
	//~ ids = GetBlockList(chk);
	
	//~ printf("%i\n", ids.at(0));
	//~ printf("%i\n\n", ids.at(1));
	
	//~ int* vals = &ids[0];
	//~ printf("%i\n", vals[0]);
	//~ printf("%i\n\n", vals[1]);
	
	//~ v_block_texture_id = BindChunkTexture(chk);
	
	//~ glGenTextures(1, &v_block_texture_id);
	//~ glBindTexture(GL_TEXTURE_1D, v_block_texture_id);
	//~ 
	//~ int vals [] = {
		//~ 1, 1, 1,
		//~ 1, 1, 1,
		//~ 1, 1, 1,
	//~ };
	//~ 
	//~ glTexImage1D(GL_TEXTURE_1D, 0, GL_RED, 9, 0, GL_RED,GL_INT, vals);
	//~ if(glGetError()) Fatal("Error Sending Texture");
	//~ 
	//~ glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//~ glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
}

void SetupScene () {
	
	LoadShaders();
	LoadObjects();
	LoadTextures();
	
	glClearColor(0.0, 0.0, 0.0, 1.0);
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

