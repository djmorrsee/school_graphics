/*
 * glob_var.c
 *
 *  Created on: Dec 1, 2014
 *      Author: djmorrsee
 */

#include "../../dj.h"

// Screen Dimensions
int v_screen_width = 600;
int v_screen_height = 600;
/////////

// Motion
bool v_move_forward = false;
bool v_move_backward = false;
bool v_move_left = false;
bool v_move_right = false;
/////////

// Viewport
bool v_use_perspective = false;
bool v_rotate_view = false; // Enable Mouse Rotation?

int v_window_width = dj_constants::c_window_size;
int v_window_height = dj_constants::c_window_size;

float v_dim = 10;
float v_field_of_view = 45;
float v_aspect_ratio = 1;
float v_clipping_plane = 1000;
////////////

// User View Rotation
float v_x_persp_rot = -90;
float v_y_persp_rot = 0;
float v_rot_speed = 5;

// User View Location
unsigned int v_object_buffer;
float v_data_buffer[100000] = { 0.0f };
///////


// GLM Matrices
glm::mat4 v_model_view_matrix = glm::mat4();
glm::mat4 v_projection_matrix = glm::mat4();
///////////////////////////


// Lights

float v_ambient_intensity = 1.0f;
extern LightProperties v_lights[8] = { LightProperties() };
//////////

// Shaders

int v_shader_mode = 0;
///////////

// Textures
unsigned int v_textures[16] = { 0 };
///////////

// Models
int v_models[8] = { 0 };
