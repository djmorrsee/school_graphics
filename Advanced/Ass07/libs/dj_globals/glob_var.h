/*
 * Global Variables for the Project
 */
#ifndef __dj_vars
#define __dj_vars

#include <stdbool.h>

// Screen Dimensions
extern glm::vec2 v_window_size;

// Viewport
extern float v_dim;
extern float v_field_of_view;
extern float v_aspect_ratio;
extern float v_clipping_plane;

extern bool v_use_perspective;

// Motion Variables
extern float v_x_rot;
extern float v_y_rot;
extern float v_rot_speed;

extern float v_x_loc;
extern float v_y_loc;
extern float v_z_loc;

// Do Motion
extern bool v_move_forward;
extern bool v_move_backward;
extern bool v_move_left;
extern bool v_move_right;

extern bool v_rotate_view;

// Objects
extern int v_objects[8];

// Textures
extern unsigned int v_textures[16];

// Shader Programs
extern int v_shader_programs[dj_constants::c_max_shaders];
extern int v_current_shader_mode;

// Lights
extern float v_ambient_intensity;
extern dj_light lights[8];

#endif
