/*
 * glob_var.c
 *
 *  Created on: Dec 1, 2014
 *      Author: djmorrsee
 */

#include "../../dj.h"

// Motion

bool v_move_forward = false;
bool v_move_backward = false;
bool v_move_left = false;
bool v_move_right = false;

/////////


// Viewport
bool v_rotate_view = false;
bool v_use_perspective = false;

int v_window_width = 0;
int v_window_height = 0;

float v_field_of_view = 45;
float v_aspect_ratio = 1;
float v_clipping_plane = 1000;
////////////

// User View Rotation
float v_x_persp_rot = -90;
float v_y_persp_rot = 0;

float v_light_x = 0;
float v_light_y = 0;

float v_dim = 10;

vector3 v_look_vector = { .x=0, .y=0, .z=-1};

// User View Location
// This is the "origin" for gluLookAt
vector3 v_camera_location = {.x=0, .y=0, .z=10};

vector3 get_look_position()
{
	// Always look at origin for this assignment //
	vector3 f = { .x=0, .y=0, .z=0 };
	return f;
}
///////////////////////////


// Lights
light lights[8] =
{
		// Default White Lights at 0, 0, 0
		{.diffuse = { 1.0, 1.0, 1.0, 1.0}, .specular = { 1, 1, 1, 1}, .ambient = {0,0,0,1}, .position = { 0.0, 3.0, 0.0}},
		{.diffuse = { 1, 1, 1, 1}, .specular = { 1, 1, 1, 1}, .ambient = {0,0,0,1}, .position = { 0, 0, 0}},
		{.diffuse = { 1, 1, 1, 1}, .specular = { 1, 1, 1, 1}, .ambient = {0,0,0,1}, .position = { 0, 0, 0}},
		{.diffuse = { 1, 1, 1, 1}, .specular = { 1, 1, 1, 1}, .ambient = {0,0,0,1}, .position = { 0, 0, 0}},
		{.diffuse = { 1, 1, 1, 1}, .specular = { 1, 1, 1, 1}, .ambient = {0,0,0,1}, .position = { 0, 0, 0}},
		{.diffuse = { 1, 1, 1, 1}, .specular = { 1, 1, 1, 1}, .ambient = {0,0,0,1}, .position = { 0, 0, 0}},
		{.diffuse = { 1, 1, 1, 1}, .specular = { 1, 1, 1, 1}, .ambient = {0,0,0,1}, .position = { 0, 0, 0}},
		{.diffuse = { 1, 1, 1, 1}, .specular = { 1, 1, 1, 1}, .ambient = {0,0,0,1}, .position = { 0, 0, 0}}
};



float v_ambient_intensity = 0.2;
//////////

// Shaders

int v_shader_mode = 0;
///////////

// Textures
unsigned int v_textures[16] = { 0 };
///////////

// Models
int v_models[8] = { 0 };
