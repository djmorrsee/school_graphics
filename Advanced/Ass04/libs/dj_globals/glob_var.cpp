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

// User View Location
unsigned int v_object_buffer;
float v_data_buffer[100000] = { 0.0f };

glm::mat4 v_model_view_matrix = glm::mat4();
glm::mat4 v_projection_matrix = glm::mat4();

///////////////////////////


// Lights

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
