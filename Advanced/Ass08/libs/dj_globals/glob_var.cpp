/*
 * glob_var.c
 *
 *  Created on: Dec 1, 2014
 *      Author: djmorrsee
 * 
 * Format: v_variable_name
 */

#include "../../dj.h"

// Drawing Vars (specific to Ass08)
int v_draw_color = 1;
bool v_first_draw = true;
bool v_clear_draw = false;

// Screen Dimensions
glm::vec2 v_window_size = 
	glm::vec2(dj_constants::c_window_size, dj_constants::c_window_size);
	
// Cursor Info
int v_cursor_x = 0;
int v_cursor_y = 0;

int v_cursor_down = 0;

// Viewport
float v_dim = 3;
float v_field_of_view = 45;
float v_aspect_ratio = 1;
float v_clipping_plane = 1000;

bool v_use_perspective = false;

// Motion Variables
float v_x_rot = -90;
float v_y_rot = 0;
float v_rot_speed = 5;

float v_x_loc = 0;
float v_y_loc = 0;
float v_z_loc = 0;

// Do Motion
bool v_move_forward = false;
bool v_move_backward = false;
bool v_move_left = false;
bool v_move_right = false;

bool v_rotate_view = false;

// Objects
dj_object v_objects[8];

// Textures
unsigned int v_textures[16] = { 0 };

// Shader Programs
int v_shader_programs[dj_constants::c_max_shaders] = { 0 };
int v_current_shader_mode = 0;

// Lights
float v_ambient_intensity = 1.0f;
dj_light lights[8];

