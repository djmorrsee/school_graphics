/*
 * Global Variables for the Project
 */
#ifndef __dj_vars
#define __dj_vars

#include <stdbool.h>
#include <vector>

// Motion
extern bool v_move_forward;
extern bool v_move_backward;
extern bool v_move_left;
extern bool v_move_right;

// View port
extern int v_window_width;
extern int v_window_height;
extern float v_field_of_view;
extern float v_aspect_ratio;
extern float v_clipping_plane;

// User View Rotation
extern bool v_rotate_view;
extern bool v_use_perspective;

extern float v_x_persp_rot;
extern float v_y_persp_rot;

extern float v_light_x;
extern float v_light_y;

extern float v_dim;

extern unsigned int v_object_buffer;
extern float v_data_buffer[100000];

extern glm::mat4 v_model_view_matrix;
extern glm::mat4 v_projection_matrix;

// User View LookVector

// User View Location

// Returns the vector sum of vlook_vector and vcamera_location

// Lighting
extern float v_ambient_intensity;

// Shader Modes
/* 0 - None
 * 1 - NDC->RGB
 */
extern int v_shader_mode;

// Textures
extern unsigned int v_textures[16];

// Models
extern int v_models[8];

#endif
