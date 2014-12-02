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
#include <math.h>

#include <GL/glut.h>

#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))

typedef enum { left=0, right, forward, backward, up, down } facing_t;


// Program Constants and Variables
#include "glob_const.h"
#include "glob_var.h"

// DJ Functions
#include "dj_structures.h"
#include "dj_primitives.h"




// GLUT Bound Functions // 
void display();
void reshape(int x, int y);
void special(int key, int x, int y);
void key(unsigned char ch, int x, int y);
void idle();
void mouse_move(int x, int y);

// DJ Structures //



// Helper Functions From CSCIx229 //
void Print(const char* format, ...);
void Project();
unsigned int LoadBMPTexture(const char* filepath);

#endif
