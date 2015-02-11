/*
 * This is a common header file for the project 
 * Modified from CSCIx229.h
 */
#ifndef __DJ
#define __DJ

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

#include <string.h>
#include <vector>
#include <math.h>

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef USEGLEW
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES

#include "GLFW/glfw3.h"

#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))

typedef enum { left=0, right, forward, backward, up, down } facing_t;

// Program Constants and Variables
#include "libs/dj_globals/glob_const.h"
#include "libs/dj_globals/glob_var.h"

// DJ Functions
#include "libs/dj_scene/motion.h"
#include "libs/dj_scene/lighting.h"
#include "libs/dj_resources/shaders.h"
#include "libs/dj_resources/textures.h"

void load_obj(const char* filename, std::vector<glm::vec4> &verts, 
									std::vector<glm::vec3> &norms, 
									std::vector<glm::vec3> &colors, 
									std::vector<glm::vec2> &tcs);

// GLUT Bound Functions // 
void display(GLFWwindow* window); 					// display.c
void reshape(int x, int y);				// reshape.c
void special(int key, int x, int y);			// special.c
void key(unsigned char ch, int x, int y);		// key.c
void key_up(unsigned char ch, int x, int y);		// key.c
void idle();						// idle.c
void mouse_move(int x, int y);				// mouse_move.c
void mouse_click(int button, int state, int x, int y); 	// mouse_move.c

// Helper Functions From CSCIx239 //
void         Print(const char* format , ...);
void         Fatal(const char* format , ...);
void         ErrCheck(const char* where);
unsigned int LoadTexBMP(const char* file);
void         Project();
int          LoadOBJ(const char* file);
int          FramesPerSecond(void);
double       Elapsed(void);
void         CreateShader(int prog,const GLenum type,const char* file);
void         PrintProgramLog(int obj);
int          CreateShaderProg(const char* VertFile,const char* FragFile);
int          CreateNoise3D(int unit);

#endif
